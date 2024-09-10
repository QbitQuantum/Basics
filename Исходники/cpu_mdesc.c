static int
cpu_n2_mdesc_init(topo_mod_t *mod, md_t *mdp, md_info_t *chip)
{
	mde_cookie_t *list1p, *list2p;
	md_cpumap_t *mcmp;
	md_proc_t *procp;
	md_fru_t *frup;
	int i, j, cnt;
	int procid_flag = 0;
	int nnode, ncomp, nproc, ncpu;
	char *str = NULL;
	uint64_t x, sn;
	char *strserial, *end;

	nnode = md_node_count(mdp);
	list1p = topo_mod_zalloc(mod, sizeof (mde_cookie_t) * nnode);

	/* Count the number of processors and strands */
	ncomp = md_scan_dag(mdp,
	    MDE_INVAL_ELEM_COOKIE,
	    md_find_name(mdp, MD_STR_COMPONENT),
	    md_find_name(mdp, "fwd"),
	    list1p);
	if (ncomp <= 0) {
		topo_mod_dprintf(mod, "Component nodes not found\n");
		topo_mod_free(mod, list1p, sizeof (mde_cookie_t) * nnode);
		return (-1);
	}
	for (i = 0, nproc = 0, ncpu = 0; i < ncomp; i++) {
		if (md_get_prop_str(mdp, list1p[i], MD_STR_TYPE, &str) == 0 &&
		    str != NULL && strcmp(str, MD_STR_PROCESSOR) == 0) {
			nproc++;
			/* check if the physical id exists */
			if (md_get_prop_val(mdp, list1p[i], MD_STR_ID, &x)
			    == 0) {
				procid_flag = 1;
			}
		}
		if (md_get_prop_str(mdp, list1p[i], MD_STR_TYPE, &str) == 0 &&
		    str && strcmp(str, MD_STR_STRAND) == 0) {
			ncpu++;
		}
	}
	topo_mod_dprintf(mod, "Found %d procs and %d strands\n", nproc, ncpu);
	if (nproc == 0 || ncpu == 0) {
		topo_mod_free(mod, list1p, sizeof (mde_cookie_t) * nnode);
		return (-1);
	}

	/* Alloc processors and strand entries */
	list2p = topo_mod_zalloc(mod, sizeof (mde_cookie_t) * 2 * ncpu);
	chip->nprocs = nproc;
	chip->procs = topo_mod_zalloc(mod, nproc * sizeof (md_proc_t));
	chip->ncpus = ncpu;
	chip->cpus = topo_mod_zalloc(mod, ncpu * sizeof (md_cpumap_t));

	/* Visit each processor node */
	procp = chip->procs;
	mcmp = chip->cpus;
	for (i = 0, nproc = 0, ncpu = 0; i < ncomp; i++) {
		if (md_get_prop_str(mdp, list1p[i], MD_STR_TYPE, &str) < 0 ||
		    str == NULL || strcmp(str, MD_STR_PROCESSOR))
			continue;
		if (md_get_prop_val(mdp, list1p[i], MD_STR_SERIAL, &sn) < 0) {
			if (md_get_prop_str(mdp, list1p[i], MD_STR_SERIAL,
			    &strserial) < 0) {
				topo_mod_dprintf(mod,
				    "Failed to get the serial number of"
				    "proc[%d]\n", nproc);
				continue;
			} else {
				sn = (uint64_t)strtoull(strserial, &end, 16);
				if (strserial == end) {
					topo_mod_dprintf(mod,
					    "Failed to convert the serial "
					    "string to serial int of "
					    "proc[%d]\n", nproc);
					continue;
				}
			}
		}
		procp->serialno = sn;

		/* Assign physical proc id */
		procp->id = -1;
		if (procid_flag) {
			if (md_get_prop_val(mdp, list1p[i], MD_STR_ID, &x)
			    == 0) {
				procp->id = x;
			}
		} else {
			procp->id = nproc;
		}
		topo_mod_dprintf(mod, "proc %d: sn=%llx, id=%d\n", nproc,
		    procp->serialno, procp->id);

		/* Get all the strands below this proc */
		cnt = md_scan_dag(mdp,
		    list1p[i],
		    md_find_name(mdp, MD_STR_COMPONENT),
		    md_find_name(mdp, "fwd"),
		    list2p);
		topo_mod_dprintf(mod, "proc[%llx]: Found %d fwd components\n",
		    sn, cnt);
		if (cnt <= 0) {
			nproc++;
			procp++;
			continue;
		}
		for (j = 0; j < cnt; j++) {
			/* Consider only the strand nodes */
			if (md_get_prop_str(mdp, list2p[j], MD_STR_TYPE, &str)
			    < 0 || str == NULL || strcmp(str, MD_STR_STRAND))
				continue;

			if (md_get_prop_val(mdp, list2p[j], MD_STR_ID, &x) < 0)
				x = (uint64_t)-1; /* invalid value */
			mcmp->cpumap_id = x;

			if (md_get_prop_val(mdp, list2p[j], MD_STR_PID, &x) < 0)
				x = mcmp->cpumap_id;
			mcmp->cpumap_pid = x;

			mcmp->cpumap_serialno = sn;
			mcmp->cpumap_chipidx = nproc;
			ncpu++;
			mcmp++;
		}

		/*
		 * To get the fru of this proc, follow the back arc up to
		 * find the first node whose fru field is set
		 */
		cnt = md_scan_dag(mdp,
		    list1p[i],
		    md_find_name(mdp, MD_STR_COMPONENT),
		    md_find_name(mdp, "back"),
		    list2p);
		topo_mod_dprintf(mod, "proc[%d]: Found %d back components\n",
		    nproc, cnt);
		if (cnt <= 0) {
			nproc++;
			procp++;
			continue;
		}
		for (j = 0; j < cnt; j++) {
			/* test the fru field which must be positive number */
			if ((md_get_prop_val(mdp, list2p[j], MD_STR_FRU, &x)
			    == 0) && x > 0)
				break;
		}
		if (j < cnt) {
			/* Found the FRU node, get the fru identity */
			topo_mod_dprintf(mod, "proc[%d] sn=%llx has a fru %d\n",
			    nproc, procp->serialno, j);
			frup = topo_mod_zalloc(mod, sizeof (md_fru_t));
			procp->fru = frup;
			if (!md_get_prop_str(mdp, list2p[j], MD_STR_NAC, &str))
				frup->nac = topo_mod_strdup(mod, str);
			else
				frup->nac = topo_mod_strdup(mod, MD_FRU_DEF);
			if (!md_get_prop_str(mdp, list2p[j], MD_STR_PART, &str))
				frup->part = topo_mod_strdup(mod, str);
			if (!md_get_prop_str(mdp, list2p[j], MD_STR_SERIAL,
			    &str))
				frup->serial = topo_mod_strdup(mod, str);
			if (!md_get_prop_str(mdp, list2p[j], MD_STR_DASH, &str))
				frup->dash = topo_mod_strdup(mod, str);
		} else {
			topo_mod_dprintf(mod, "proc[%d] sn=%llx has no fru\n",
			    i, procp->serialno);
		}

		nproc++;
		procp++;
	} /* for i */

	topo_mod_free(mod, list1p, sizeof (mde_cookie_t) * nnode);
	topo_mod_free(mod, list2p, sizeof (mde_cookie_t) * 2*chip->ncpus);

	return (0);
}