/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "places.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

readplaces_ret *
readplace_1(Place *argp, CLIENT *clnt)
{
	static readplaces_ret clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, READPLACE,
		(xdrproc_t) xdr_Place, (caddr_t) argp,
		(xdrproc_t) xdr_readplaces_ret, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

readplaces_ret *
readairport_1(Place *argp, CLIENT *clnt)
{
	static readplaces_ret clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, READAIRPORT,
		(xdrproc_t) xdr_Place, (caddr_t) argp,
		(xdrproc_t) xdr_readplaces_ret, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
