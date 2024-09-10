unichar* read_file(U_FILE *f){

	unichar *text = NULL;

	text = (unichar *)malloc(sizeof(unichar));
	if(text==NULL){
		fatal_alloc_error("malloc");
	}
	text[0]='\0';

	int total_read = 0;
	int read;
	do {
		unichar buffer[READ_FILE_BUFFER_SIZE+1];
		memset(buffer,0,sizeof(unichar)*(READ_FILE_BUFFER_SIZE+1));

		int ok=1;

		read = u_fread(buffer,READ_FILE_BUFFER_SIZE,f,&ok);

		total_read += u_strlen(buffer);
		text = (unichar *)realloc(text,sizeof(unichar)*(total_read+1));
		if(text==NULL){
				fatal_alloc_error("realloc");
		}
		u_strcat(text,buffer);

	} while (read == READ_FILE_BUFFER_SIZE);

	text[total_read]='\0';

	return text;
}