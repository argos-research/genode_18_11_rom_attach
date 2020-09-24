/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _RWALL_H_RPCGEN
#define _RWALL_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user or with the express written consent of
 * Sun Microsystems, Inc.
 *
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 *
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 *
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 *
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 *
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 */
/*
 * Copyright (c) 1984, 1990 by Sun Microsystems, Inc.
 */

/* from @(#)rwall.x	1.6 91/03/11 TIRPC 1.0 */

#ifndef _rpcsvc_rwall_h
#define _rpcsvc_rwall_h

typedef char *wrapstring;


#endif /* ! _rpcsvc_rwall_h */

#define WALLPROG 100008
#define WALLVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define WALLPROC_WALL 2
extern  void * wallproc_wall_1(wrapstring *, CLIENT *);
extern  void * wallproc_wall_1_svc(wrapstring *, struct svc_req *);
extern int wallprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define WALLPROC_WALL 2
extern  void * wallproc_wall_1();
extern  void * wallproc_wall_1_svc();
extern int wallprog_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_RWALL_H_RPCGEN */