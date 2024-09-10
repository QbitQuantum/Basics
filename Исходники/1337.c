void
mod_1337(void)
{
	FILE *f;
	int i, j, nnlines, nchars = 0;
	char c, *act;

	f = fopen(FILENAME_1337, "r");

	while(1) {
		c = getc(f);
		if(feof(f)) break;
		if((i=conv_ind(c)) == -1) goto err;
		if(getc(f)!=':') goto err;
		if(getc(f)!='\n') goto err;

		nnlines = 0;
		conv_tab[i].n = 0;
		do {
			c = getc(f);
			nchars++;
			if(c=='\n') {
				if(nnlines==0)
					conv_tab[i].n++;
				else
					nchars--;
				nnlines++;
			} else {
				nnlines = 0;
			}
		} while(nnlines<2 && !feof(f));
	}

	act = conv_buf = (char *) malloc(nchars*sizeof(char));
	CHECK_MALLOC(conv_buf);
	atexit(conv_buf_free);
	rewind(f);

	while(1) {
		c = getc(f);
		if(feof(f)) break;
		if((i=conv_ind(c)) == -1) goto err; 
		if(getc(f)!=':') goto err;
		if(getc(f)!='\n') goto err;

		conv_tab[i].beg = act;
		for(j=0; j<conv_tab[i].n; j++) {
			while((*act=getc(f)) != '\n')
				act++;
			*act = '\0';
			act++;
		}
		if(getc(f)!='\n' && !feof(f)) goto err;
	}

	fclose(f);
	mod_add(&leet);
	return;
err:
	fclose(f);
	puts("Error loading module \"1337\"");
}