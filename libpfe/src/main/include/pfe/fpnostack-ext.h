#ifndef PFE_FPNOSTACK_EXT_H
#define PFE_FPNOSTACK_EXT_H 1256212372
/* generated 2009-1022-1352 make-header.py ../../c/fpnostack-ext.c */

#include <pfe/pfe-ext.h>

/**
 *  -- The No-FP-Stack Floating-Point Word Set
 *
 *  Copyright (C) Krishna Myneni and Guido Draheim, 2002
 *  Copyright (C) 2005 - 2008 Guido U. Draheim <guidod@gmx.de>
 *
 *  @see     GNU LGPL
 *  @author  Krishna Myneni              (modified by $Author: guidod $)
 *  @version $Revision: 1.6 $
 *     (modified $Date: 2008-09-10 19:18:13 $)
 *
 *  @description
 *         The No-FP-Stack Floating-Point Wordset is not usually
 *         used on embedded platforms. This Module implements
 *         the floating-point words but expects and puts the
 *         floating-point values on the forth parameter-stack.
 */

#ifdef __cplusplus
extern "C" {
#endif




extern void FXCode (p4_nofp_d_f_align);

extern void FXCode (p4_nofp_to_float);

extern else

void FXCode (p4_nofp_to_float);

extern endif

void FXCode (p4_nofp_d_to_f);

extern void FXCode (p4_nofp_f_store);

extern void FXCode (p4_nofp_f_star);

extern void FXCode (p4_nofp_f_plus);

extern void FXCode (p4_nofp_f_minus);

extern void FXCode (p4_nofp_f_slash);

extern void FXCode (p4_nofp_f_zero_less);

extern void FXCode (p4_nofp_f_zero_equal);

extern void FXCode (p4_nofp_f_equal);

extern void FXCode (p4_nofp_f_not_equal);

extern void FXCode (p4_nofp_f_less_than);

extern void FXCode (p4_nofp_f_greater_than);

extern void FXCode (p4_nofp_f_less_than_or_equal);

extern void FXCode (p4_nofp_f_greater_than_or_equal);

extern void FXCode (p4_nofp_f_to_d);

/** S>F  ( n -- x )
 */
extern void FXCode (p4_nofp_s_to_f);

/** FTRUNC>S  ( x -- n )
 */
extern void FXCode (p4_nofp_f_trunc_to_s);

/** FROUND>S ( x -- n )
 */
extern void FXCode (p4_nofp_f_round_to_s);

/** FTRUNC ( x -- x' )
 */
extern void FXCode (p4_nofp_f_trunc);

/** -FROT  ( x1 x2 x3 -- x3 x1 x2 )
 */
extern void FXCode (p4_nofp_minus_f_rot);

/** FNIP  ( x1 x2 -- x2 )
 */
extern void FXCode (p4_nofp_f_nip);

/** FTUCK  ( x1 x2 -- x2 x1 x2 )
 */
extern void FXCode (p4_nofp_f_tuck);

/** 1/F  ( x -- 1/x )
 */
extern void FXCode (p4_nofp_one_over_f);

/** F^2  ( x -- x^2 )
 */
extern void FXCode (p4_nofp_f_square);

/** F^N  ( x u -- x^u )
 * For large exponents, use F** instead.  Of course u=-1 is large.
 */
extern void FXCode (p4_nofp_f_power_n);

/** F2/  ( x -- x/2 )
 */
extern void FXCode (p4_nofp_f_two_slash);

/** F2*  ( x -- x*2 )
 */
extern void FXCode (p4_nofp_f_two_star);

/** F0>  ( x -- flag )
*/
extern void FXCode (p4_nofp_f_zero_greater);

/** F0<>  ( x -- flag )
*/
extern void FXCode (p4_nofp_f_zero_not_equal);

extern void FXCode (p4_nofp_f_fetch);

extern void FXCode_RT (p4_nofp_f_constant_RT);

extern void FXCode (p4_nofp_f_constant);

extern void FXCode (p4_nofp_f_depth);

extern void FXCode (p4_nofp_f_drop);

extern void FXCode (p4_nofp_f_dup);

extern void FXCode_XE (p4_nofp_f_literal_execution);

extern void FXCode (p4_nofp_f_literal);

extern void FXCode (p4_nofp_floor);

extern void FXCode (p4_nofp_f_max);

extern void FXCode (p4_nofp_f_min);

extern void FXCode (p4_nofp_f_negate);

extern void FXCode (p4_nofp_f_over);

extern void FXCode (p4_nofp_f_rot);

extern endif

void FXCode (p4_nofp_f_round);

extern void FXCode (p4_nofp_f_swap);

extern void FXCode_RT (p4_nofp_f_variable_RT);

extern void FXCode (p4_nofp_f_variable);

extern void FXCode (p4_nofp_represent);

extern void FXCode (p4_nofp_d_f_align);

extern void FXCode (p4_nofp_d_f_aligned);

extern void FXCode (p4_nofp_d_float_plus);

extern void FXCode (p4_nofp_d_floats);

extern void FXCode (p4_nofp_f_star_star);

extern void FXCode (p4_nofp_f_dot);

extern void FXCode (p4_nofp_f_abs);

extern void FXCode (p4_nofp_f_e_dot);

extern void FXCode (p4_nofp_f_s_dot);

extern void FXCode (p4_nofp_f_proximate);

extern void FXCode (p4_nofp_set_precision);

extern void FXCode (p4_nofp_s_f_store);

extern void FXCode (p4_nofp_s_f_fetch);

extern void FXCode (p4_nofp_s_float_plus);

extern void FXCode (p4_nofp_s_floats);

extern void FXCode (p4_nofp_f_acos);

extern void FXCode (p4_nofp_f_acosh);

extern void FXCode (p4_nofp_f_alog);

extern void FXCode (p4_nofp_f_asin);

extern void FXCode (p4_nofp_f_asinh);

extern void FXCode (p4_nofp_f_atan);

extern void FXCode (p4_nofp_f_atan2);

extern void FXCode (p4_nofp_f_atanh);

extern void FXCode (p4_nofp_f_cos);

extern void FXCode (p4_nofp_f_cosh);

extern void FXCode (p4_nofp_f_exp);

extern void FXCode (p4_nofp_f_expm1);

extern void FXCode (p4_nofp_f_expm1);

extern endif
void FXCode (p4_nofp_f_ln);

extern void FXCode (p4_nofp_f_lnp1);

extern void FXCode (p4_nofp_f_lnp1);

extern endif
void FXCode (p4_nofp_f_log);

extern void FXCode (p4_nofp_f_sin);

extern void FXCode (p4_nofp_f_sincos);

extern void FXCode (p4_nofp_f_sinh);

extern void FXCode (p4_nofp_f_sqrt);

extern void FXCode (p4_nofp_f_tan);

extern void FXCode (p4_nofp_f_tanh);

/**
 * return double float-aligned address
 */
_extern  p4cell p4_nofp_dfaligned (p4cell n) ; /*{*/

/**
 *  used in engine
 */
_extern  int p4_nofp_to_float (const p4_char_t *p, p4cell n, double *r) ; /*{*/

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif
