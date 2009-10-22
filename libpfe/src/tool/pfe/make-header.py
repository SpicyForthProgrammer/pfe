#! /usr/bin/env python
import sys
import re
import os
import os.path
import string
import time

def m(obj, regex):
    return re.search(regex, obj)
def s(obj, regex,replace):
    return re.sub(regex, replace, obj)
def test_s(path):
    return os.path.isfile(path) and os.path.getsize(path)

helpstring = """ <*.c file>
\t scan the C file in the pfe/* source directory and regenerate
\t the header file derived from them. The script will look for:
\t - a global comment block at the start of the file to be copied
\t - FXCode(name) definitions unless they are marked 'static'
\t - a preceding comment block before that FXCode extern
\t - any C declaration preceded by '_extern' copied to 'extern'
\t - a preceding comment block before that _extern prototope
\t - multiple lines between #ifndef _extern...#endif\\n with the
\t   ifndef removed. Header #includes are moved to the top of the.
\t   generated output file right after the initial #include
\t The body of each regenerated header file is wrapped in the
\t usual #ifndef once_declare...#endif derived from the filename
\t of the input/output file. The output file has just the .h ext
\t replaced with a .c extension. Additionally each header file has
\t an 'initial include' file required to typedef the most basic
\t pfe idioms including the #define FXCode(). In pfe each of the
\t c source files has a two part stem worset-ext.c and the part
\t after the last hyphen determines the variant of the initial
\t include file - pfe-sub.h, pfe-ext.h, pfe-mix.h etc.
"""
if len(sys.argv) == 1: print sys.argv[0], helpstring ; sys.exit(1)

programname = sys.argv[0]
inputfile = sys.argv[1]
outputfile = None
if len(sys.argv) > 2:
    outputfile = sys.argv[2]

file = os.path.basename(inputfile)
if not outputfile:
    outputfile = s(file, r"\.c",r".h")

pfe = os.path.dirname(outputfile)
if not len(pfe): pfe="../pfe"

inc = ""
x = m(file,r"-(\w\w\w).c$")
if x:
    if test_s(pfe+"/incl-"+x.group(1)+".h"):
        inc = "<pfe/incl-"+x.group(1)+".h>"
    if test_s(pfe+"/pfe-"+x.group(1)+".h"):
        inc = "<pfe/pfe-"+x.group(1)+".h>"
#
x = m(file,r"-(\w\w\w\w).c$")
if x:
    if test_s(pfe+"/def-"+x.group(1)+".h"):
        inc = "<pfe/def-"+x.group(1)+".h>"
    if test_s(pfe+"/pfe-"+x.group(1)+".h"):
        inc = "<pfe/pfe-"+x.group(1)+".h>"
#

if not len(inc):
    print >>sys.stderr, file, " " * (27-len(file))," skipped (pfe='"+pfe+"')"
    sys.exit()

inc_outputfile = outputfile
if outputfile == os.path.basename(outputfile) or "/include/" in outputfile:
    found = re.search(".*/include/(.*)", os.getcwd())
    if found: inc_outputfile = found.group(1) + "/" + outputfile

tr_cpp = string.maketrans("./-"+string.lowercase, "___"+string.uppercase)
once = s(string.translate(inc_outputfile,tr_cpp), r"_+",r"_")
print once,
if len(once) < 27 : print " " * (27 - len(once)),

prg = s(programname, r".*/([^/]*)$", r"\1")

out = ""
out += "#ifndef "+once+"\n"
out += "#define "+once+" "+"%i"%time.time()+"\n"
out += "/* generated"+time.strftime(" %Y-%m%d-%H%M ", time.localtime())+\
       prg+" "+inputfile+" */\n\n"

T = ""
try:
    F = open(inputfile,"r")
except IOError, x:
    print "no input text:",inputfile,":",str(x)
    sys.exit()
else:
    T = F.read()
    F.close()

ext = ""
def ext_append(text): global ext; ext += text ; return ""
def out_append(text): global out; out += text ; return ""

T = s(T, r"(?sx) (\#ifn?def\s+_export\s+ (?:\#define\s+_export\s+)?) "
      r"         ((?:.(?!\#endif))*.) "
      r"         (\#endif)  ",
      lambda x : ext_append(x.group(2)))

if not m(ext, r"^\s*\#\s*include\s*[\<\"]"):
    out_append("#include "+inc+"\n")
ext = s(ext, r"(?x) ( \#\s*include\s*[\<\"][^<>\"]*[\"\>]\s* ) ",
  lambda x : out_append(x.group(1)))
T = s(T, r"(?sx) ^ ( \/\*\*\s (?:.(?!\*\/))* .\*\/ ) ",
      lambda x : out_append("\n"+x.group(1)+"\n"))
out += "\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n"
out += "\n"+ext+"\n"
def q1_(doc,pre,decl,args):
    global out
    if doc is None: doc = ""
    if not m(pre, r"(static|extern)"):
        pre = s(pre, r"^\s*", r"\nextern ")
        pre = s(pre, r"\s*$", r" ")
        if decl not in ["FXCode", "FXCode_XE", "FXCode_RT", "P4_CODE"]:
            decl = "P4_CODE" ; pre = "\nextern "
        args = s(args, r"(?s)\s+", r" ")
        if doc: doc = "\n"+doc
        out += doc+pre+decl+args+";\n"
    return ""
T = s(T, r"(?sx) (\/\*\*\s(?:.(?!\*\/))*.\*\/)?"
      r"         (\s*(?:\w+\s+)*)"
      r"         \b (FXCode|FXCode_XE|FXCode_RT|P4_CODE) (\s*\(\s* \w+ \))",
      lambda x : q1_(x.group(1), x.group(2), x.group(3), x.group(4)))

def q2_(a,b,c,d):
    global out
    if a is None: a = ""
    if not m(b, r"(static|extern)$"):
        b = s(b, r"_export", r"_extern")
        if not m(b, r"extern\s*$"): b += " extern "
        b = s(b, r"^\s*", r"\n")
        b = s(b, r"\s*$", r" ")
        c = s(c, r"(?s)\s+", r" ")
        d = "; /*"+d+"*/"
        if a : a = "\n"+a
        out += a+b+c+d+"\n"
    return ""
T = s(T, r"(?sx) (/\*\*\s(?:.(?!\*\/))*.\*\/)? "
      r"         (\s*_export) \b ([^;{}=]+) ([;{}=]) ",
      lambda x : q2_(x.group(1), x.group(2), x.group(3), x.group(4)))

def q3_(a,b,c,d):
    global out
    if a is None: a = ""
    if not m(b, r"(static|extern|_export)"):
        b = s(b, r"^\s*", r"\nextern ")
        b = s(b, r"\s*$", r" ")
        c = s(c, r"(?s)\s+", r" ")
        d = s(d, r"\s*", r" ")
        d = "; /*"+d+"*/"
        if a : a = "\n"+a
        out += a+b+c+d+"\n"
    return ""
T = s(T, r"(?sx) (/\*\*\s(?:.(?!\*\/))*.\*\/)"
      r"         (\s*(?:\w+[*]*\s+|[*]\s+)+) "
      r"          \b (\w+\s*\([^();{}=]*\)) ([^;{}=]*[;{}=]) ",
      lambda x : q3_(x.group(1), x.group(2), x.group(3), x.group(4)))

out += "\n#ifdef __cplusplus\n} /* extern \"C\" */\n#endif\n\n"
out += "\n#endif\n"
try:
    F = open (outputfile, "w")
except IOError, x:
    print "could open output file:", str(x)
    sys.exit()
else:
    F.write(out)
    F.close()

count = 0
def counting(): global count ; count += 1 ; return ""
s(out, r"extern", lambda x : counting() )
print " " * (4 - len("%i"%count)),count," extern       ", inc

