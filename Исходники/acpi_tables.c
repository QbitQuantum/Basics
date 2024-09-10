unsigned long write_acpi_tables(unsigned long start)
{
	unsigned long current;
	acpi_rsdp_t *rsdp;
	acpi_rsdt_t *rsdt;
	acpi_hpet_t *hpet;
	acpi_madt_t *madt;
	acpi_srat_t *srat;
	acpi_slit_t *slit;
	acpi_fadt_t *fadt;
	acpi_facs_t *facs;
	acpi_header_t *dsdt;
	acpi_header_t *ssdt;
	acpi_header_t *ssdtx;
	void *p;

	int i;

	get_bus_conf(); //it will get sblk, pci1234, hcdn, and sbdn

	/* Align ACPI tables to 16 bytes */
	start = ALIGN(start, 16);
	current = start;

	printk(BIOS_INFO, "ACPI: Writing ACPI tables at %lx...\n", start);

	/* We need at least an RSDP and an RSDT Table */
	rsdp = (acpi_rsdp_t *) current;
	current += sizeof(acpi_rsdp_t);
	rsdt = (acpi_rsdt_t *) current;
	current += sizeof(acpi_rsdt_t);

	/* clear all table memory */
	memset((void *)start, 0, current - start);

	acpi_write_rsdp(rsdp, rsdt, NULL);
	acpi_write_rsdt(rsdt);

	/* FACS */
	printk(BIOS_DEBUG, "ACPI:    * FACS\n");
	facs = (acpi_facs_t *) current;
	current += sizeof(acpi_facs_t);
	acpi_create_facs(facs);

	/* DSDT */
	printk(BIOS_DEBUG, "ACPI:    * DSDT at %lx\n", current);
	dsdt = (acpi_header_t *)current;
	memcpy(dsdt, &AmlCode, sizeof(acpi_header_t));
	current += dsdt->length;
	memcpy(dsdt, &AmlCode, dsdt->length);
	printk(BIOS_DEBUG, "ACPI:    * DSDT @ %p Length %x\n", dsdt, dsdt->length);

	/* FADT */
	printk(BIOS_DEBUG, "ACPI:    * FADT at %lx\n", current);
	fadt = (acpi_fadt_t *) current;
	current += sizeof(acpi_fadt_t);

	acpi_create_fadt(fadt, facs, dsdt);
	acpi_add_table(rsdp, fadt);

	/*
	 * We explicitly add these tables later on:
	 */
	printk(BIOS_DEBUG, "ACPI:    * HPET at %lx\n", current);
	hpet = (acpi_hpet_t *) current;
	current += sizeof(acpi_hpet_t);
	acpi_create_hpet(hpet);
	acpi_add_table(rsdp, hpet);

	/* If we want to use HPET Timers Linux wants an MADT */
	printk(BIOS_DEBUG, "ACPI:    * MADT at %lx\n", current);
	madt = (acpi_madt_t *) current;
	acpi_create_madt(madt);
	current+=madt->header.length;
	acpi_add_table(rsdp, madt);

	/* SRAT */
	printk(BIOS_DEBUG, "ACPI:    * SRAT at %lx\n", current);
	srat = (acpi_srat_t *) current;
	acpi_create_srat(srat);
	current+=srat->header.length;
	acpi_add_table(rsdp, srat);

	/* SLIT */
	printk(BIOS_DEBUG, "ACPI:   * SLIT at %lx\n", current);
	slit = (acpi_slit_t *) current;
	acpi_create_slit(slit);
	current+=slit->header.length;
	acpi_add_table(rsdp, slit);

	/* SSDT */
	printk(BIOS_DEBUG, "ACPI:    * SSDT at %lx\n", current);
	ssdt = (acpi_header_t *)current;

	acpi_create_ssdt_generator(ssdt, ACPI_TABLE_CREATOR);
	current += ssdt->length;
	acpi_add_table(rsdp, ssdt);

#if CONFIG_ACPI_SSDTX_NUM >= 1

	//same htio, but different position? We may have to copy, change HCIN, and recalculate the checknum and add_table

	for(i=1;i<sysconf.hc_possible_num;i++) {  // 0: is hc sblink
		if((sysconf.pci1234[i] & 1) != 1 ) continue;
		u8 c;
		if(i<7) {
			c  = (u8) ('4' + i - 1);
		}
		else {
			c  = (u8) ('A' + i - 1 - 6);
		}
		current = ALIGN(current, 8);
		printk(BIOS_DEBUG, "ACPI:    * SSDT for PCI%c Aka hcid = %d\n", c, sysconf.hcid[i]); //pci0 and pci1 are in dsdt
		ssdtx = (acpi_header_t *)current;
		switch(sysconf.hcid[i]) {
		case 1: //8132
			p = &AmlCode_ssdt2;
			break;
		case 2: //8151
			p = &AmlCode_ssdt3;
			break;
		case 3: //8131
			p = &AmlCode_ssdt4;
			break;
		default:
			continue;
		}
		memcpy(ssdtx, p, sizeof(acpi_header_t));
		current += ssdtx->length;
		memcpy(ssdtx, p, ssdtx->length);
		update_ssdtx((void *)ssdtx, i);
		ssdtx->checksum = 0;
		ssdtx->checksum = acpi_checksum((u8 *)ssdtx, ssdtx->length);
		acpi_add_table(rsdp, ssdtx);
	}
#endif

	printk(BIOS_INFO, "ACPI: done.\n");
	return current;
}