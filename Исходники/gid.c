int
setgid(gid_t gid)
{
	proc_t *p;
	int error;
	int do_nocd = 0;
	cred_t	*cr, *newcr;
	ksid_t ksid, *ksp;
	zone_t	*zone = crgetzone(CRED());


	if (!VALID_GID(gid, zone))
		return (set_errno(EINVAL));

	if (gid > MAXUID) {
		if (ksid_lookupbygid(zone, gid, &ksid) != 0)
			return (set_errno(EINVAL));
		ksp = &ksid;
	} else {
		ksp = NULL;
	}

	/*
	 * Need to pre-allocate the new cred structure before grabbing
	 * the p_crlock mutex.  We cannot hold the mutex across the
	 * secpolicy functions.
	 */
	newcr = cralloc_ksid();
	p = ttoproc(curthread);
	mutex_enter(&p->p_crlock);
retry:
	cr = p->p_cred;
	crhold(cr);
	mutex_exit(&p->p_crlock);


	if ((gid == cr->cr_rgid || gid == cr->cr_sgid) &&
	    secpolicy_allow_setid(cr, -1, B_TRUE) != 0) {
		mutex_enter(&p->p_crlock);
		crfree(cr);
		if (cr != p->p_cred)
			goto retry;
		error = 0;
		crcopy_to(cr, newcr);
		p->p_cred = newcr;
		newcr->cr_gid = gid;
		crsetsid(newcr, ksp, KSID_GROUP);
		mutex_exit(&p->p_crlock);
	} else if ((error = secpolicy_allow_setid(cr, -1, B_FALSE)) == 0) {
		mutex_enter(&p->p_crlock);
		crfree(cr);
		if (cr != p->p_cred)
			goto retry;
		/*
		 * A privileged process that makes itself look like a
		 * set-gid process must be marked to produce no core dump.
		 */
		if (cr->cr_gid != gid ||
		    cr->cr_rgid != gid ||
		    cr->cr_sgid != gid)
			do_nocd = 1;
		crcopy_to(cr, newcr);
		p->p_cred = newcr;
		newcr->cr_gid = gid;
		newcr->cr_rgid = gid;
		newcr->cr_sgid = gid;
		crsetsid(newcr, ksp, KSID_GROUP);
		mutex_exit(&p->p_crlock);
	} else {
		crfree(newcr);
		crfree(cr);
		if (ksp != NULL)
			ksid_rele(ksp);

	}

	if (error == 0) {
		if (do_nocd) {
			mutex_enter(&p->p_lock);
			p->p_flag |= SNOCD;
			mutex_exit(&p->p_lock);
		}
		crset(p, newcr);	/* broadcast to process threads */
		return (0);
	}
	return (set_errno(error));
}