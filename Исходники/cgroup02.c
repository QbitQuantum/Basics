int main(int argc, char **argv)
{
	FILE *cgf;
	bool found_zdtmtstroot = false, found_newroot = false;
	char paux[1024];
	int ret = -1;
	int fd;

	test_init(argc, argv);

	if (mount_and_add(cgname, "prefix", subname))
		goto out;
	if (mount_and_add(cgname2, "prefix", subname)) {
		sprintf(paux, "%s/%s", dirname, cgname);
		umount(paux);
		rmdir(paux);
		goto out;
	}

	sprintf(paux, "%s/%s/prefix", dirname, cgname);
	fd = open(paux, O_DIRECTORY);
	if (fd < 0)
		goto out_umount;

	if (fchmod(fd, 0777) < 0) {
		fail("fchmod");
		goto out_umount;
	}

	test_daemon();
	test_waitsig();

	if (close(fd) < 0) {
		fail("fd didn't survive");
		goto out_umount;
	}

	cgf = fopen("/proc/self/mountinfo", "r");
	if (cgf == NULL) {
		fail("No mountinfo file");
		goto out_umount;
	}

	while (fgets(paux, sizeof(paux), cgf)) {
		char *s;

		s = strstr(paux, cgname);
		if (s && test_exists(paux, "prefix")) {
			found_zdtmtstroot = true;
		}

		s = strstr(paux, cgname2);
		if (s && test_exists(paux, "newroot")) {
			found_newroot = true;
		}
	}

	if (!found_zdtmtstroot) {
		fail("oldroot not rewritten to zdtmtstroot!\n");
		goto out_close;
	}

	if (!found_newroot) {
		fail("oldroot not rewritten to newroot!\n");
		goto out_close;
	}

	pass();
	ret = 0;


out_close:
	fclose(cgf);
out_umount:
	sprintf(paux, "%s/%s", dirname, cgname);
	umount(paux);
	rmdir(paux);

	sprintf(paux, "%s/%s", dirname, cgname2);
	umount(paux);
	rmdir(paux);
out:
	return ret;
}