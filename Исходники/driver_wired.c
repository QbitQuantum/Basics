static void * wpa_driver_wired_init(void *ctx, const char *ifname)
{
	struct wpa_driver_wired_data *drv;
	int flags;

	drv = os_zalloc(sizeof(*drv));
	if (drv == NULL)
		return NULL;
	os_strlcpy(drv->ifname, ifname, sizeof(drv->ifname));
	drv->ctx = ctx;

#ifdef __linux__
	drv->pf_sock = socket(PF_PACKET, SOCK_DGRAM, 0);
	if (drv->pf_sock < 0)
		perror("socket(PF_PACKET)");
#else /* __linux__ */
	drv->pf_sock = -1;
#endif /* __linux__ */

	if (wpa_driver_wired_get_ifflags(ifname, &flags) == 0 &&
	    !(flags & IFF_UP) &&
	    wpa_driver_wired_set_ifflags(ifname, flags | IFF_UP) == 0) {
		drv->iff_up = 1;
	}

	if (wired_multicast_membership(drv->pf_sock,
				       if_nametoindex(drv->ifname),
				       pae_group_addr, 1) == 0) {
		wpa_printf(MSG_DEBUG, "%s: Added multicast membership with "
			   "packet socket", __func__);
		drv->membership = 1;
	} else if (wpa_driver_wired_multi(ifname, pae_group_addr, 1) == 0) {
		wpa_printf(MSG_DEBUG, "%s: Added multicast membership with "
			   "SIOCADDMULTI", __func__);
		drv->multi = 1;
	} else if (wpa_driver_wired_get_ifflags(ifname, &flags) < 0) {
		wpa_printf(MSG_INFO, "%s: Could not get interface "
			   "flags", __func__);
		os_free(drv);
		return NULL;
	} else if (flags & IFF_ALLMULTI) {
		wpa_printf(MSG_DEBUG, "%s: Interface is already configured "
			   "for multicast", __func__);
	} else if (wpa_driver_wired_set_ifflags(ifname,
						flags | IFF_ALLMULTI) < 0) {
		wpa_printf(MSG_INFO, "%s: Failed to enable allmulti",
			   __func__);
		os_free(drv);
		return NULL;
	} else {
		wpa_printf(MSG_DEBUG, "%s: Enabled allmulti mode",
			   __func__);
		drv->iff_allmulti = 1;
	}
#if defined(__FreeBSD__) || defined(__DragonFly__) || defined(__FreeBSD_kernel__)
	{
		int status;
		wpa_printf(MSG_DEBUG, "%s: waiting for link to become active",
			   __func__);
		while (wpa_driver_wired_get_ifstatus(ifname, &status) == 0 &&
		       status == 0)
			sleep(1);
	}
#endif /* defined(__FreeBSD__) || defined(__DragonFly__) || defined(FreeBSD_kernel__) */

	return drv;
}