struct VDir* _vdwOpenDir(struct VDir* vd, const char* path) {
	struct VDirW32* vdw = (struct VDirW32*) vd;
	if (!path) {
		return 0;
	}
	const char* dir = vdw->path;
	size_t size = sizeof(char) * (strlen(path) + strlen(dir) + 2);
	char* combined = malloc(size);
	StringCbPrintfA(combined, size, "%s\\%s", dir, path);

	struct VDir* vd2 = VDirOpen(combined);
	if (!vd2) {
		vd2 = VDirOpenArchive(combined);
	}
	free(combined);
	return vd2;
}