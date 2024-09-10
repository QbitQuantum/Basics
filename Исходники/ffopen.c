FILE *ffopen(const char *filename, const char *mode)
{
    struct opened_file *ptr;
    struct stat stat_buf;  /* test for pipes */
    int is_read_file, i;
    const char *p;

    /* see if is a read/write file */
    is_read_file = 0;
    p = mode;
    while (*p) {
	if (*p++ == 'r') is_read_file = 1;
    }

    if (strcmp(filename,"-") == 0) {
	if (is_read_file) return stdin;
	flush_mode = 1;
	return stdout;
    }

    if (strncmp(filename,"@mem:",5) == 0) {
	fatal_error("option does not suport memory files %s", filename);
    }

    /* see if file has already been opened */
	
    ptr = opened_file_start;
    while (ptr != NULL) {
	if (strcmp(filename,ptr->name) == 0) {
	    if (ptr->usage_count == 0) {			/* reuse of opened file */
		if (is_read_file && !ptr->is_read_file) {	/* was write, now read */
		     i = fflush(ptr->handle);
		     if (i) fprintf(stderr,"WARNING: wgrib2 could not flush %s in write->read\n", ptr->name);
                     fseek(ptr->handle, 0L, SEEK_SET);		/* rewind file */
		}
		ptr->is_read_file = is_read_file;
	    }
	    if (is_read_file != ptr->is_read_file)  {
		fatal_error("ffopen: file can only read or write not both: %s", ptr->name);
	    }
	    (ptr->usage_count)++;
	    return ptr->handle;
	}
	ptr = ptr->next;
    }

    ptr = (struct opened_file *) malloc( sizeof(struct opened_file) );
    if (ptr == NULL) fatal_error("ffopen: memory allocation problem (%s)", filename);
    ptr->name = (char *) malloc(strlen(filename) + 1);
    if (ptr->name == NULL) fatal_error("ffopen: memory allocation problem (%s)", filename);

    strncpy(ptr->name, filename, strlen(filename)+1);
    ptr->is_read_file = is_read_file;
    ptr->usage_count = 1;
    ptr->do_not_close_flag = 1;		// default is not to close file file

    /* check if filename is @tmp:XXX or just XXX */
    if (strlen(filename) > 5 && strncmp(filename, "@tmp:", 5) == 0) {
	if (is_read_file) {
	    /* remove ptr */
	    free(ptr->name);
	    free(ptr);
	    fatal_error("ffopen: creating temporary file for read is not a good idea (%s)", filename);
	}
        ptr->handle = tmpfile();	/* ISO C to generate temporary file */
        if (ptr->handle == NULL) {
	    /* remove ptr */
	    free(ptr->name);
	    free(ptr);
	    fatal_error("ffopen: could not open tmpfile %s", filename);
	}
        /* add ptr to linked list */
        ptr->next = opened_file_start;
        opened_file_start = ptr;
        return ptr->handle;
    }

    /* disk file or pipe */
    ptr->handle = fopen(filename,mode);
    if (ptr->handle == NULL) {
	free(ptr->name);
	free(ptr);
	// fatal_error("ffopen: could not open %s", filename);
	return NULL;
    }

    /* check if output is to a pipe */
    if (is_read_file == 0) {
	if (stat(filename, &stat_buf) == -1) {
	    /* remove ptr */
	    free(ptr->name);
	    free(ptr);
	    fatal_error("ffopen: could not stat file: %s", filename);
	}
        if (S_ISFIFO(stat_buf.st_mode)) {
	    flush_mode  = 1;
	}
    }

    /* add ptr to linked list */
    ptr->next = opened_file_start;
    opened_file_start = ptr;
    return ptr->handle;
}