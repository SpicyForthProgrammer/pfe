#ifndef PFE_BLOCK_MIX_H
#define PFE_BLOCK_MIX_H 20091024
/* generated by make-header.py from ../../c/block-mix.c */

#include <pfe/pfe-mix.h>

/**
 * -- miscellaneous useful extra words for BLOCK-EXT
 *
 *  Copyright (C) Tektronix, Inc. 1998 - 2001.
 *  Copyright (C) 2005 - 2008 Guido U. Draheim <guidod@gmx.de>
 *
 *  @see     GNU LGPL
 *  @author  Guido U. Draheim            (modified by $Author: guidod $)
 *  @version $Revision: 514 $
 *     (modified $Date: 2009-10-22 16:18:28 +0200 (Do, 22. Okt 2009) $)
 *
 *  @description
 *      Compatiblity with former standards, miscellaneous useful words.
 *      ... for BLOCK-EXT
 */

#ifdef __cplusplus
extern "C" {
#endif




/** CLOSE-BLOCKFILE ( -- ) [FTH] w32for
 * w32for-implementation:
 blockhandle -1 <> if flush close-file drop then
 -1 set-blockfile
 * in pfe:
 : CLOSE-BLOCKFILE
   BLOCK-FILE ?DUP IF FLUSH CLOSE-FILE DROP THEN
   OFF> BLOCK-FILE ;
 */
extern void FXCode (p4_close_blockfile);

/** OPEN-BLOCKFILE ( "filename" -- ) [FTH] w32for
 * w32for-implementation:
   close-blockfile
   parse-word r/w open-file abort" failed to open block-file"
   set-blockfile
   empty-buffers
 */
extern void FXCode (p4_open_blockfile);

/** CREATE-BLOCKFILE ( blocks-count "filename" -- ) [FTH] w32for
 * w32for-implementation:
   close-blockfile
   parse-word r/w create-file abort" failed to create block-file"
   set-blockfile
   dup b/buf m* blockhandle resize-file
   abort" unable to create a file of that size"
   empty-buffers
   0 do i wipe loop
   flush
 * pfe does not wipe the buffers
 */
extern void FXCode (p4_create_blockfile);

/** SET-BLOCKFILE ( block-file* -- ) [EXT] win32for
 * win32forth uses a system-filedescriptor where -1 means unused
 * in the BLOCKHANDLE, but we use a "FILE*"-like structure, so NULL
 * means NOT-IN-USE. Here we set it.
 */
extern void FXCode(p4_set_blockfile);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif
