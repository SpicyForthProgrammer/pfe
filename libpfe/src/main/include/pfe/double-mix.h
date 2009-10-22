#ifndef PFE_DOUBLE_MIX_H
#define PFE_DOUBLE_MIX_H 1256214392
/* generated 2009-1022-1426 make-header.py ../../c/double-mix.c */

#include <pfe/pfe-mix.h>

/**
 * -- miscellaneous useful extra words for DOUBLE-EXT
 *
 *  Copyright (C) Tektronix, Inc. 1998 - 2001.
 *  Copyright (C) 2005 - 2008 Guido U. Draheim <guidod@gmx.de>
 *
 *  @see     GNU LGPL
 *  @author  Guido U. Draheim            (modified by $Author: guidod $)
 *  @version $Revision: 1.3 $
 *     (modified $Date: 2008-04-20 04:46:30 $)
 *
 *  @description
 *      Compatiblity with former standards, miscellaneous useful words.
 *      ... for DOUBLE-EXT  (which is almost complete... just almost)
 */

#ifdef __cplusplus
extern "C" {
#endif




/** 2ROT ( d1,d1 d2,d2 d3,d3 -- d2,d2 d3,d3 d1,d1 )
 * the double-cell => ROT operation.
 * actively moves six cells, i.e.
   ( x1 x2 x3 x4 x5 x6 -- x3 x4 x5 x6 x1 x2 )
 */
extern void FXCode (p4_two_rot);

/** DU< ( d1,d1 d2,d2 -- flag )
 * the double-cell unsigned-is-less operation ( =>"U<" )
 */
extern void FXCode (p4_d_u_less);

/** LITERAL, ( value -- )
 * take the value from stack (or cs-stack) and compile a runtime-code and
 * the value as for => LITERAL ... this word is never state-smart, it
 * is not immediate, and has therefore no complications with => POSTPONE
 * (compare also with =>"COMPILE," to make a call-stub with an exectoken)
 */
extern void FXCode (p4_literal_comma);

/** 2LITERAL, ( x1,x2 -- )
 * take the double-value from stack (or cs-stack) and compile a runtime-code
 * and the value as for => 2LITERAL ... this word is never state-smart, it
 * is not immediate, and has therefore no complications with => POSTPONE
 * (compare also with =>"COMPILE," to make a call-stub with an exectoken)
 */
extern void FXCode (p4_two_literal_comma);

/** DCELLS ( x -- x' )
 * computes the number of address units for the specified number
 * of double-cells
 : DCELLS CELLS 2* ;
 */
extern void FXCode (p4_dcells);

/** DLSHIFT ( x1,x2 y -- z1,z2 )
 * shift-left a double-cell value.
 * The shift-count is given as a single-cell.
 */
extern void FXCode (p4_d_shiftleft);

/** DRSHIFT ( x1,x2 y -- z1,z2 )
 * shift-right a double-cell value.
 * The shift-count is given as a single-cell.
 * This is an arithmetic shift as for a signed double-cell value.
 */
extern void FXCode (p4_d_shiftright);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif
