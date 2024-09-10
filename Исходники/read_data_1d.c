int read_data_1d(FILE *fp, int *ncols, int *nlines, double **data){
	struct line_reader lr;
	size_t len;
	char *line;
	int got_first_line = 0;
	*ncols = 0;
	*nlines = 0;
	lr_init(&lr, fp);
	int nlines_alloc = 0;
	while(NULL != (line = next_line(&lr, &len))){
		if(line[0] == '#'){ continue; }
		line[len] = '\0';
		if(!got_first_line){
			char *saveptr;
			char *field;
			field = STRTOK(line, " \t", &saveptr);
			while(NULL != field){
				(*ncols)++;
				field = STRTOK(NULL, " \t", &saveptr);
			}
			
			nlines_alloc = 256;
			*data = (double*)realloc(*data, sizeof(double) * (*ncols) * nlines_alloc);
			
			got_first_line = 1;
		}
		
		if(*nlines >= nlines_alloc){
			nlines_alloc *= 2;
			*data = (double*)realloc(*data, sizeof(double) * (*ncols) * nlines_alloc);
		}
		
		int nf = 0;
		char *saveptr;
		char *field;
		field = STRTOK(line, " \t", &saveptr);
		while(NULL != field && nf < *ncols){
			(*data)[nf+(*nlines)*(*ncols)] = atof(field);
			++nf;
			field = STRTOK(NULL, " \t", &saveptr);
		}
		(*nlines)++;
	}
	if(!feof(fp)){
		return -1;
	}
	lr_free(&lr);
	return 0;
}