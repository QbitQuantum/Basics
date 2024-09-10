int vzctl2_get_free_envid(unsigned *neweid, const char *dst,
		const char *unused)
{
	int i;
	struct vzctl_conf_simple conf;
	char file[STR_SIZE];
	char lckfile[STR_SIZE];
	char dstlck[PATH_MAX];
	struct stat st;
	int check_ve_private = 0;
	int check_ve_root = 0;
	int check_dst = 0;
	int fail_cnt = 0;
	int fd;
	ctid_t ctid = {};

	vzctl_parse_conf_simple(ctid, GLOBAL_CFG, &conf);

	if (conf.ve_private_orig != NULL && strstr(conf.ve_private_orig, "$VEID"))
		check_ve_private = 1;
	if (conf.ve_root_orig != NULL && strstr(conf.ve_root_orig, "$VEID"))
		check_ve_root = 1;
	if (dst != NULL && strstr(dst, "$VEID")) {
		snprintf(dstlck, sizeof(dstlck), "%s.lck", dst);
		check_dst = 1;
	}

	*neweid = 0;
	for (i = START_ID; i < INT_MAX/2 && fail_cnt < GET_FREE_ENVID_FAIL_MAX; i++) {
		ctid_t ctid = {i, };
		/* Check for VEID.conf */
		vzctl2_get_env_conf_path(ctid, file, sizeof(file));
		if (lstat(file, &st)) {
			if (errno != ENOENT) {
				logger(-1, errno, "Failed to stat %s", file);
				fail_cnt++;
				continue;
			}
		} else
			continue;
		/* lock envid */
		snprintf(lckfile, sizeof(lckfile), "%s.lck", file);
		fd = open(lckfile, O_CREAT|O_EXCL, 0644);
		if (fd == -1) {
			if (errno != EEXIST) {
				fail_cnt++;
				logger(-1, errno, "Failed to create %s", lckfile);
			}
			continue;
		}
		close(fd);

		/* check if PATH(s) exist */
		if ((check_ve_private && !is_dst_free(conf.ve_private_orig, ctid, &fail_cnt)) ||
		    (check_ve_root && !is_dst_free(conf.ve_root_orig, ctid, &fail_cnt)) ||
		    (check_dst &&
			(!is_dst_free(dst, ctid, &fail_cnt) || !is_dst_free(dstlck, ctid, &fail_cnt))))
		{
			/* unlock envid */
			unlink(lckfile);
			continue;
		}
		*neweid = i;
		break;
	}
	vzctl_free_conf_simple(&conf);

	if (*neweid == 0)
		return vzctl_err(-1, 0,  "Failed to get unused Countainer id");

	return 0;
}