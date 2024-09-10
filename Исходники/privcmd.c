static int
privcmd_ioctl(struct cdev *dev, unsigned long cmd, caddr_t arg,
	      int mode, struct thread *td)
{
	int error, i;

	switch (cmd) {
	case IOCTL_PRIVCMD_HYPERCALL: {
		struct ioctl_privcmd_hypercall *hcall;

		hcall = (struct ioctl_privcmd_hypercall *)arg;
#ifdef __amd64__
		/*
		 * The hypervisor page table walker will refuse to access
		 * user-space pages if SMAP is enabled, so temporary disable it
		 * while performing the hypercall.
		 */
		if (cpu_stdext_feature & CPUID_STDEXT_SMAP)
			stac();
#endif
		error = privcmd_hypercall(hcall->op, hcall->arg[0],
		    hcall->arg[1], hcall->arg[2], hcall->arg[3], hcall->arg[4]);
#ifdef __amd64__
		if (cpu_stdext_feature & CPUID_STDEXT_SMAP)
			clac();
#endif
		if (error >= 0) {
			hcall->retval = error;
			error = 0;
		} else {
			error = xen_translate_error(error);
			hcall->retval = 0;
		}
		break;
	}
	case IOCTL_PRIVCMD_MMAPBATCH: {
		struct ioctl_privcmd_mmapbatch *mmap;
		vm_map_t map;
		vm_map_entry_t entry;
		vm_object_t mem;
		vm_pindex_t pindex;
		vm_prot_t prot;
		boolean_t wired;
		struct xen_add_to_physmap_range add;
		xen_ulong_t *idxs;
		xen_pfn_t *gpfns;
		int *errs, index;
		struct privcmd_map *umap;
		uint16_t num;

		mmap = (struct ioctl_privcmd_mmapbatch *)arg;

		if ((mmap->num == 0) ||
		    ((mmap->addr & PAGE_MASK) != 0)) {
			error = EINVAL;
			break;
		}

		map = &td->td_proc->p_vmspace->vm_map;
		error = vm_map_lookup(&map, mmap->addr, VM_PROT_NONE, &entry,
		    &mem, &pindex, &prot, &wired);
		if (error != KERN_SUCCESS) {
			error = EINVAL;
			break;
		}
		if ((entry->start != mmap->addr) ||
		    (entry->end != mmap->addr + (mmap->num * PAGE_SIZE))) {
			vm_map_lookup_done(map, entry);
			error = EINVAL;
			break;
		}
		vm_map_lookup_done(map, entry);
		if ((mem->type != OBJT_MGTDEVICE) ||
		    (mem->un_pager.devp.ops != &privcmd_pg_ops)) {
			error = EINVAL;
			break;
		}
		umap = mem->handle;

		add.domid = DOMID_SELF;
		add.space = XENMAPSPACE_gmfn_foreign;
		add.foreign_domid = mmap->dom;

		/*
		 * The 'size' field in the xen_add_to_physmap_range only
		 * allows for UINT16_MAX mappings in a single hypercall.
		 */
		num = MIN(mmap->num, UINT16_MAX);

		idxs = malloc(sizeof(*idxs) * num, M_PRIVCMD, M_WAITOK);
		gpfns = malloc(sizeof(*gpfns) * num, M_PRIVCMD, M_WAITOK);
		errs = malloc(sizeof(*errs) * num, M_PRIVCMD, M_WAITOK);

		set_xen_guest_handle(add.idxs, idxs);
		set_xen_guest_handle(add.gpfns, gpfns);
		set_xen_guest_handle(add.errs, errs);

		/* Allocate a bitset to store broken page mappings. */
		umap->err = BITSET_ALLOC(mmap->num, M_PRIVCMD,
		    M_WAITOK | M_ZERO);

		for (index = 0; index < mmap->num; index += num) {
			num = MIN(mmap->num - index, UINT16_MAX);
			add.size = num;

			error = copyin(&mmap->arr[index], idxs,
			    sizeof(idxs[0]) * num);
			if (error != 0)
				goto mmap_out;

			for (i = 0; i < num; i++)
				gpfns[i] = atop(umap->phys_base_addr +
				    (i + index) * PAGE_SIZE);

			bzero(errs, sizeof(*errs) * num);

			error = HYPERVISOR_memory_op(
			    XENMEM_add_to_physmap_range, &add);
			if (error != 0) {
				error = xen_translate_error(error);
				goto mmap_out;
			}

			for (i = 0; i < num; i++) {
				if (errs[i] != 0) {
					errs[i] = xen_translate_error(errs[i]);

					/* Mark the page as invalid. */
					BIT_SET(mmap->num, index + i,
					    umap->err);
				}
			}

			error = copyout(errs, &mmap->err[index],
			    sizeof(errs[0]) * num);
			if (error != 0)
				goto mmap_out;
		}

		umap->mapped = true;

mmap_out:
		free(idxs, M_PRIVCMD);
		free(gpfns, M_PRIVCMD);
		free(errs, M_PRIVCMD);
		if (!umap->mapped)
			free(umap->err, M_PRIVCMD);

		break;
	}

	default:
		error = ENOSYS;
		break;
	}

	return (error);
}