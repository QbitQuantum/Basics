/*
 * Internal useful routines
 */
static bool
flush_out(RECSTREAM *rstrm, bool eor)
{
	u_int32_t eormask = (eor == true) ? LAST_FRAG : 0;
	u_int32_t len =
	    (u_int32_t) (PtrToUlong(rstrm->out_finger) -
			 PtrToUlong(rstrm->frag_header) - sizeof(u_int32_t));

	*(rstrm->frag_header) = htonl(len | eormask);
	len =
	    (u_int32_t) (PtrToUlong(rstrm->out_finger) -
			 PtrToUlong(rstrm->out_base));
	if ((*(rstrm->writeit))
	    (rstrm->xdrs, rstrm->tcp_handle, rstrm->out_base,
	     (int)len) != (int)len)
		return (false);
	rstrm->frag_header = (u_int32_t *) (void *)rstrm->out_base;
	rstrm->out_finger = (char *)rstrm->out_base + sizeof(u_int32_t);
	return (true);
}