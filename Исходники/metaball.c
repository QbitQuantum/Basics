/**
 * R T _ M E T A B A L L _ I M P O R T 5
 *
 * Import an metaball/sphere from the database format to the internal
 * structure. Apply modeling transformations as well.
 */
int
rt_metaball_import5(struct rt_db_internal *ip, const struct bu_external *ep, register const fastf_t *mat, const struct db_i *dbip)
{
    struct wdb_metaballpt *mbpt;
    struct rt_metaball_internal *mb;
    int metaball_count = 0, i;

    /* must be double for import and export */
    double *buf;

    if (dbip) RT_CK_DBI(dbip);

    BU_CK_EXTERNAL(ep);
    metaball_count = ntohl(*(uint32_t *)ep->ext_buf);
    buf = (double *)bu_malloc((metaball_count*5+1)*SIZEOF_NETWORK_DOUBLE, "rt_metaball_import5: buf");
    ntohd((unsigned char *)buf, (unsigned char *)ep->ext_buf+2*SIZEOF_NETWORK_LONG, metaball_count*5+1);

    RT_CK_DB_INTERNAL(ip);
    ip->idb_major_type = DB5_MAJORTYPE_BRLCAD;
    ip->idb_type = ID_METABALL;
    ip->idb_meth = &rt_functab[ID_METABALL];
    BU_ALLOC(ip->idb_ptr, struct rt_metaball_internal);

    mb = (struct rt_metaball_internal *)ip->idb_ptr;
    mb->magic = RT_METABALL_INTERNAL_MAGIC;
    mb->method = ntohl(*(uint32_t *)(ep->ext_buf + SIZEOF_NETWORK_LONG));
    mb->threshold = buf[0];

    BU_LIST_INIT(&mb->metaball_ctrl_head);
    if (mat == NULL) mat = bn_mat_identity;
    for (i=1; i<=metaball_count*5; i+=5) {
	/* Apply modeling transformations */
	BU_GET(mbpt, struct wdb_metaballpt);
	mbpt->l.magic = WDB_METABALLPT_MAGIC;
	MAT4X3PNT(mbpt->coord, mat, &buf[i]);
	mbpt->fldstr = buf[i+3] / mat[15];
	mbpt->sweat = buf[i+4];
	BU_LIST_INSERT(&mb->metaball_ctrl_head, &mbpt->l);
    }

    bu_free((genptr_t)buf, "rt_metaball_import5: buf");
    return 0;		/* OK */
}