static int Overture_MRG_extract_resource(struct package *pkg,
									struct package_resource *pkg_res)
{
	if (!pkg || !pkg_res)
		return -CUI_EPARA;

	pkg_res->raw_data = malloc(pkg_res->raw_data_length_lo);
	if (!pkg_res->raw_data)
		return -CUI_EMEM;

	if (pkg->ior.io->readvec(&pkg->ior, pkg_res->raw_data, pkg_res->raw_data_length_lo,
		pkg_res->offset_lo, IO_SEEK_SET)) {
			free(pkg_res->raw_data);
			pkg_res->raw_data = NULL;
			return -CUI_EREADVEC;
	}

#if 0	// 体验版
	char *ext = PathFindExtensionA(pkg_res->name);
	if (!ext || (ext[0] != '.') || (ext[1] == '\x0')) {
		if (!memcmp(pkg_res->raw_data, "OggS", 4)) {
			pkg_res->replace_extension = _T(".ogg");
			pkg_res->flags = PKG_RES_FLAG_REEXT;
		} else if (!memcmp(pkg_res->raw_data, "RIFF", 4)) {
			pkg_res->replace_extension = _T(".wav");
			pkg_res->flags = PKG_RES_FLAG_REEXT;
		}
	}
#endif

	return 0;
}