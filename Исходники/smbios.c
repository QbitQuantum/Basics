unsigned long smbios_write_tables(unsigned long current)
{
	struct smbios_entry *se;
	unsigned long tables;
	int len = 0;
	int max_struct_size = 0;
	int handle = 0;

	current = ALIGN(current, 16);
	printk(BIOS_DEBUG, "%s: %08lx\n", __func__, current);

	se = (struct smbios_entry *)current;
	current += sizeof(struct smbios_entry);
	current = ALIGN(current, 16);

	tables = current;
	update_max(len, max_struct_size, smbios_write_type0(&current,
		handle++));
	update_max(len, max_struct_size, smbios_write_type1(&current,
		handle++));
	update_max(len, max_struct_size, smbios_write_type2(&current,
		handle, handle + 1)); /* The chassis handle is the next one */
	handle++;
	update_max(len, max_struct_size, smbios_write_type3(&current,
		handle++));
	update_max(len, max_struct_size, smbios_write_type4(&current,
		handle++));
	update_max(len, max_struct_size, smbios_write_type11(&current,
		&handle));
	if (IS_ENABLED(CONFIG_ELOG))
		update_max(len, max_struct_size,
			elog_smbios_write_type15(&current,handle++));
	update_max(len, max_struct_size, smbios_write_type16(&current,
		handle++));
	update_max(len, max_struct_size, smbios_write_type17(&current,
		&handle));
	update_max(len, max_struct_size, smbios_write_type19(&current,
		handle++));
	update_max(len, max_struct_size, smbios_write_type20(&current,
		&handle));
	update_max(len, max_struct_size, smbios_write_type32(&current,
		handle++));

	update_max(len, max_struct_size, smbios_walk_device_tree(all_devices,
		&handle, &current));

	update_max(len, max_struct_size, smbios_write_type127(&current,
		handle++));

	memset(se, 0, sizeof(struct smbios_entry));
	memcpy(se->anchor, "_SM_", 4);
	se->length = sizeof(struct smbios_entry);
	se->major_version = 2;
	se->minor_version = 7;
	se->max_struct_size = max_struct_size;
	se->struct_count = handle;
	se->smbios_bcd_revision = 0x27;
	memcpy(se->intermediate_anchor_string, "_DMI_", 5);

	se->struct_table_address = (u32)tables;
	se->struct_table_length = len;

	se->intermediate_checksum = smbios_checksum((u8 *)se + 0x10,
						    sizeof(struct smbios_entry)
						    - 0x10);
	se->checksum = smbios_checksum((u8 *)se, sizeof(struct smbios_entry));
	return current;
}