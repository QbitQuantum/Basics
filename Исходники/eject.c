/*
 * See if device can be mounted by looking in /etc/fstab.
 * If so, set device name and mount point name, and return 1,
 * otherwise return 0.
 */
static int MountableDevice(const char *name, char **mountName, char **deviceName)
{
	FILE *fp;
	char line[1024];
	char s1[1024];
	char s2[1024];
	int rc;

	fp = fopen("/etc/fstab", "r");
	if (fp == NULL) {
/*
 * /etc/fstab may be unreadable in some situations due to passwords in the
 * file.
 */
		return -1;
	}

	while (fgets(line, sizeof(line), fp) != 0) {
		rc = sscanf(line, "%1023s %1023s", s1, s2);
		if (rc >= 2 && s1[0] != '#' && strcmp(s2, name) == 0) {
			FCLOSE(fp);
			*deviceName = estrdup(s1);
			*mountName = estrdup(s2);
			return 1;
		}
	}
	FCLOSE(fp);
	return 0;
}