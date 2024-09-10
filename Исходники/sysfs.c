struct mdinfo *sysfs_read(int fd, char *devnm, unsigned long options)
{
	char fname[PATH_MAX];
	char buf[PATH_MAX];
	char *base;
	char *dbase;
	struct mdinfo *sra;
	struct mdinfo *dev, **devp;
	DIR *dir = NULL;
	struct dirent *de;

	sra = xcalloc(1, sizeof(*sra));
	sysfs_init(sra, fd, devnm);
	if (sra->sys_name[0] == 0) {
		free(sra);
		return NULL;
	}

	sprintf(fname, "/sys/block/%s/md/", sra->sys_name);
	base = fname + strlen(fname);

	sra->devs = NULL;
	if (options & GET_VERSION) {
		strcpy(base, "metadata_version");
		if (load_sys(fname, buf))
			goto abort;
		if (strncmp(buf, "none", 4) == 0) {
			sra->array.major_version =
				sra->array.minor_version = -1;
			strcpy(sra->text_version, "");
		} else if (strncmp(buf, "external:", 9) == 0) {
			sra->array.major_version = -1;
			sra->array.minor_version = -2;
			strcpy(sra->text_version, buf+9);
		} else {
			sscanf(buf, "%d.%d",
			       &sra->array.major_version,
			       &sra->array.minor_version);
			strcpy(sra->text_version, buf);
		}
	}
	if (options & GET_LEVEL) {
		strcpy(base, "level");
		if (load_sys(fname, buf))
			goto abort;
		sra->array.level = map_name(pers, buf);
	}
	if (options & GET_LAYOUT) {
		strcpy(base, "layout");
		if (load_sys(fname, buf))
			goto abort;
		sra->array.layout = strtoul(buf, NULL, 0);
	}
	if (options & GET_DISKS) {
		strcpy(base, "raid_disks");
		if (load_sys(fname, buf))
			goto abort;
		sra->array.raid_disks = strtoul(buf, NULL, 0);
	}
	if (options & GET_DEGRADED) {
		strcpy(base, "degraded");
		if (load_sys(fname, buf))
			goto abort;
		sra->array.failed_disks = strtoul(buf, NULL, 0);
	}
	if (options & GET_COMPONENT) {
		strcpy(base, "component_size");
		if (load_sys(fname, buf))
			goto abort;
		sra->component_size = strtoull(buf, NULL, 0);
		/* sysfs reports "K", but we want sectors */
		sra->component_size *= 2;
	}
	if (options & GET_CHUNK) {
		strcpy(base, "chunk_size");
		if (load_sys(fname, buf))
			goto abort;
		sra->array.chunk_size = strtoul(buf, NULL, 0);
	}
	if (options & GET_CACHE) {
		strcpy(base, "stripe_cache_size");
		if (load_sys(fname, buf))
			/* Probably level doesn't support it */
			sra->cache_size = 0;
		else
			sra->cache_size = strtoul(buf, NULL, 0);
	}
	if (options & GET_MISMATCH) {
		strcpy(base, "mismatch_cnt");
		if (load_sys(fname, buf))
			goto abort;
		sra->mismatch_cnt = strtoul(buf, NULL, 0);
	}
	if (options & GET_SAFEMODE) {
		int scale = 1;
		int dot = 0;
		unsigned i;
		unsigned long msec;
		size_t len;

		strcpy(base, "safe_mode_delay");
		if (load_sys(fname, buf))
			goto abort;

		/* remove a period, and count digits after it */
		len = strlen(buf);
		for (i = 0; i < len; i++) {
			if (dot) {
				if (isdigit(buf[i])) {
					buf[i-1] = buf[i];
					scale *= 10;
				}
				buf[i] = 0;
			} else if (buf[i] == '.') {
				dot=1;
				buf[i] = 0;
			}
		}
		msec = strtoul(buf, NULL, 10);
		msec = (msec * 1000) / scale;
		sra->safe_mode_delay = msec;
	}
	if (options & GET_BITMAP_LOCATION) {
		strcpy(base, "bitmap/location");
		if (load_sys(fname, buf))
			goto abort;
		if (strncmp(buf, "file", 4) == 0)
			sra->bitmap_offset = 1;
		else if (strncmp(buf, "none", 4) == 0)
			sra->bitmap_offset = 0;
		else if (buf[0] == '+')
			sra->bitmap_offset = strtol(buf+1, NULL, 10);
		else
			goto abort;
	}

	if (! (options & GET_DEVS))
		return sra;

	/* Get all the devices as well */
	*base = 0;
	dir = opendir(fname);
	if (!dir)
		goto abort;
	sra->array.spare_disks = 0;

	devp = &sra->devs;
	sra->devs = NULL;
	while ((de = readdir(dir)) != NULL) {
		char *ep;
		if (de->d_ino == 0 ||
		    strncmp(de->d_name, "dev-", 4) != 0)
			continue;
		strcpy(base, de->d_name);
		dbase = base + strlen(base);
		*dbase++ = '/';

		dev = xmalloc(sizeof(*dev));

		/* Always get slot, major, minor */
		strcpy(dbase, "slot");
		if (load_sys(fname, buf)) {
			/* hmm... unable to read 'slot' maybe the device
			 * is going away?
			 */
			strcpy(dbase, "block");
			if (readlink(fname, buf, sizeof(buf)) < 0 &&
			    errno != ENAMETOOLONG) {
				/* ...yup device is gone */
				free(dev);
				continue;
			} else {
				/* slot is unreadable but 'block' link
				 * still intact... something bad is happening
				 * so abort
				 */
				free(dev);
				goto abort;
			}

		}
		strcpy(dev->sys_name, de->d_name);
		dev->disk.raid_disk = strtoul(buf, &ep, 10);
		if (*ep) dev->disk.raid_disk = -1;

		strcpy(dbase, "block/dev");
		if (load_sys(fname, buf)) {
			/* assume this is a stale reference to a hot
			 * removed device
			 */
			free(dev);
			continue;
		}
		sra->array.nr_disks++;
		sscanf(buf, "%d:%d", &dev->disk.major, &dev->disk.minor);

		/* special case check for block devices that can go 'offline' */
		strcpy(dbase, "block/device/state");
		if (load_sys(fname, buf) == 0 &&
		    strncmp(buf, "offline", 7) == 0) {
			free(dev);
			continue;
		}

		/* finally add this disk to the array */
		*devp = dev;
		devp = & dev->next;
		dev->next = NULL;

		if (options & GET_OFFSET) {
			strcpy(dbase, "offset");
			if (load_sys(fname, buf))
				goto abort;
			dev->data_offset = strtoull(buf, NULL, 0);
			strcpy(dbase, "new_offset");
			if (load_sys(fname, buf) == 0)
				dev->new_data_offset = strtoull(buf, NULL, 0);
			else
				dev->new_data_offset = dev->data_offset;
		}
		if (options & GET_SIZE) {
			strcpy(dbase, "size");
			if (load_sys(fname, buf))
				goto abort;
			dev->component_size = strtoull(buf, NULL, 0) * 2;
		}
		if (options & GET_STATE) {
			dev->disk.state = 0;
			strcpy(dbase, "state");
			if (load_sys(fname, buf))
				goto abort;
			if (strstr(buf, "in_sync"))
				dev->disk.state |= (1<<MD_DISK_SYNC);
			if (strstr(buf, "faulty"))
				dev->disk.state |= (1<<MD_DISK_FAULTY);
			if (dev->disk.state == 0)
				sra->array.spare_disks++;
		}
		if (options & GET_ERROR) {
			strcpy(buf, "errors");
			if (load_sys(fname, buf))
				goto abort;
			dev->errors = strtoul(buf, NULL, 0);
		}
	}
	closedir(dir);
	return sra;

 abort:
	if (dir)
		closedir(dir);
	sysfs_free(sra);
	return NULL;
}