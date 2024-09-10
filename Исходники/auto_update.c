int
au_check_header_valid(int idx, long nbytes)
{
	image_header_t *hdr;
	unsigned long checksum;
	unsigned char buf[4];

	hdr = (image_header_t *)LOAD_ADDR;
#if defined(CONFIG_FIT)
	if (genimg_get_format ((void *)hdr) != IMAGE_FORMAT_LEGACY) {
		puts ("Non legacy image format not supported\n");
		return -1;
	}
#endif

	/* check the easy ones first */
#undef CHECK_VALID_DEBUG
#ifdef CHECK_VALID_DEBUG
	printf("magic %#x %#x ", image_get_magic (hdr), IH_MAGIC);
	printf("arch %#x %#x ", image_get_arch (hdr), IH_ARCH_ARM);
	printf("size %#x %#lx ", image_get_data_size (hdr), nbytes);
	printf("type %#x %#x ", image_get_type (hdr), IH_TYPE_KERNEL);
#endif
	if (nbytes < image_get_header_size ()) {
		printf ("Image %s bad header SIZE\n", aufile[idx]);
		return -1;
	}
	if (!image_check_magic (hdr) || !image_check_arch (hdr, IH_ARCH_ARM)) {
		printf ("Image %s bad MAGIC or ARCH\n", aufile[idx]);
		return -1;
	}
	/* check the hdr CRC */
	if (!image_check_hcrc (hdr)) {
		printf ("Image %s bad header checksum\n", aufile[idx]);
		return -1;
	}
	/* check the type - could do this all in one gigantic if() */
	if ((idx == IDX_FIRMWARE) &&
		!image_check_type (hdr, IH_TYPE_FIRMWARE)) {
		printf ("Image %s wrong type\n", aufile[idx]);
		return -1;
	}
	if ((idx == IDX_KERNEL) && !image_check_type (hdr, IH_TYPE_KERNEL)) {
		printf ("Image %s wrong type\n", aufile[idx]);
		return -1;
	}
	if ((idx == IDX_DISK) && !image_check_type (hdr, IH_TYPE_FILESYSTEM)) {
		printf ("Image %s wrong type\n", aufile[idx]);
		return -1;
	}
	if ((idx == IDX_APP) && !image_check_type (hdr, IH_TYPE_RAMDISK)
		&& !image_check_type (hdr, IH_TYPE_FILESYSTEM)) {
		printf ("Image %s wrong type\n", aufile[idx]);
		return -1;
	}
	if ((idx == IDX_PREPARE || idx == IDX_PREINST || idx == IDX_POSTINST)
		&& !image_check_type (hdr, IH_TYPE_SCRIPT)) {
		printf ("Image %s wrong type\n", aufile[idx]);
		return -1;
	}
	/* special case for prepare.img */
	if (idx == IDX_PREPARE)
		return 0;
	/* recycle checksum */
	checksum = image_get_data_size (hdr);
	/* for kernel and app the image header must also fit into flash */
	if ((idx != IDX_DISK) && (idx != IDX_FIRMWARE))
		checksum += image_get_header_size ();
	/* check the size does not exceed space in flash. HUSH scripts */
	/* all have ausize[] set to 0 */
	if ((ausize[idx] != 0) && (ausize[idx] < checksum)) {
		printf ("Image %s is bigger than FLASH\n", aufile[idx]);
		return -1;
	}
	/* check the time stamp from the EEPROM */
	/* read it in */
	i2c_read_multiple(0x54, auee_off[idx].time, 1, buf, sizeof(buf));
#ifdef CHECK_VALID_DEBUG
	printf ("buf[0] %#x buf[1] %#x buf[2] %#x buf[3] %#x "
		"as int %#x time %#x\n",
		buf[0], buf[1], buf[2], buf[3],
		*((unsigned int *)buf), image_get_time (hdr));
#endif
	/* check it */
	if (*((unsigned int *)buf) >= image_get_time (hdr)) {
		printf ("Image %s is too old\n", aufile[idx]);
		return -1;
	}

	return 0;
}