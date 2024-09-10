extern u32 fs_zip_to_menu(const char *zipfile, u32 icolor, u32 selicolor, u32 selrcolor, u32 selbcolor)
{
	int fid;
	unzFile unzf;
	t_win_menuitem item;

	if (menu_renew(&g_menu) == NULL) {
		return 0;
	}

	fid = freq_enter_hotzone();
	unzf = unzOpen(zipfile);

	if (unzf == NULL) {
		freq_leave(fid);
		return 0;
	}

	add_parent_to_menu(g_menu, icolor, selicolor, selrcolor, selbcolor);

	if (unzGoToFirstFile(unzf) != UNZ_OK) {
		unzClose(unzf);
		freq_leave(fid);

		return g_menu->size;
	}

	do {
		char fname[PATH_MAX];
		unz_file_info file_info;
		t_fs_filetype ft;
		char t[20];

		if (unzGetCurrentFileInfo(unzf, &file_info, fname, PATH_MAX, NULL, 0, NULL, 0) != UNZ_OK)
			break;

		if (file_info.uncompressed_size == 0)
			continue;

		ft = fs_file_get_type(fname);

		if (ft == fs_filetype_chm || ft == fs_filetype_zip || ft == fs_filetype_rar)
			continue;

		win_menuitem_new(&item);

		item.data = (void *) ft;
		buffer_copy_string(item.compname, fname);

		SPRINTF_S(t, "%u", (unsigned int) file_info.uncompressed_size);
		buffer_copy_string(item.shortname, t);
		filename_to_itemname(&item, fname);
		item.selected = false;
		item.icolor = icolor;
		item.selicolor = selicolor;
		item.selrcolor = selrcolor;
		item.selbcolor = selbcolor;
		item.data3 = file_info.uncompressed_size;
		win_menu_add(g_menu, &item);
	} while (unzGoToNextFile(unzf) == UNZ_OK);

	unzClose(unzf);
	freq_leave(fid);

	return g_menu->size;
}