#ifndef _PFE_VERSION_SUB_H
#define _PFE_VERSION_SUB_H 1158897469
/* generated 2006-0922-0557 ../../pfe/../mk/Make-H.pl ../../pfe/version-sub.c */

#include <pfe/pfe-sub.h>

/** 
 * -- Version File
 *
 *  Copyright (C) Tektronix, Inc. 1998 - 2003.
 *  Copyright (C) 2005 - 2006 Guido U. Draheim <guidod@gmx.de>
 *
 *  @see     GNU LGPL
 *  @author  Guido U. Draheim            (modified by $Author: guidod $)
 *  @version $Revision: 1.3 $
 *     (modified $Date: 2006-09-22 04:43:03 $)
 *
 *  @description
 *      there are some internal functions in the version-file 
 *      that are used to print out compile-time, -date, -version 
 *      and the license of course.
 */

#ifdef __cplusplus
extern "C" {
#endif




_extern  P4_GCC_CONST const char* p4_version_string(void) ; /*{*/

_extern  P4_GCC_CONST const char* p4_copyright_string(void) ; /*{*/

_extern  P4_GCC_CONST const char* p4_license_string (void) ; /*{*/

_extern  P4_GCC_CONST const char* p4_warranty_string (void) ; /*{*/

_extern  P4_GCC_CONST const char* p4_compile_date (void) ; /*{*/

_extern  P4_GCC_CONST const char* p4_compile_time (void) ; /*{*/

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif
