int createblock(u64_t blocknum) {
	getpath(blocknum);
	int i;
	FILE *block1;
	block1 = fopen(path, "wb");
	char buf[1024];
	//memset(buf, "0", 1024);
	strcpy(buf, "567890");
	for (i = 0; i < 1024 * 16; i++) {
		fwrite(buf, 1024, 1, block1);
	}
	fclose(block1);
	addlist(blocknum);
	return 0;
}