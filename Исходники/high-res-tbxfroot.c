__init u32 hrt_get_acpi_pm_ptr(void)
{
	struct fadt_descriptor_rev2 *fadt2;
	struct fadt_descriptor_rev1 *fadt1;
	struct rsdt_descriptor_rev1 *rsdt;
	struct xsdt_descriptor_rev2 *xsdt;
	RSDP_DESCRIPTOR *rsdp = hrt_find_acpi_rsdp();
	struct acpi_table_header *header;
	u32 rtn;

	if (!rsdp) {
		printk("ACPI: System description tables not found\n");
		return 0;
	}
	/*
	 * Now that we have that problem out of the way, lets set up this
	 * timer.  We need to figure the addresses based on the revision
	 * of ACPI, which is in this here table we just found.
	 * We will not check the RSDT checksum, but will the FADT.
	 */
	if (rsdp->revision == 2) {
		xsdt =
		    (struct xsdt_descriptor_rev2 *) 
			__va(rsdp->xsdt_physical_address);
		fadt2 =
		    (struct fadt_descriptor_rev2 *)
			__va(xsdt->table_offset_entry[0]);
		header = (struct acpi_table_header *) fadt2;
		rtn = (u32) fadt2->xpm_tmr_blk.address;
	} else {
		rsdt =
		    (struct rsdt_descriptor_rev1 *) 
			__va(rsdp->rsdt_physical_address);
		fadt1 =
		    (struct fadt_descriptor_rev1 *) 
			__va(rsdt->table_offset_entry[0]);
		header = (struct acpi_table_header *) fadt1;
		rtn = (u32) fadt1->pm_tmr_blk;
	}
	/*
	 * Verify the signature and the checksum, if good, return
	 * the address.
	 */
	if (STRNCMP((NATIVE_CHAR *) header->signature,
		    FADT_SIG, sizeof (FADT_SIG) - 1) == 0 &&
	    hrt_acpi_checksum((NATIVE_CHAR *) header, header->length) == 0) 
		return rtn;

	printk("ACPI: Signature or checksum failed on FADT\n");
	return 0;
}