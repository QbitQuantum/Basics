static int
pkg_open_v2(struct pkg **pkg_p, const char *path,
		struct archive **a, struct archive_entry **ae,
		struct pkg_manifest_key *keys, int flags)
{
	struct pkg_v2_header hdr;
	FILE *fs;
	int fd, ret;

	if (strncmp(path, "-", 2) == 0) {
		fd = STDIN_FILENO;
	}
	else {
		fd = open(path, O_RDONLY);
	}

	memset(&hdr, 0, sizeof(hdr));

	if (fd == -1) {
		if ((flags & PKG_OPEN_TRY) == 0) {
			pkg_emit_error("open(%s): %s", path, strerror(errno));
		}

		return (EPKG_FATAL);
	}

	if (!pkg_is_v2(fd)) {
		return (EPKG_END);
	}

	fs = fdopen(fd, "r");

	if (fs == NULL) {
		if ((flags & PKG_OPEN_TRY) == 0) {
			pkg_emit_error("fdopen(%s): %s", path, strerror(errno));
		}

		return (EPKG_FATAL);
	}

	if ((ret = pkg_open_header_v2(fs, &hdr)) != EPKG_OK) {
		if ((flags & PKG_OPEN_TRY) == 0) {
			pkg_emit_error("bad v2 header in %s: %s", path, strerror(errno));
		}

		return (ret);
	}

	/* If we have signature, we need to check it */
	if (hdr.signature_offset > 0) {
		/* TODO: write signatures check */
	}

	/* Load manifest */
	if ((ret = pkg_read_manifest_v2(fs, pkg_p, keys)) != EPKG_OK) {
		if ((flags & PKG_OPEN_TRY) == 0) {
			pkg_emit_error("bad v2 manifest in %s: %s", path, strerror(errno));
		}

		return (ret);
	}

	if (flags & PKG_OPEN_MANIFEST_COMPACT) {
		return (EPKG_OK);
	}

	/* Read files as well */
	if ((ret = pkg_read_files_v2(fs, *pkg_p, keys)) != EPKG_OK) {
		if (ret != EPKG_END) {
			/* We have some fatal error */

			return (EPKG_FATAL);
		}
	}

	/* If we need files, then go to payload and open archive */
	if (flags & PKG_OPEN_MANIFEST_ONLY) {
		return (EPKG_OK);
	}

	if ((ret = pkg_read_archive_v2(fs, *pkg_p, a, ae)) != EPKG_OK) {
		if (ret != EPKG_END) {
			/* We have some fatal error */

			return (EPKG_FATAL);
		}
	}

	return (ret);
}