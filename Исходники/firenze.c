static void firenze_send_pci_inventory(void)
{
	uint64_t base, abase, end, aend, offset;
	int64_t rc;

	if (!fsp_pcie_inv)
		return;

	prlog(PR_DEBUG, "PLAT: Sending PCI inventory to FSP, table has"
	      " %d entries\n",
	      fsp_pcie_inv->num_entries);

	{
		unsigned int i;

		prlog(PR_DEBUG, "HWP SLT VDID DVID SVID SDID\n");
		prlog(PR_DEBUG, "---------------------------\n");
		for (i = 0; i < fsp_pcie_inv->num_entries; i++) {
			struct fsp_pcie_entry *e = &fsp_pcie_inv->entries[i];

			prlog(PR_DEBUG, "%03d %03d %04x %04x %04x %04x\n",
			      e->hw_proc_id, e->slot_idx,
			      e->vendor_id, e->device_id,
			      e->subsys_vendor_id, e->subsys_device_id);
		}
	}

	/*
	 * Get the location of the table in a form we can send
	 * to the FSP
	 */
	base = (uint64_t)fsp_pcie_inv;
	end = base + sizeof(struct fsp_pcie_inventory) +
		fsp_pcie_inv->num_entries * fsp_pcie_inv->entry_size;
	abase = base & ~0xffful;
	aend = (end + 0xffful) & ~0xffful;
	offset = PSI_DMA_PCIE_INVENTORY + (base & 0xfff);

	/* We can only accomodate so many entries in the PSI map */
	if ((aend - abase) > PSI_DMA_PCIE_INVENTORY_SIZE) {
		prerror("PLAT: PCIe inventory too large (%lld bytes)\n",
			aend - abase);
		goto bail;
	}

	/* Map this in the TCEs */
	fsp_tce_map(PSI_DMA_PCIE_INVENTORY, (void *)abase, aend - abase);

	/* Send FSP message */
	rc = fsp_sync_msg(fsp_mkmsg(FSP_CMD_PCI_POWER_CONF, 3,
				    hi32(offset), lo32(offset),
				    end - base), true);
	if (rc)
		prerror("PLAT: FSP error %lld sending inventory\n", rc);

	/* Unmap */
	fsp_tce_unmap(PSI_DMA_PCIE_INVENTORY, aend - abase);
 bail:
	/*
	 * We free the inventory. We'll have to redo that on hotplug
	 * when we support it but that isn't the case yet
	 */
	free(fsp_pcie_inv);
	fsp_pcie_inv = NULL;
}