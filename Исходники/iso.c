// Apply various workarounds to Linux config files
static void fix_config(const char* psz_fullpath, const char* psz_path, const char* psz_basename, EXTRACT_PROPS* props)
{
	size_t i, nul_pos;
	char *iso_label = NULL, *usb_label = NULL, *src, *dst;

	nul_pos = safe_strlen(psz_fullpath);
	src = safe_strdup(psz_fullpath);
	if (src == NULL)
		return;
	for (i=0; i<nul_pos; i++)
		if (src[i] == '/') src[i] = '\\';

	// Workaround for config files requiring an ISO label for kernel append that may be
	// different from our USB label. Oh, and these labels must have spaces converted to \x20.
	if ((props->is_syslinux_cfg) || (props->is_grub_cfg)) {
		iso_label = replace_char(img_report.label, ' ', "\\x20");
		usb_label = replace_char(img_report.usb_label, ' ', "\\x20");
		if ((iso_label != NULL) && (usb_label != NULL)) {
			if (replace_in_token_data(src, (props->is_syslinux_cfg) ? "append" : "linuxefi", iso_label, usb_label, TRUE) != NULL)
				uprintf("  Patched %s: '%s' ⇨ '%s'\n", src, iso_label, usb_label);
		}
		safe_free(iso_label);
		safe_free(usb_label);
	}

	// Fix dual BIOS + EFI support for tails and other ISOs
	if ( (props->is_syslinux_cfg) && (safe_stricmp(psz_path, efi_dirname) == 0) &&
		 (safe_stricmp(psz_basename, syslinux_cfg[0]) == 0) &&
		 (!img_report.has_efi_syslinux) && (dst = safe_strdup(src)) ) {
		dst[nul_pos-12] = 's'; dst[nul_pos-11] = 'y'; dst[nul_pos-10] = 's';
		CopyFileA(src, dst, TRUE);
		uprintf("Duplicated %s to %s\n", src, dst);
		free(dst);
	}

	// Workaround for FreeNAS
	if (props->is_grub_cfg) {
		iso_label = malloc(MAX_PATH);
		usb_label = malloc(MAX_PATH);
		if ((iso_label != NULL) && (usb_label != NULL)) {
			safe_sprintf(iso_label, MAX_PATH, "cd9660:/dev/iso9660/%s", img_report.label);
			safe_sprintf(usb_label, MAX_PATH, "msdosfs:/dev/msdosfs/%s", img_report.usb_label);
			if (replace_in_token_data(src, "set", iso_label, usb_label, TRUE) != NULL)
				uprintf("  Patched %s: '%s' ⇨ '%s'\n", src, iso_label, usb_label);
		}
		safe_free(iso_label);
		safe_free(usb_label);
	}

	free(src);
}