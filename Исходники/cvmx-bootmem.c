int64_t cvmx_bootmem_phy_named_block_alloc(uint64_t size, uint64_t min_addr,
					   uint64_t max_addr,
					   uint64_t alignment,
					   char *name,
					   uint32_t flags)
{
	int64_t addr_allocated;
	struct cvmx_bootmem_named_block_desc *named_block_desc_ptr;

#ifdef DEBUG
	cvmx_dprintf("cvmx_bootmem_phy_named_block_alloc: size: 0x%llx, min: "
		     "0x%llx, max: 0x%llx, align: 0x%llx, name: %s\n",
		     (unsigned long long)size,
		     (unsigned long long)min_addr,
		     (unsigned long long)max_addr,
		     (unsigned long long)alignment,
		     name);
#endif
	if (cvmx_bootmem_desc->major_version != 3) {
		cvmx_dprintf("ERROR: Incompatible bootmem descriptor version: "
			     "%d.%d at addr: %p\n",
			     (int)cvmx_bootmem_desc->major_version,
			     (int)cvmx_bootmem_desc->minor_version,
			     cvmx_bootmem_desc);
		return -1;
	}

	/*
	 * Take lock here, as name lookup/block alloc/name add need to
	 * be atomic.
	 */
	if (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
		cvmx_spinlock_lock((cvmx_spinlock_t *)&(cvmx_bootmem_desc->lock));

	/* Get pointer to first available named block descriptor */
	named_block_desc_ptr =
		cvmx_bootmem_phy_named_block_find(NULL,
						  flags | CVMX_BOOTMEM_FLAG_NO_LOCKING);

	/*
	 * Check to see if name already in use, return error if name
	 * not available or no more room for blocks.
	 */
	if (cvmx_bootmem_phy_named_block_find(name,
					      flags | CVMX_BOOTMEM_FLAG_NO_LOCKING) || !named_block_desc_ptr) {
		if (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
			cvmx_spinlock_unlock((cvmx_spinlock_t *)&(cvmx_bootmem_desc->lock));
		return -1;
	}


	/*
	 * Round size up to mult of minimum alignment bytes We need
	 * the actual size allocated to allow for blocks to be
	 * coallesced when they are freed.  The alloc routine does the
	 * same rounding up on all allocations.
	 */
	size = ALIGN(size, CVMX_BOOTMEM_ALIGNMENT_SIZE);

	addr_allocated = cvmx_bootmem_phy_alloc(size, min_addr, max_addr,
						alignment,
						flags | CVMX_BOOTMEM_FLAG_NO_LOCKING);
	if (addr_allocated >= 0) {
		named_block_desc_ptr->base_addr = addr_allocated;
		named_block_desc_ptr->size = size;
		strncpy(named_block_desc_ptr->name, name,
			cvmx_bootmem_desc->named_block_name_len);
		named_block_desc_ptr->name[cvmx_bootmem_desc->named_block_name_len - 1] = 0;
	}

	if (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
		cvmx_spinlock_unlock((cvmx_spinlock_t *)&(cvmx_bootmem_desc->lock));
	return addr_allocated;
}