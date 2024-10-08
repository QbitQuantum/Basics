static int __ef_pd_alloc(ef_pd* pd, ef_driver_handle pd_dh,
			 int ifindex, enum ef_pd_flags flags, int vlan_id)
{
  ci_resource_alloc_t ra;
  const char* s;
  int rc;

  if( (s = getenv("EF_VI_PD_FLAGS")) != NULL ) {
    if( ! strcmp(s, "vf") )
      flags = EF_PD_VF;
    else if( ! strcmp(s, "phys") )
      flags = EF_PD_PHYS_MODE;
    else if( ! strcmp(s, "default") )
      flags = 0;
  }

  if( flags & EF_PD_VF )
    flags |= EF_PD_PHYS_MODE;

  memset(&ra, 0, sizeof(ra));
  ef_vi_set_intf_ver(ra.intf_ver, sizeof(ra.intf_ver));
  ra.ra_type = EFRM_RESOURCE_PD;
  ra.u.pd.in_ifindex = ifindex;
  ra.u.pd.in_flags = 0;
  if( flags & EF_PD_VF )
    ra.u.pd.in_flags |= EFCH_PD_FLAG_VF;
  if( flags & EF_PD_PHYS_MODE )
    ra.u.pd.in_flags |= EFCH_PD_FLAG_PHYS_ADDR;
  if( flags & EF_PD_RX_PACKED_STREAM )
    ra.u.pd.in_flags |= EFCH_PD_FLAG_RX_PACKED_STREAM;
  if( flags & EF_PD_VPORT )
    ra.u.pd.in_flags |= EFCH_PD_FLAG_VPORT;
  if( flags & EF_PD_MCAST_LOOP )
    ra.u.pd.in_flags |= EFCH_PD_FLAG_MCAST_LOOP;
  if( flags & EF_PD_MEMREG_64KiB )
    /* FIXME: We're overloading the packed-stream flag here.  The only
     * effect it has is to force ef_memreg to use at least 64KiB buffer
     * table entries.  Unfortunately this won't work if the adapter is not
     * in packed-stream mode.
     */
    ra.u.pd.in_flags |= EFCH_PD_FLAG_RX_PACKED_STREAM;
  ra.u.pd.in_vlan_id = vlan_id;

  rc = ci_resource_alloc(pd_dh, &ra);
  if( rc < 0 ) {
    LOGVV(ef_log("ef_pd_alloc: ci_resource_alloc %d", rc));
    return rc;
  }

  pd->pd_flags = flags;
  pd->pd_resource_id = ra.out_id.index;

  pd->pd_intf_name = malloc(IF_NAMESIZE);
  if( pd->pd_intf_name == NULL ) {
    LOGVV(ef_log("ef_pd_alloc: malloc failed"));
    return -ENOMEM;
  }
  if( if_indextoname(ifindex, pd->pd_intf_name) == NULL ) {
    free(pd->pd_intf_name);
    LOGVV(ef_log("ef_pd_alloc: if_indextoname failed %d", errno));
    return -errno;
  }

  pd->pd_cluster_name = NULL;
  pd->pd_cluster_sock = -1;
  pd->pd_cluster_dh = 0;
  pd->pd_cluster_viset_resource_id = 0;

  return 0;
}