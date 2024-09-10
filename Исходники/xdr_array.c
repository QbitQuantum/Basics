/*
 * XDR an array of arbitrary elements
 * *addrp is a pointer to the array, *sizep is the number of elements.
 * If addrp is NULL (*sizep * elsize) bytes are allocated.
 * elsize is the size (in bytes) of each element, and elproc is the
 * xdr procedure to call to handle each element of the array.
 */
bool_t
xdr_array (XDR *xdrs, caddr_t *addrp, u_int *sizep, u_int maxsize, u_int elsize, xdrproc_t elproc)
{
  u_int i;
  caddr_t target = *addrp;
  u_int c;		/* the actual element count */
  bool_t stat = TRUE;
  u_int nodesize;

  /* like strings, arrays are really counted arrays */
  if (!xdr_u_int (xdrs, sizep))
    {
      return FALSE;
    }
  c = *sizep;
  /*
   * XXX: Let the overflow possibly happen with XDR_FREE because mem_free()
   * doesn't actually use its second argument anyway.
   */
  if ((c > maxsize || c > UINT_MAX / elsize) && (xdrs->x_op != XDR_FREE))
    {
      return FALSE;
    }
  nodesize = c * elsize;

  /*
   * if we are deserializing, we may need to allocate an array.
   * We also save time by checking for a null array if we are freeing.
   */
  if (target == NULL)
    switch (xdrs->x_op)
      {
      case XDR_DECODE:
	if (c == 0)
	  return TRUE;
	*addrp = target = mem_alloc (nodesize);
	if (target == NULL)
	  {
#ifdef USE_IN_LIBIO
	    if (_IO_fwide (stderr, 0) > 0)
	      (void) fwprintf (stderr, L"%s",
				 _("xdr_array: out of memory\n"));
	    else
#endif
	      (void) fputs (_("xdr_array: out of memory\n"), stderr);
	    return FALSE;
	  }
	memset (target, 0, nodesize);
	break;

      case XDR_FREE:
	return TRUE;
      default:
	break;
      }

  /*
   * now we xdr each element of array
   */
  for (i = 0; (i < c) && stat; i++)
    {
      stat = (*elproc) (xdrs, target, LASTUNSIGNED);
      target += elsize;
    }

  /*
   * the array may need freeing
   */
  if (xdrs->x_op == XDR_FREE)
    {
      mem_free (*addrp, nodesize);
      *addrp = NULL;
    }
  return stat;
}