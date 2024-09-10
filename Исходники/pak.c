static void write_header(struct pak_file *p, int dir_offset) {	
	struct pak_hdr hdr;
	
	strncpy(hdr.magic, "PACK", 4);
	hdr.offset = dir_offset;
	hdr.length = p->nf * (sizeof *p->dir);
	
	assert(p->f);
	REWIND(p->f);	
	WRITFUN(&hdr, sizeof hdr, 1, p->f);
}