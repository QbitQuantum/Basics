void pefree(Pe *pe) {
	int i;
	for (i = 0; i < pe->nsections; i++) {
		RtlFreeAnsiString(ANSI_NAME_STRING(&pe->sect[i]));
	}
	for (i = 0; i < pe->nsymbols; i++) {
		free(pe->symtab[i].name);
	}
	free(pe->symtab);
	free(pe->sect);
	free(pe);
}