struct berval*
slapi_ch_bvdup (const struct berval* v)
{
    struct berval* newberval = ber_bvdup ((struct berval *)v);
    if (newberval == NULL) {
		int	oserr = errno;

	  	oom_occurred();
		slapi_log_error( SLAPI_LOG_FATAL, SLAPD_MODULE,
		    "ber_bvdup of %lu bytes failed; OS error %d (%s)%s\n",
			(unsigned long)v->bv_len, oserr, slapd_system_strerror( oserr ),
			oom_advice );
		exit( 1 );
    }
    return newberval;
}