int main(int argc, char *argv[]) {
	pnamestruct pn;
	FILE *fd;
	unsigned int off;
	int len;
	int count = 0;
	char pack[4], *fname = NULL, *pbor  = NULL, *p;

	setbuf(stdin,  NULL);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	fputs("\n"
		"BOR music player v"VER"\n"
		"v0.1 by Luigi Auriemma\n"
		"e-mail: [email protected]\n"
		"web:    aluigi.org\n"
		"v0.2-0.3 by Plombo\n"
		"e-mail: [email protected]\n"
		"web:    lavalit.com\n"
		"\n", stdout);

	if(argc < 2) {
		printf("\n"
			"Usage: %s <file.BOR/PAK> [filename]\n"
			"\n"
			"filename is a part of the bor file you want play\n"
			"use this function for playing a specific file in a PAK archive\n"
			"\n", argv[0]);
		exit(1);
	}

	if(argc > 2) pbor = slashback(argv[2]);
	fname = argv[1];

	MYFOPEN {
		fname = malloc(strlen(argv[1]) + 5);
		if(!fname) std_err();
		p = fname + sprintf(fname, "%s", argv[1]);

		strcpy(p, ".bor");
		MYFOPEN {

			strcpy(p, ".pak");
			MYFOPEN std_err();
		}
	}

	aoinit(NULL);
	printf ("- press Ctrl+Z, Ctrl+D, Ctrl+C, Esc, 'x', or 'q' to exit\n"
			"- press Space to pause or unpause\n"
			"- press Tab or Enter to go to the next song\n"
			"\n");
	if(!fread(pack, 4, 1, fd)) goto quit;
	if(memcmp(pack, "PACK", 4)) {
		if(borplay(fd, fname, 0, -1) >= 0) count = 1;
		goto quit;
	}

	if(fseek(fd, -4, SEEK_END) < 0) std_err();

	if(!fread(&off, 4, 1, fd)) goto quit;
	if(fseek(fd, off, SEEK_SET) < 0) std_err();
	
	
	if (!pbor)
		printf("- playing all music files in %s\n", argv[1]);
	while((len = fread(&pn, 1, sizeof(pn), fd)) > 12) {
		p = strrchr(pn.namebuf, '.');
		
		if((p && !stricmp(p, ".bor")) || (stristr(pn.namebuf, "music"))) {
			if(pbor && !stristr(pn.namebuf, pbor)) goto next;
			count++;
			if(borplay(fd, pn.namebuf, pn.filestart, pn.filesize) < 0) break;
		}

next:
		off += pn.pns_len;
		if(fseek(fd, off, SEEK_SET) < 0) std_err();
	}

quit:
	fclose(fd);
	if(device) {
		ao_shutdown();
	}
	if (count == 0) printf("- no matching files found\n");
	printf("- finished\n");
	return(0);
}