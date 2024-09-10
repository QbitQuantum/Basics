int start_cache_next_image(void)
{
	cache_image_t *p = NULL;
	cache_image_t tmp;
	t_fs_filetype ft;
	dword free_memory;
	int fid;

	if (avoid_times && curr_times++ < avoid_times) {
//      dbg_printf(d, "%s: curr_times %d avoid time %d", __func__, curr_times, avoid_times);
		return -1;
	}

	free_memory = get_free_mem();

	if (config.scale >= 100) {
		if (free_memory < 8 * 1024 * 1024) {
			return -1;
		}
	} else if (free_memory < 1024 * 1024) {
		return -1;
	}

	cache_lock();

	for (p = ccacher.caches; p != ccacher.caches + ccacher.caches_size; ++p) {
		if (p->status == CACHE_INIT || p->status == CACHE_FAILED) {
			break;
		}
	}

	// if we ecounter FAILED cache, abort the caching, because user will quit when the image shows up
	if (p == ccacher.caches + ccacher.caches_size || p->status == CACHE_FAILED) {
		cache_unlock();
		return 0;
	}

	copy_cache_image(&tmp, p);
	cache_unlock();
	ft = fs_file_get_type(tmp.filename);
	fid = freq_enter_hotzone();

	if (tmp.where == scene_in_dir) {
		char fullpath[PATH_MAX];

		STRCPY_S(fullpath, tmp.archname);
		STRCAT_S(fullpath, tmp.filename);
		tmp.result =
			image_open_archive(fullpath, tmp.archname, ft, &tmp.width,
							   &tmp.height, &tmp.data, &tmp.bgc, tmp.where,
							   &tmp.exif_array);
	} else {
		tmp.result =
			image_open_archive(tmp.filename, tmp.archname, ft, &tmp.width,
							   &tmp.height, &tmp.data, &tmp.bgc, tmp.where,
							   &tmp.exif_array);
	}

	if (tmp.result == 0 && tmp.data != NULL && config.imgbrightness != 100) {
		pixel *t = tmp.data;
		short b = 100 - config.imgbrightness;
		dword i;

		for (i = 0; i < tmp.height * tmp.width; i++) {
			*t = disp_grayscale(*t, 0, 0, 0, b);
			t++;
		}
	}

	freq_leave(fid);

	cache_lock();

	for (p = ccacher.caches; p != ccacher.caches + ccacher.caches_size; ++p) {
		if (p->status == CACHE_INIT || p->status == CACHE_FAILED) {
			break;
		}
	}

	// recheck the first unloaded (and not failed) image, for we haven't locked cache for a while
	if (p == ccacher.caches + ccacher.caches_size || p->status == CACHE_FAILED) {
		free_cache_image(&tmp);
		cache_unlock();
		return 0;
	}

	if (tmp.result == 0) {
		dword memory_used;

		memory_used = tmp.width * tmp.height * sizeof(pixel);

//      dbg_printf(d, "SERVER: Image %u finished loading", (unsigned)tmp.selidx);
//      dbg_printf(d, "%s: Memory usage %uKB", __func__, (unsigned) ccacher.memory_usage / 1024);
		ccacher.memory_usage += memory_used;
		cacher_cleared = false;
		tmp.status = CACHE_OK;
		copy_cache_image(p, &tmp);
		tmp.data = NULL;
		tmp.exif_array = NULL;
		free_cache_image(&tmp);
		curr_times = avoid_times = 0;
	} else if ((tmp.result == 4 || tmp.result == 5)
			   || (tmp.where == scene_in_rar && tmp.result == 6)) {
		// out of memory
		// if unrar throwed a bad_cast exception when run out of memory, result can be 6 also.

		// is memory completely out of memory?
		if (ccacher.memory_usage == 0) {
//          dbg_printf(d, "SERVER: Image %u finished failed(%u), giving up", (unsigned)tmp.selidx, tmp.result);
			tmp.status = CACHE_FAILED;
			copy_cache_image(p, &tmp);
			p->data = NULL;
			p->exif_array = NULL;
		} else {
			// retry later
//          dbg_printf(d, "SERVER: Image %u finished failed(%u), retring", (unsigned)tmp.selidx, tmp.result);
//          dbg_printf(d, "%s: Memory usage %uKB", __func__, (unsigned) ccacher.memory_usage / 1024);
			if (avoid_times) {
				avoid_times *= 2;
			} else {
				avoid_times = 1;
			}

			avoid_times = min(avoid_times, 32767);
			curr_times = 0;
		}

		free_cache_image(&tmp);
	} else {
//      dbg_printf(d, "SERVER: Image %u finished failed(%u)", (unsigned)tmp.selidx, tmp.result);
		tmp.status = CACHE_FAILED;
		copy_cache_image(p, &tmp);
		p->data = NULL;
		p->exif_array = NULL;
		free_cache_image(&tmp);
	}

	cache_unlock();

	return 0;
}