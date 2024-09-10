/*
 * Parallel to llc_rtrequest.
 */
static void
arp_rtrequest(
	int req,
	struct rtentry *rt,
	__unused struct sockaddr *sa)
{
	struct sockaddr *gate = rt->rt_gateway;
	struct llinfo_arp *la = rt->rt_llinfo;
	static struct sockaddr_dl null_sdl = {sizeof(null_sdl), AF_LINK, 0, 0, 0, 0, 0, {0}};
	struct timeval timenow;

	if (!arpinit_done) {
		panic("%s: ARP has not been initialized", __func__);
		/* NOTREACHED */
	}
	lck_mtx_assert(rnh_lock, LCK_MTX_ASSERT_OWNED);
	RT_LOCK_ASSERT_HELD(rt);

	if (rt->rt_flags & RTF_GATEWAY)
		return;
	getmicrotime(&timenow);
	switch (req) {

	case RTM_ADD:
		/*
		 * XXX: If this is a manually added route to interface
		 * such as older version of routed or gated might provide,
		 * restore cloning bit.
		 */
		if ((rt->rt_flags & RTF_HOST) == 0 &&
		    SIN(rt_mask(rt))->sin_addr.s_addr != 0xffffffff)
			rt->rt_flags |= RTF_CLONING;
		if (rt->rt_flags & RTF_CLONING) {
			/*
			 * Case 1: This route should come from a route to iface.
			 */
			if (rt_setgate(rt, rt_key(rt),
			    (struct sockaddr *)&null_sdl) == 0) {
				gate = rt->rt_gateway;
				SDL(gate)->sdl_type = rt->rt_ifp->if_type;
				SDL(gate)->sdl_index = rt->rt_ifp->if_index;
				/*
				 * In case we're called before 1.0 sec.
				 * has elapsed.
				 */
				rt->rt_expire = MAX(timenow.tv_sec, 1);
			}
			break;
		}
		/* Announce a new entry if requested. */
		if (rt->rt_flags & RTF_ANNOUNCE) {
			RT_UNLOCK(rt);
			dlil_send_arp(rt->rt_ifp, ARPOP_REQUEST,
			    SDL(gate), rt_key(rt), NULL, rt_key(rt));
			RT_LOCK(rt);
		}
		/*FALLTHROUGH*/
	case RTM_RESOLVE:
		if (gate->sa_family != AF_LINK ||
		    gate->sa_len < sizeof(null_sdl)) {
		        if (log_arp_warnings)
				log(LOG_DEBUG, "arp_rtrequest: bad gateway value\n");
			break;
		}
		SDL(gate)->sdl_type = rt->rt_ifp->if_type;
		SDL(gate)->sdl_index = rt->rt_ifp->if_index;
		if (la != 0)
			break; /* This happens on a route change */
		/*
		 * Case 2:  This route may come from cloning, or a manual route
		 * add with a LL address.
		 */
		rt->rt_llinfo = la = arp_llinfo_alloc();
		if (la == NULL) {
			if (log_arp_warnings)
				log(LOG_DEBUG, "%s: malloc failed\n", __func__);
			break;
		}
		rt->rt_llinfo_free = arp_llinfo_free;

		arp_inuse++, arp_allocated++;
		Bzero(la, sizeof(*la));
		la->la_rt = rt;
		rt->rt_flags |= RTF_LLINFO;
		LIST_INSERT_HEAD(&llinfo_arp, la, la_le);

		/*
		 * This keeps the multicast addresses from showing up
		 * in `arp -a' listings as unresolved.  It's not actually
		 * functional.  Then the same for broadcast.
		 */
		if (IN_MULTICAST(ntohl(SIN(rt_key(rt))->sin_addr.s_addr))) {
			RT_UNLOCK(rt);
			dlil_resolve_multi(rt->rt_ifp, rt_key(rt), gate,
			    sizeof(struct sockaddr_dl));
			RT_LOCK(rt);
			rt->rt_expire = 0;
		}
		else if (in_broadcast(SIN(rt_key(rt))->sin_addr, rt->rt_ifp)) {
			struct sockaddr_dl	*gate_ll = SDL(gate);
			size_t	broadcast_len;
			ifnet_llbroadcast_copy_bytes(rt->rt_ifp,
			    LLADDR(gate_ll), sizeof(gate_ll->sdl_data),
			    &broadcast_len);
			gate_ll->sdl_alen = broadcast_len;
			gate_ll->sdl_family = AF_LINK;
			gate_ll->sdl_len = sizeof(struct sockaddr_dl);
			/* In case we're called before 1.0 sec. has elapsed */
			rt->rt_expire = MAX(timenow.tv_sec, 1);
		}

		if (SIN(rt_key(rt))->sin_addr.s_addr ==
		    (IA_SIN(rt->rt_ifa))->sin_addr.s_addr) {
		    /*
		     * This test used to be
		     *	if (loif.if_flags & IFF_UP)
		     * It allowed local traffic to be forced
		     * through the hardware by configuring the loopback down.
		     * However, it causes problems during network configuration
		     * for boards that can't receive packets they send.
		     * It is now necessary to clear "useloopback" and remove
		     * the route to force traffic out to the hardware.
		     */
			rt->rt_expire = 0;
			ifnet_lladdr_copy_bytes(rt->rt_ifp, LLADDR(SDL(gate)), SDL(gate)->sdl_alen = 6);
			if (useloopback) {
#if IFNET_ROUTE_REFCNT
				/* Adjust route ref count for the interfaces */
				if (rt->rt_if_ref_fn != NULL &&
				    rt->rt_ifp != lo_ifp) {
					rt->rt_if_ref_fn(lo_ifp, 1);
					rt->rt_if_ref_fn(rt->rt_ifp, -1);
				}
#endif /* IFNET_ROUTE_REFCNT */
				rt->rt_ifp = lo_ifp;
			}

		}
		break;

	case RTM_DELETE:
		if (la == 0)
			break;
		arp_inuse--;
		/*
		 * Unchain it but defer the actual freeing until the route
		 * itself is to be freed.  rt->rt_llinfo still points to
		 * llinfo_arp, and likewise, la->la_rt still points to this
		 * route entry, except that RTF_LLINFO is now cleared.
		 */
		LIST_REMOVE(la, la_le);
		la->la_le.le_next = NULL;
		la->la_le.le_prev = NULL;
		rt->rt_flags &= ~RTF_LLINFO;
		if (la->la_hold != NULL)
			m_freem(la->la_hold);
		la->la_hold = NULL;
	}
}