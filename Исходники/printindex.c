void
dumpisect(ISect *is)
{
	int j;
	uchar *buf;
	u32int i;
	u64int off;
	IBucket ib;
	IEntry ie;

	buf = emalloc(is->blocksize);
	for(i=0; i<is->blocks; i++){
		off = is->blockbase+(u64int)is->blocksize*i;
		if(readpart(is->part, off, buf, is->blocksize) < 0)
			fprint(2, "read %s at 0x%llux: %r\n", is->part->name, off);
		else{
			unpackibucket(&ib, buf, is->bucketmagic);
			for(j=0; j<ib.n; j++){
				unpackientry(&ie, &ib.data[j*IEntrySize]);
				pie(&ie);
			}
		}
	}
}