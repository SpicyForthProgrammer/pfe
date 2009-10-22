#ifndef PFE_EXCEPTION_EXT_H
#define PFE_EXCEPTION_EXT_H 1256212372
/* generated 2009-1022-1352 make-header.py ../../c/exception-ext.c */

#include <pfe/pfe-ext.h>

/**
 * --    The Optional Exception Word Set
 *
 *  Copyright (C) Tektronix, Inc. 1998 - 2001.
 *  Copyright (C) 2005 - 2008 Guido U. Draheim <guidod@gmx.de>
 *
 *  @see     GNU LGPL
 *  @author  Guido U. Draheim            (modified by $Author: guidod $)
 *  @version $Revision: 1.8 $
 *     (modified $Date: 2008-09-11 01:27:20 $)
 *
 *  @description
 *      These words implement an exception system in the
 *      widely known => THROW &amp; => CATCH concept.
 *
 *      see the PFE-SIG wordset for catching OS traps.
 */

#ifdef __cplusplus
extern "C" {
#endif




/** CATCH ( catch-xt* -- 0 | throw#! ) [ANS]
 * execute the given execution-token and catch
 * any exception that can be caught therein.
 * software can arbitrarily raise an exception
 * using => THROW - the value 0 means there
 * was no exception, other denote implementation
 * dependent exception-codes.
 */
extern void FXCode (p4_catch);

/** THROW ( throw#! -- [THROW] | throw# -- ) [ANS]
 * raise an exception - it will adjust the depth
 * of all stacks and start interpreting at the point
 * of the latest => CATCH <br>
 * if n is null nothing happens, the -1 (ie. => FALSE )
 * is the raise-code of => ABORT - the other codes
 * are implementation dependent and will result in
 * something quite like => ABORT
 */
extern void FXCode (p4_throw);

/** ABORT ( -- [THROW] ) [ANS]
 * throw - cleanup some things and go back to the QUIT routine
 : ABORT -1 THROW ;
 */
extern void FXCode (p4_abort);

/** ((ABORT")) ( -- ) [HIDDEN]
 * compiled by => ABORT" what"
 */
extern void FXCode_XE (p4_abort_quote_execution);

/** 'ABORT"' ( [string<">] -- [THROW] ) [ANS]
 * throw like => ABORT but print an additional error-message
 * to stdout telling what has happened.
 */
extern void FXCode (p4_abort_quote);

extern void FXCode_RT (p4_exception_string_RT);

/** (EXCEPTION-STRING: ( exception# [description<closeparen>] -- )
 * append a node with the given id and a pointer to an
 * extern zstring to the => NEXT-EXCEPTION chain-list.
 */
extern void FXCode (p4_exception_string);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif
