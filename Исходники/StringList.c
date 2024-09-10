int save_StringList(StringList *sl, char *file) {
AtomicFile *f;

	if ((f = openfile(file, "w")) == NULL)
		return -1;

	while(sl != NULL) {
		fprintf(f->f, "%s\n", sl->str);
		sl = sl->next;
	}
	return closefile(f);
}