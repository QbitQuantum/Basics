int main(int argc,char *argv[]) {
	size_t n = 5;

	int opt;
	while((opt = getopt(argc,argv,"n:")) != -1) {
		switch(opt) {
			case 'n': n = atoi(optarg); break;
			default:
				usage(argv[0]);
		}
	}

	/* open file, if any */
	FILE *in = stdin;
	if(optind < argc) {
		in = fopen(argv[optind],"r");
		if(!in)
			error("Unable to open '%s'",argv[optind]);
	}

	/* check whether we can seek */
	if(fseek(in,0,SEEK_END) < 0) {
		/* remove error that fseek() has set */
		clearerr(in);

		/* no, ok, then the idea is the following:
		 * we don't need to keep all the memory and do a lot of malloc and realloc. it is sufficient
		 * to read the stuff block by block and keep only the last few blocks that contain at least
		 * <n> lines. therefore, we introduce a single-linked-list and reuse the first one if all
		 * others still contain at least <n> lines. this way, we save a lot of memory and time
		 * because we don't need so many heap-allocs/reallocs. */
		size_t lines = 0;
		sReadBuf *buf;
		sReadBuf *prev = NULL;
		sReadBuf *first = NULL;
		do {
			if(first && (lines - first->lines) > n) {
				buf = first;
				lines -= buf->lines;
				first = first->next;
			}
			else {
				buf = (sReadBuf*)malloc(sizeof(sReadBuf));
				if(!buf)
					error("Unable to allocate more memory");
			}

			buf->bytes = fread(buf->buffer,1,BUF_SIZE,in);
			buf->lines = countLines(buf->buffer,buf->bytes);
			lines += buf->lines;
			buf->next = NULL;
			if(prev)
				prev->next = buf;
			else if(first)
				first->next = buf;
			else
				first = buf;
			prev = buf;
		}
		while(buf->bytes > 0);

		/* throw away the first blocks if they are not needed */
		while((lines - first->lines) > n) {
			lines -= first->lines;
			first = first->next;
		}

		/* print out the lines */
		buf = first;
		while(!ferror(stdout) && buf != NULL) {
			for(size_t i = 0; i < buf->bytes; i++) {
				int c = buf->buffer[i];
				if(lines <= n)
					putchar(c);
				if(c == '\n')
					lines--;
			}
			buf = buf->next;
		}
	}
	else {
		/* we can seek, therefore we can do it better. we don't need to search through the whole
		 * file, but can seek to the end and stepwise backwards until we've found enough lines. */
		fpos_t pos;
		if(fgetpos(in,&pos) < 0)
			error("Unable to get file-position");

		/* search backwards until we've found the number of requested lines */
		size_t lines = 0;
		while(!ferror(in) && pos > 0 && lines < n) {
			size_t amount = MIN(BUF_SIZE,pos);
			pos -= amount;
			fseek(in,pos,SEEK_SET);
			for(size_t i = 0; i < amount; i++) {
				int c = fgetc(in);
				if(c == '\n')
					lines++;
			}
		}
		if(ferror(in))
			error("Read failed");

		/* print the lines */
		fseek(in,pos,SEEK_SET);
		int c;
		while((c = fgetc(in)) != EOF) {
			if(lines <= n)
				putchar(c);
			if(c == '\n') {
				if(ferror(stdout))
					break;
				lines--;
			}
		}
	}
	if(ferror(in))
		error("Read failed");
	if(ferror(stdout))
		error("Write failed");

	/* clean up */
	if(optind < argc)
		fclose(in);
	return EXIT_SUCCESS;
}