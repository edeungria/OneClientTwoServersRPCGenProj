/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "places.h"

bool_t
xdr_placetype (XDR *xdrs, placetype objp)
{
	register int32_t *buf;

	 if (!xdr_vector (xdrs, (char *)objp, PNAMELEN,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_airporttype (XDR *xdrs, airporttype objp)
{
	register int32_t *buf;

	 if (!xdr_vector (xdrs, (char *)objp, ANAMELEN,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_statetype (XDR *xdrs, statetype objp)
{
	register int32_t *buf;

	 if (!xdr_vector (xdrs, (char *)objp, STATELEN,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_codetype (XDR *xdrs, codetype objp)
{
	register int32_t *buf;

	 if (!xdr_vector (xdrs, (char *)objp, CODELEN,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_airportlist (XDR *xdrs, airportlist *objp)
{
	register int32_t *buf;

	 if (!xdr_pointer (xdrs, (char **)objp, sizeof (struct Airport), (xdrproc_t) xdr_Airport))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Airport (XDR *xdrs, Airport *objp)
{
	register int32_t *buf;

	 if (!xdr_codetype (xdrs, objp->code))
		 return FALSE;
	 if (!xdr_airporttype (xdrs, objp->name))
		 return FALSE;
	 if (!xdr_statetype (xdrs, objp->state))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->latitude))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->longitude))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->distance))
		 return FALSE;
	 if (!xdr_airportlist (xdrs, &objp->next))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_readplaces_ret (XDR *xdrs, readplaces_ret *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->err))
		 return FALSE;
	switch (objp->err) {
	case 0:
		 if (!xdr_airportlist (xdrs, &objp->readplaces_ret_u.list))
			 return FALSE;
		break;
	case 1:
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

bool_t
xdr_Place (XDR *xdrs, Place *objp)
{
	register int32_t *buf;

	 if (!xdr_placetype (xdrs, objp->name))
		 return FALSE;
	 if (!xdr_statetype (xdrs, objp->state))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->latitude))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->longitude))
		 return FALSE;
	return TRUE;
}
