int padding_decoder(char *file_name, unsigned long long content_length) {

  int fp_in;
  unsigned long long f_size;

#ifdef _MSC_VER
  struct __stat64 file_stats;
#else  
  struct stat64 file_stats;
#endif

  char file_name_in[256] = "";
  char file_name_out[256] = "";
  char *ptr;
  int retval;

  strcpy(file_name_in, file_name);  
  ptr = strstr(file_name_in, PAD_SUFFIX);

  memcpy(file_name_out, file_name_in, (ptr - file_name_in));

#ifdef _MSC_VER
  fp_in = open((const char*)file_name_in, _O_RDWR | _O_CREAT | _O_BINARY, _S_IREAD | _S_IWRITE);
#else
  fp_in = open64(file_name_in, O_RDWR | O_CREAT, S_IRWXU);
#endif

  if(fp_in == -1) {
    printf("open error: %s\n", file_name_in);
    return -1;
  }

#ifdef _MSC_VER
  _fstat64(fp_in, &file_stats);
#else
  fstat64(fp_in, &file_stats);
#endif

  f_size = file_stats.st_size;

  if(f_size > content_length) {
#ifdef _MSC_VER
    retval = _chsize(fp_in, (long)content_length); /* TODO: 64 bits, how ??? */
#else
	  retval = ftruncate64(fp_in, content_length);
#endif

	  if(retval != 0) {
		  printf("Problem in padding decoding.\n" );
		  close(fp_in);
		  return -1;
	  }
  }

  close(fp_in);
	 
	if(rename(file_name_in, file_name_out) < 0) {

		if(errno == EEXIST) {
			retval = remove(file_name_out);
		
			if(retval == -1) {    
				printf("errno: %i\n", errno);
				fflush(stdout);
				close(fp_in);
				return -1;
			}
		
			if(rename(file_name_in, file_name_out) < 0) {
				printf("rename() error1: %s\n", file_name_in);
				fflush(stdout);
				close(fp_in);
				return -1;
			}
		}
		else {
			printf("rename() error2: %s\n", file_name_in);
			fflush(stdout);
			close(fp_in);
			return -1;
		}
	}

  return 0;
}