#ifndef _PFE_HEADER_SUB_H
#define _PFE_HEADER_SUB_H 1105051253
/* generated 2005-0106-2340 ../../../pfe/../mk/Make-H.pl ../../../pfe/header-sub.c */

#include <pfe/pfe-sub.h>

/** 
 *  Implements header creation and navigation.
 *
 *  Copyright (C) Tektronix, Inc. 1998 - 2001. All rights reserved.
 *
 *  @see     GNU LGPL
 *  @author  Tektronix CTE              @(#) %derived_by: guidod %
 *  @version %version:  33.33 %
 *    (%date_modified:  Wed Mar 19 18:05:40 2003 %)
 */

#ifdef __cplusplus
extern "C" {
#endif


/* you must differentiate between VAR-style body and DOES-style body */
# define P4_TO_LINK(C)     ((p4char**)(C) -1 )
# define P4_LINK_FROM(C)   ((p4xt)(C) + 1 )
# define P4_TO_BODY(C)     ((p4cell *)((p4xt)(C) + 1))
# define P4_BODY_FROM(P)   ((p4xt)((p4cell *)(P) - 1))
# define P4_TO_DOES_BODY(C)  ((p4cell *)((p4xt)(C) + 2))
# define P4_TO_DOES_CODE(C)  ((p4xcode **)((p4xt)(C) + 1))
# ifdef PFE_CALL_THREADING
extern const p4xcode* p4_to_code (p4xt xt);
# define P4_TO_CODE(C)     (p4_to_code((p4xt)C))
# else
# define P4_TO_CODE(C)     (C)
# endif


/**
 * (DICTVAR) forth-thread variable runtime, => VARIABLE like
 */
extern P4_CODE (p4_dictvar_RT);

/**
 * (DICTGET) forth-thread constget runtime, => VALUE like
 */
extern P4_CODE (p4_dictget_RT);

/**
 * make a new dictionary entry in the word list identified by wid 
 *                   (fixme: delete the externs in other code portions)
 */
_extern  p4_namebuf_t* p4_header_comma (const p4_namechar_t *name, int len, p4_Wordl *wid) ; /*{*/

_extern  p4_namebuf_t* p4_make_header (p4code cfa, char flags, const p4_namechar_t* name, int count, p4_Wordl* wid) ; /*{*/

_extern  p4_namebuf_t* p4_header (p4code cfa, char flags) ; /*{*/

_extern  p4_namebuf_t* p4_header_in (p4_Wordl* wid) ; /*{*/

_extern  p4cell * p4_to_body (p4xt xt) ; /*{*/

_extern  p4xt p4_body_from (p4cell* body) ; /*{*/

_extern  p4_namebuf_t** p4_name_to_link (const p4_namebuf_t* p) ; /*{*/

_extern  p4_namebuf_t * p4_link_to_name (p4_namebuf_t **l) ; /*{*/

_extern  p4_Semant * p4_to_semant (p4xt xt) ; /*{*/

_extern  p4_namebuf_t ** p4_to_link (p4xt xt) ; /*{*/

_extern  p4xt p4_name_from (const p4_namebuf_t *p) ; /*{*/

_extern  p4_namebuf_t * p4_to_name (p4xt c) ; /*{*/

_extern  void p4_dot_name (const p4_namebuf_t *nfa) ; /*{*/

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif