/**
 * -- Stackhelp for CHAINLIST words - executable WORDLISTs
 *
 *  Copyright (C) Tektronix, Inc. 1998 - 2001.
 *  Copyright (C) 2005 - 2008 Guido U. Draheim <guidod@gmx.de>
 *
 *  @see     GNU LGPL
 *  @author  Guido U. Draheim            (modified by $Author$)
 *  @version $Revision$
 *     (modified $Date$)
 *
 *  @description
 *         Allow executables list embedded in the pfe interpreter
 *         based on pure wordlists instead of defer link chains.
 */
/*@{*/
#if defined(__version_control__) && defined(__GNUC__)
static char* id __attribute__((unused)) =
"@(#) $Id$";
#endif

#define _P4_SOURCE 1
#include <pfe/pfe-base.h>

P4_LISTWORDSET (chainlist_check) [] =
{
    P4_STKi ("NEW-WORDLIST",            "<name> --"),
    P4_STKi (".WORDS",                  "wordlist* --"),
    P4_STKi ("REDO-ALL-WORDS",          "wordlist* --"),
    P4_STKi ("DO-ALL-WORDS",            "wordlist* --"),
    P4_STKi ("DO-ALL-WORDS-WHILE-LOOP", "wordlist* xt* --"),
    P4_STKi ("DO-ALL-WORDS-WHILE",      "wordlist* xt* --"),
    P4_STKi ("DO-SYNONYM",              "wordlist* <do-name> <orig-name> --"),
    P4_STKi ("DO-ALIAS",                "xt* on-wordlist* <do-name> --"),
    P4_STKi ("ALIAS-ATEXIT",            "xt* <name> --"),
    P4_STKi ("ALIAS",                   "xt* <name> --"),
    P4_STKi ("ATEXIT-WORDLIST",         "-- atexit-wordlist*"),
    P4_STKi ("PROMPT-WORDLIST",         "-- prompt-wordlist*"),
    P4_STKi ("ABORT-WORDLIST",          "-- abort-wordlist*"),
};
P4_COUNTWORDSET (chainlist_check, "Check-chainlists - executable wordlists");

/*@}*/