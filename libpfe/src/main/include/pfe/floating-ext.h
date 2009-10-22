#ifndef PFE_FLOATING_EXT_H
#define PFE_FLOATING_EXT_H 1256214393
/* generated 2009-1022-1426 make-header.py ../../c/floating-ext.c */

#include <pfe/pfe-ext.h>

/**
 *  -- The Optional Floating-Point Word Set
 *
 *  Copyright (C) Tektronix, Inc. 1998 - 2001.
 *  Copyright (C) 2005 - 2008 Guido U. Draheim <guidod@gmx.de>
 *
 *  @see     GNU LGPL
 *  @author  Guido U. Draheim            (modified by $Author: guidod $)
 *  @version $Revision: 1.13 $
 *     (modified $Date: 2008-09-11 01:27:20 $)
 *
 *  @description
 *         The Optional Floating-Point Wordset is not usually
 *         used on embedded platforms. The PFE can be configured
 *         to even not allocate the separate floating-point stack
 *         that most of the floating-point words refer to.
 */

#ifdef __cplusplus
extern "C" {
#endif




extern void FXCode (p4_d_f_align);

extern void FXCode (p4_to_float);

extern else

void FXCode (p4_to_float);

extern endif

void FXCode (p4_d_to_f);

extern void FXCode (p4_f_store);

extern void FXCode (p4_f_star);

extern void FXCode (p4_f_plus);

extern void FXCode (p4_f_minus);

extern void FXCode (p4_f_slash);

extern void FXCode (p4_f_zero_less);

extern void FXCode (p4_f_zero_equal);

extern void FXCode (p4_f_less_than);

/** ( f: a -- n,n )
 * b is the integer representation of a
 *
 * we use truncation towards zero.
 * compare with =>"F>S" and its => "FROUND>S" / => "FTRUNC>S"
 */
extern void FXCode (p4_f_to_d);

extern void FXCode (p4_f_fetch);

extern void FXCode_RT (p4_f_constant_RT);

extern void FXCode (p4_f_constant);

extern void FXCode (p4_f_depth);

extern void FXCode (p4_f_drop);

extern void FXCode (p4_f_dup);

extern void FXCode_XE (p4_f_literal_execution);

extern void FXCode (p4_f_literal);

extern void FXCode (p4_floor);

extern void FXCode (p4_f_max);

extern void FXCode (p4_f_min);

extern void FXCode (p4_f_negate);

extern void FXCode (p4_f_over);

extern void FXCode (p4_f_rot);

extern endif

void FXCode (p4_f_round);

extern void FXCode (p4_f_swap);

extern void FXCode_RT (p4_f_variable_RT);

extern void FXCode (p4_f_variable);

extern void FXCode (p4_represent);

extern void FXCode (p4_d_f_align);

extern void FXCode (p4_d_f_aligned);

extern void FXCode (p4_d_float_plus);

extern void FXCode (p4_d_floats);

extern void FXCode (p4_f_star_star);

extern void FXCode (p4_f_dot);

extern void FXCode (p4_f_abs);

extern void FXCode (p4_f_e_dot);

extern void FXCode (p4_f_s_dot);

extern void FXCode (p4_f_proximate);

extern void FXCode (p4_set_precision);

extern void FXCode (p4_s_f_store);

extern void FXCode (p4_s_f_fetch);

extern void FXCode (p4_s_float_plus);

extern void FXCode (p4_s_floats);

extern void FXCode (p4_f_acos);

extern void FXCode (p4_f_acosh);

extern void FXCode (p4_f_alog);

extern void FXCode (p4_f_asin);

extern void FXCode (p4_f_asinh);

extern void FXCode (p4_f_atan);

extern void FXCode (p4_f_atan2);

extern void FXCode (p4_f_atanh);

extern void FXCode (p4_f_cos);

extern void FXCode (p4_f_cosh);

extern void FXCode (p4_f_exp);

extern void FXCode (p4_f_expm1);

extern void FXCode (p4_f_expm1);

extern endif
void FXCode (p4_f_ln);

extern void FXCode (p4_f_lnp1);

extern void FXCode (p4_f_lnp1);

extern endif
void FXCode (p4_f_log);

extern void FXCode (p4_f_sin);

extern void FXCode (p4_f_sincos);

extern void FXCode (p4_f_sinh);

extern void FXCode (p4_f_sqrt);

extern void FXCode (p4_f_tan);

extern void FXCode (p4_f_tanh);

extern void FXCode (p4_interpret_float);

/**
 * return double float-aligned address
 */
_extern  p4cell p4_dfaligned (p4cell n) ; /*{*/

/**
 *  used in engine
 */
_extern  int p4_to_float (const p4_char_t *p, p4cell n, double *r) ; /*{*/

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif
