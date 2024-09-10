static int wl1271_boot_upload_nvs(struct wl1271 *wl)
{
	size_t nvs_len, burst_len;
	int i;
	u32 dest_addr, val;
	u8 *nvs_ptr, *nvs, *nvs_aligned;

	nvs = wl->nvs;
	if (nvs == NULL)
		return -ENODEV;

	nvs_ptr = nvs;

	nvs_len = wl->nvs_len;

	/* Update the device MAC address into the nvs */
	nvs[11] = wl->mac_addr[0];
	nvs[10] = wl->mac_addr[1];
	nvs[6] = wl->mac_addr[2];
	nvs[5] = wl->mac_addr[3];
	nvs[4] = wl->mac_addr[4];
	nvs[3] = wl->mac_addr[5];

	/*
	 * Layout before the actual NVS tables:
	 * 1 byte : burst length.
	 * 2 bytes: destination address.
	 * n bytes: data to burst copy.
	 *
	 * This is ended by a 0 length, then the NVS tables.
	 */

	/* FIXME: Do we need to check here whether the LSB is 1? */
	while (nvs_ptr[0]) {
		burst_len = nvs_ptr[0];
		dest_addr = (nvs_ptr[1] & 0xfe) | ((u32)(nvs_ptr[2] << 8));

		/* FIXME: Due to our new wl1271_translate_reg_addr function,
		   we need to add the REGISTER_BASE to the destination */
		dest_addr += REGISTERS_BASE;

		/* We move our pointer to the data */
		nvs_ptr += 3;

		for (i = 0; i < burst_len; i++) {
			val = (nvs_ptr[0] | (nvs_ptr[1] << 8)
			       | (nvs_ptr[2] << 16) | (nvs_ptr[3] << 24));

			wl1271_debug(DEBUG_BOOT,
				     "nvs burst write 0x%x: 0x%x",
				     dest_addr, val);
			wl1271_reg_write32(wl, dest_addr, val);

			nvs_ptr += 4;
			dest_addr += 4;
		}
	}

	/*
	 * We've reached the first zero length, the first NVS table
	 * is 7 bytes further.
	 */
	nvs_ptr += 7;
	nvs_len -= nvs_ptr - nvs;
	nvs_len = ALIGN(nvs_len, 4);

	/* FIXME: The driver sets the partition here, but this is not needed,
	   since it sets to the same one as currently in use */
	/* Now we must set the partition correctly */
	wl1271_set_partition(wl,
			     part_table[PART_WORK].mem.start,
			     part_table[PART_WORK].mem.size,
			     part_table[PART_WORK].reg.start,
			     part_table[PART_WORK].reg.size);

	/* Copy the NVS tables to a new block to ensure alignment */
	nvs_aligned = kmemdup(nvs_ptr, nvs_len, GFP_KERNEL);

	/* And finally we upload the NVS tables */
	/* FIXME: In wl1271, we upload everything at once.
	   No endianness handling needed here?! The ref driver doesn't do
	   anything about it at this point */
	wl1271_spi_mem_write(wl, CMD_MBOX_ADDRESS, nvs_aligned, nvs_len);

	kfree(nvs_aligned);
	return 0;
}