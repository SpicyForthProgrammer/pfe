#ifndef PFE_STRING_EXT_H
#define PFE_STRING_EXT_H 1256212374
/* generated 2009-1022-1352 make-header.py ../../c/string-ext.c */

#include <pfe/pfe-ext.h>

/**
 * -- The Optional String Word Set
 *
 *  Copyright (C) Tektronix, Inc. 1998 - 2001.
 *  Copyright (C) 2005 - 2008 Guido U. Draheim <guidod@gmx.de>
 *
 *  @see     GNU LGPL
 *  @author  Guido U. Draheim            (modified by $Author: guidod $)
 *  @version $Revision: 1.3 $
 *     (modified $Date: 2008-04-20 04:46:29 $)
 *
 *  @description
 *      The basic words for handling string buffers. There are
 *      much more buffer words used in most Forth implementations around
 *      but they can usually implemented as colon-word quite effectivly
 *      on the basis of the STRING wordset.
 */

#ifdef __cplusplus
extern "C" {
#endif




/** -TRAILING ( str-ptr str-len -- str-ptr str-len' )
 * check the given buffer if it contains whitespace at its end.
 * If so, shorten str-len to meet the last non-whitespace
 * character in the buffer.
 */
extern void FXCode (p4_dash_trailing);

/** /STRING ( str-ptr str-len n -- str-ptr' str-len' )
 * shorten the buffer from the beginning by n characters, i.e.
  str-ptr += n ;
  str-len -= n;
 */
extern void FXCode (p4_slash_string);

/** BLANK ( str-ptr str-len -- )
 * => FILL a given buffer with => BL blanks
 */
extern void FXCode (p4_blank);

/** CMOVE ( from-ptr to-ptr len# -- )
 *  memcpy an area from->to for len bytes, starting at
 *  the lower addresses, see => CMOVE>
 */
extern void FXCode (p4_cmove);

/** CMOVE> ( from-ptr to-ptr len# -- )
 *  memcpy an area from->to for len bytes, starting
 *  with the higher addresses, see => CMOVE
 */
extern void FXCode (p4_cmove_up);

/** COMPARE ( str1-ptr str1-len str2-ptr str2-len -- diff# )
 * compare both str-buffers, return 0 if they are equal,
 * -1 if lower or shorter, and 1 if greater or longer
 */
extern void FXCode (p4_compare);

/** SEARCH ( str1-ptr str1-len str2-ptr str2-len -- str1-ptr' str1-len' flag )
 * search the str-buffer1 for the text of str-buffer2,
 * if it is contained return TRUE and return buffer-values that
 * point to the contained string, otherwise return FALSE and
 * leave the original str-buffer1.
 */
extern void FXCode (p4_search);

/** SLITERAL ( C: str-ptr str-len -- S: str-ptr str-len )
 * this word does almost the same as => LITERAL - it takes
 * an => S" string as specified in the CS-STACK at compile
 * time and compiles into the current definition where it is
 * returned as if there were a direct string-literal. This
 * can be used to compute a string-literal at compile-time
 * and hardwire it.
 example:
   : ORIGINAL-HOME  [ $HOME COUNT ] SLITERAL ; ( -- str-ptr str-len )
 */
extern void FXCode (p4_sliteral);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif
