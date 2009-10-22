#ifndef PFE_SHELL_OS_EXT_H
#define PFE_SHELL_OS_EXT_H 1256212373
/* generated 2009-1022-1352 make-header.py ../../c/shell-os-ext.c */

#include <pfe/pfe-ext.h>

/**
 * -- os-like / shell-like commands for pfe
 *
 *  Copyright (C) Tektronix, Inc. 1998 - 2001.
 *  Copyright (C) 2005 - 2008 Guido U. Draheim <guidod@gmx.de>
 *
 *  @see     GNU LGPL
 *  @author  Guido U. Draheim            (modified by $Author: guidod $)
 *  @version $Revision: 1.4 $
 *     (modified $Date: 2008-05-02 03:03:35 $)
 *
 *  @description
 *        These builtin words are modelled after common shell commands,
 *        so that the Portable Forth Environment can often
 *        be put in the place of a normal OS shell.
 */

#ifdef __cplusplus
extern "C" {
#endif




/** $PID ( -- pid )
 * calls system's <c> getpid </c>
 */
extern void FXCode (p4_getpid);

/** $UID ( -- val )
 * calls system's <c> getuid </c>
 */
extern void FXCode (p4_getuid);

/** $EUID ( -- val )
 * calls system's <c> geteuid </c>
 */
extern void FXCode (p4_geteuid);

/** $GID ( -- val )
 * calls system's <c> getgid </c>
 */
extern void FXCode (p4_getgid);

/** UMASK ( val -- ret )
 * calls system's <c> umask </c>
 */
extern void FXCode (p4_umask);

/** $HOME ( -- str-ptr str-len )
 * calls system's <c> getenv(HOME) </c>
 */
extern void FXCode (p4_home);

/** $USER ( -- str-ptr str-len )
 * calls system's <c> getenv(USER) </c>
 */
extern void FXCode (p4_user);

/** $CWD ( -- str-ptr str-len )
 * calls system's <c> getcwd </c>
 */
extern void FXCode (p4_cwd);

/** PWD ( -- )
 * calls system's <c> getcwd </c> and prints it to the screen
 : PWD  $CWD TYPE ;
 */
extern void FXCode (p4_pwd);

/** CHDIR ( bstring -- )
 * change the current directory. <br>
 */
extern void FXCode (p4_chdir);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif
