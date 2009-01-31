/*
 * Copyright 2003 Sun Microsystems, Inc.  All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Sun designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Sun in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
 * CA 95054 USA or visit www.sun.com if you need additional information or
 * have any questions.
 */
  

#ifndef __MLIB_IMAGECLIPPING_H
#define __MLIB_IMAGECLIPPING_H

#ifdef __SUNPRO_C
#pragma ident	"@(#)mlib_ImageClipping.h	1.1	02/04/19 SMI"
#endif /* __SUNPRO_C */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

mlib_status mlib_ImageClippingMxN(mlib_image *dst_i,
                                  mlib_image *src_i,
                                  mlib_image *dst_e,
                                  mlib_image *src_e,
                                  mlib_s32 *edg_sizes,
                                  const mlib_image *dst,
                                  const mlib_image *src,
                                  mlib_s32 kw,
                                  mlib_s32 kh,
                                  mlib_s32 kw1,
                                  mlib_s32 kh1);

mlib_status mlib_ImageClipping(mlib_image *dst_i,
                               mlib_image *src_i,
                               mlib_image *dst_e,
                               mlib_image *src_e,
                               mlib_s32 *edg_sizes,
                               const mlib_image *dst,
                               const mlib_image *src,
                               mlib_s32 ker_size);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MLIB_IMAGECLIPPING_H */
