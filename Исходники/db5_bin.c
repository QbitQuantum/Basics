/**
 * R T _ B I N U N I F _ I M P O R T 5
 *
 * Import a uniform-array binary object from the database format to
 * the internal structure.
 */
int
rt_binunif_import5( struct rt_db_internal	*ip,
		    const struct bu_external	*ep,
		    const mat_t			mat,
		    const struct db_i		*dbip,
		    struct resource		*resp,
		    const int			minor_type)
{
    struct rt_binunif_internal	*bip;
    int				i;
    unsigned char			*srcp;
    unsigned long			*ldestp;
    int				in_cookie, out_cookie;
    int				gotten;

    BU_CK_EXTERNAL( ep );

    /*
     * There's no particular size to expect
     *
     * BU_ASSERT_LONG( ep->ext_nbytes, ==, SIZEOF_NETWORK_DOUBLE * 3*4 );
     */

    RT_CK_DB_INTERNAL( ip );
    ip->idb_major_type = DB5_MAJORTYPE_BINARY_UNIF;
    ip->idb_minor_type = minor_type;
    ip->idb_meth = &rt_functab[ID_BINUNIF];
    ip->idb_ptr = bu_malloc( sizeof(struct rt_binunif_internal),
			     "rt_binunif_internal");

    bip = (struct rt_binunif_internal *)ip->idb_ptr;
    bip->magic = RT_BINUNIF_INTERNAL_MAGIC;
    bip->type = minor_type;

    /*
     * Convert from database (network) to internal (host) format
     */
    switch (bip->type) {
	case DB5_MINORTYPE_BINU_FLOAT:
	    bip->count = ep->ext_nbytes/SIZEOF_NETWORK_FLOAT;
	    bip->u.uint8 = (unsigned char *) bu_malloc( bip->count * sizeof(float),
							"rt_binunif_internal" );
	    ntohf( (unsigned char *) bip->u.uint8,
		   ep->ext_buf, bip->count );
	    break;
	case DB5_MINORTYPE_BINU_DOUBLE:
	    bip->count = ep->ext_nbytes/SIZEOF_NETWORK_DOUBLE;
	    bip->u.uint8 = (unsigned char *) bu_malloc( bip->count * sizeof(double),
							"rt_binunif_internal" );
	    ntohd( (unsigned char *) bip->u.uint8,
		   ep->ext_buf, bip->count );
	    break;
	case DB5_MINORTYPE_BINU_8BITINT:
	case DB5_MINORTYPE_BINU_8BITINT_U:
	    bip->count = ep->ext_nbytes;
	    bip->u.uint8 = (unsigned char *) bu_malloc( ep->ext_nbytes,
							"rt_binunif_internal" );
	    memcpy((char *) bip->u.uint8, (char *) ep->ext_buf, ep->ext_nbytes);
	    break;
	case DB5_MINORTYPE_BINU_16BITINT:
	case DB5_MINORTYPE_BINU_16BITINT_U:
	    bip->count = ep->ext_nbytes/2;
	    bip->u.uint8 = (unsigned char *) bu_malloc( ep->ext_nbytes,
							"rt_binunif_internal" );
#if 0
	    srcp = (unsigned char *) ep->ext_buf;
	    sdestp = (unsigned short *) bip->u.uint8;
	    for (i = 0; i < bip->count; ++i, ++sdestp, srcp += 2) {
		*sdestp = bu_gshort( srcp );
		bu_log("Just got %d", *sdestp);
	    }
#endif
	    in_cookie = bu_cv_cookie("nus");
	    out_cookie = bu_cv_cookie("hus");
	    if (bu_cv_optimize(in_cookie) != bu_cv_optimize(out_cookie)) {
		gotten =
		    bu_cv_w_cookie((genptr_t)bip->u.uint8, out_cookie,
				   ep->ext_nbytes,
				   ep->ext_buf, in_cookie, bip->count);
		if (gotten != bip->count) {
		    bu_log("%s:%d: Tried to convert %d, did %d",
			   __FILE__, __LINE__, bip->count, gotten);
		    bu_bomb("\n");
		}
	    } else
		memcpy((char *) bip->u.uint8,
		       (char *) ep->ext_buf,
		       ep->ext_nbytes );
	    break;
	case DB5_MINORTYPE_BINU_32BITINT:
	case DB5_MINORTYPE_BINU_32BITINT_U:
	    bip->count = ep->ext_nbytes/4;
	    bip->u.uint8 = (unsigned char *) bu_malloc( ep->ext_nbytes,
							"rt_binunif_internal" );
	    srcp = (unsigned char *) ep->ext_buf;
	    ldestp = (unsigned long *) bip->u.uint8;
	    for (i = 0; i < bip->count; ++i, ++ldestp, srcp += 4) {
		*ldestp = bu_glong( srcp );
	    }
	    break;
	case DB5_MINORTYPE_BINU_64BITINT:
	case DB5_MINORTYPE_BINU_64BITINT_U:
	    bu_log("rt_binunif_import5() Can't handle 64-bit integers yet\n");
	    return -1;
    }

    return 0;		/* OK */
}