void main (int argc, char **argv) {
	struct stat f_stat;
	int c, c1, state, i, j, subst, subst1;
	ushort c2;

	fprintf(stderr, "rewrite: Utility for dictionary rewriting the standard input to the standard output\n");
	if (argc!=4) {
		printf("Usage:\nrewrite <alphabet> <info_dic> <comp_dic>");
		exit(1);
	}
	
	fi = fopen(argv[1],"rb");
	memset(codes, 0, 65536*sizeof(int));
	for (letter_count=1; (c=fgetchar(fi))>=' '; letter_count++) {
		if (codes[c] != 0) {
			printf("Duplicated letter in the alphabet! \n");
			exit(1);
		}
		codes[c] = letter_count;
		letters[letter_count]=c;
	}
	fclose(fi);
	

	stat(argv[2],&f_stat);
	fi = fopen(argv[2],"rb");
	infos = malloc(f_stat.st_size);
	fread(infos, 1, f_stat.st_size, fi);
	fclose(fi);
	
	stat(argv[3],&f_stat);
	fi = fopen(argv[3],"rb");
	cells = malloc(f_stat.st_size);
	fread(cells, 1, f_stat.st_size, fi);
	fclose(fi);
	
	
	fi = stdin;  //fopen(argv[4],"rb");
	fo = stdout; //fopen(argv[5],"wb");
		
	state = cell_to_int(0);
	i=0; j=0; subst=-1; subst1=0;

	ushort newline = '\n';
	while (testin(i)!=0) {
		c=testin(j);
		c1 = codes[c];
		if (c1!=0 && cells[state+c1].tc.c==c1) {
			state = cell_to_int(state+c1);
			if (cells[state].tc.c==0) {
				subst = j;
				subst1 = cell_to_int(state);
			}
			j++;
		} else {
			if (subst!=-1) {
				i=subst+1; j=i; state = cell_to_int(0);
				fwrite(infos+subst1,sizeof(ushort),wstrlen(infos+subst1),fo);
				fwrite()
				subst=-1;
			} else {
				c2 = testin(i);
				fwrite(&c2,sizeof(ushort),1,fo); // write char as is to stream
				i++; j=i; state = cell_to_int(0);
			}
		}
	}

		
//	fclose(fi);
//	fclose(fo);				

}	