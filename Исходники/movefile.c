int
isc_movefile(const char *oldname, const char *newname) {
	return (rename(oldname, newname));
}