#ifndef PFE_BLOCK_SUB_H
#define PFE_BLOCK_SUB_H 20091024
/* generated by make-header.py from ../../c/block-sub.c */

#include <pfe/pfe-sub.h>

/**
 * --  Block-oriented Subroutines
 *
 *  Copyright (C) Tektronix, Inc. 1998 - 2001.
 *  Copyright (C) 2005 - 2008 Guido U. Draheim <guidod@gmx.de>
 *
 *  @see     GNU LGPL
 *  @author  Guido U. Draheim            (modified by $Author: guidod $)
 *  @version $Revision: 527 $
 *     (modified $Date: 2009-10-24 11:01:52 +0200 (Sa, 24 Okt 2009) $)
 */

#ifdef __cplusplus
extern "C" {
#endif




/**
 * Return best possible access method,
 * 0 if no access but file exists, -1 if file doesn't exist.
 */
extern int p4_file_access (const p4_char_t *fn, int len); /*{*/

/**
 * open file
 */
extern p4_File * p4_open_file (const p4_char_t *name, int len, int mode); /*{*/

/**
 * create file
 */
extern p4_File * p4_create_file (const p4_char_t *name, int len, int mode); /*{*/

/**
 * close file
 */
extern int p4_close_file (p4_File *fid); /*{*/

/**
 * seek file
 */
extern int p4_reposition_file (p4_File *fid, _p4_off_t pos); /*{*/

/**
 * read file
 */
extern int p4_read_file (void *p, p4ucell *n, p4_File *fid); /*{*/

/**
 * write file
 */
extern int p4_write_file (void *p, p4ucell n, p4_File *fid); /*{*/

/**
 * resize file
 */
extern int p4_resize_file (p4_File *fid, _p4_off_t size); /*{*/

/**
 * read line
 */
extern int p4_read_line (void* buf, p4ucell *u, p4_File *fid, p4cell *ior); /*{*/

/**
 * source input: read from block-file
 */
extern p4_File * p4_open_blockfile (const p4_char_t *name, int len); /*{*/

/**
 * set fid as current block-file, possibly close the old one.
 * (does nothing if argument is null, returns the argument)
 */
extern p4_File* p4_set_blockfile (p4_File* fid); /*{*/

/**
 * very traditional block read/write primitive
 */
extern void p4_blockfile_read_write (p4_File *fid, void *p, p4ucell n, int readflag); /*{*/

/**
 * traditional BUFFER impl
 */
extern void* p4_blockfile_buffer (p4_File *fid, p4_blk_t blk, int *reload); /*{*/

/**
 * traditional BLOCK impl
 */
extern void* p4_blockfile_block (p4_File *fid, p4_blk_t blk); /*{*/

/**
 * EMPTY-BUFFERS
 */
extern void p4_blockfile_empty_buffers (p4_File *fid); /*{*/

/**
 * SAVE-BUFFERS
 */
extern void p4_blockfile_save_buffers (p4_File *fid); /*{*/

/**
 * UPDATE
 */
extern void p4_blockfile_update (p4_File *fid); /*{*/

/**
 * LIST
 */
extern void p4_blockfile_list (p4_File *fid, int n); /*{*/

/**
 * => INTERPET file
 */
extern void p4_blockfile_load (p4_File *fid, p4_blk_t blk); /*{*/

/**
 * => THRU
 */
extern void p4_blockfile_thru (p4_File *fid, p4_blk_t lo, p4_blk_t hi); /*{*/

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif
