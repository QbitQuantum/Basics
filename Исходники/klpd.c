/*
 * Register the klpd.
 * If the pid_t passed in is positive, update the registration for
 * the specific process; that is only possible if the process already
 * has a registration on it.  This change of registration will affect
 * all processes which share common ancestry.
 *
 * MY_PID (pid 0) can be used to create or change the context for
 * the current process, typically done after fork().
 *
 * A negative value can be used to register a klpd globally.
 *
 * The per-credential klpd needs to be cleaned up when entering
 * a zone or unsetting the flag.
 */
int
klpd_reg(int did, idtype_t type, id_t id, priv_set_t *psetbuf)
{
	cred_t *cr = CRED();
	door_handle_t dh;
	klpd_reg_t *kpd;
	priv_set_t pset;
	door_info_t di;
	credklpd_t *ckp = NULL;
	pid_t pid = -1;
	projid_t proj = -1;
	kproject_t *kpp = NULL;

	if (CR_FLAGS(cr) & PRIV_XPOLICY)
		return (set_errno(EINVAL));

	if (copyin(psetbuf, &pset, sizeof (priv_set_t)))
		return (set_errno(EFAULT));

	if (!priv_issubset(&pset, &CR_OEPRIV(cr)))
		return (set_errno(EPERM));

	switch (type) {
	case P_PID:
		pid = (pid_t)id;
		if (pid == P_MYPID)
			pid = curproc->p_pid;
		if (pid == curproc->p_pid)
			ckp = crklpd_alloc();
		break;
	case P_PROJID:
		proj = (projid_t)id;
		kpp = project_hold_by_id(proj, crgetzone(cr),
		    PROJECT_HOLD_FIND);
		if (kpp == NULL)
			return (set_errno(ESRCH));
		break;
	default:
		return (set_errno(ENOTSUP));
	}


	/*
	 * Verify the door passed in; it must be a door and we won't
	 * allow processes to be called on their own behalf.
	 */
	dh = door_ki_lookup(did);
	if (dh == NULL || door_ki_info(dh, &di) != 0) {
		if (ckp != NULL)
			crklpd_rele(ckp);
		if (kpp != NULL)
			project_rele(kpp);
		return (set_errno(EBADF));
	}
	if (type == P_PID && pid == di.di_target) {
		if (ckp != NULL)
			crklpd_rele(ckp);
		ASSERT(kpp == NULL);
		return (set_errno(EINVAL));
	}

	kpd = kmem_zalloc(sizeof (*kpd), KM_SLEEP);
	crhold(kpd->klpd_cred = cr);
	kpd->klpd_door = dh;
	kpd->klpd_door_pid = di.di_target;
	kpd->klpd_ref = 1;
	kpd->klpd_pset = pset;

	if (kpp != NULL) {
		mutex_enter(&klpd_mutex);
		kpd = klpd_link(kpd, &kpp->kpj_klpd, B_TRUE);
		mutex_exit(&klpd_mutex);
		if (kpd != NULL)
			klpd_rele(kpd);
		project_rele(kpp);
	} else if ((int)pid < 0) {
		/* Global daemon */
		mutex_enter(&klpd_mutex);
		(void) klpd_link(kpd, &klpd_list, B_FALSE);
		mutex_exit(&klpd_mutex);
	} else if (pid == curproc->p_pid) {
		proc_t *p = curproc;
		cred_t *newcr = cralloc();

		/* No need to lock, sole reference to ckp */
		kpd = klpd_link(kpd, &ckp->crkl_reg, B_TRUE);

		if (kpd != NULL)
			klpd_rele(kpd);

		mutex_enter(&p->p_crlock);
		cr = p->p_cred;
		crdup_to(cr, newcr);
		crsetcrklpd(newcr, ckp);
		p->p_cred = newcr;	/* Already held for p_cred */

		crhold(newcr);		/* Hold once for the current thread */
		mutex_exit(&p->p_crlock);
		crfree(cr);		/* One for the p_cred */
		crset(p, newcr);
	} else {
		proc_t *p;
		cred_t *pcr;
		mutex_enter(&pidlock);
		p = prfind(pid);
		if (p == NULL || !prochasprocperm(p, curproc, CRED())) {
			mutex_exit(&pidlock);
			klpd_rele(kpd);
			return (set_errno(p == NULL ? ESRCH : EPERM));
		}
		mutex_enter(&p->p_crlock);
		crhold(pcr = p->p_cred);
		mutex_exit(&pidlock);
		mutex_exit(&p->p_crlock);
		/*
		 * We're going to update the credential's ckp in place;
		 * this requires that it exists.
		 */
		ckp = crgetcrklpd(pcr);
		if (ckp == NULL) {
			crfree(pcr);
			klpd_rele(kpd);
			return (set_errno(EINVAL));
		}
		crklpd_setreg(ckp, kpd);
		crfree(pcr);
	}

	return (0);
}