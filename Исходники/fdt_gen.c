int encode_file(char *file, char *base_dir, FILE *fp, int *s_id) {

	char fullname[MAX_PATH_LENGTH];
	char fullpath[MAX_PATH_LENGTH];

#ifdef _MSC_VER
	struct __stat64 file_stats;
#else
	struct stat64 file_stats;
#endif
	int i;

	uri_t *uri = NULL;
	char *hostname = NULL;
	alc_session_t *s = get_alc_session(*s_id);
	char *user = NULL;
	char *uri_str = NULL;	
	
#ifdef USE_ZLIB
	int retcode;
	char enc_fullpath[MAX_PATH_LENGTH];

#ifdef _MSC_VER
	struct __stat64 enc_file_stats;
#else
	struct stat64 enc_file_stats;
#endif
#endif

#ifdef USE_OPENSSL
	char *md5 = NULL;
#endif

#ifdef FDT_INST_FEC_OTI_FILE
	div_t div_max_n;
	int max_n;

	div_max_n = div((s->def_max_sblen * (100 + s->def_fec_ratio)), 100);
	max_n = div_max_n.quot;
#endif

	unsigned long long padding_length;

#ifdef _MSC_VER
	user = getenv("USERNAME");
#else
	user = getenv("USER");
#endif

	memset(fullpath, 0, MAX_PATH_LENGTH);

	if(!(strcmp(base_dir, "") == 0)) {
		strcpy(fullpath, base_dir);

#ifdef _MSC_VER
		strcat(fullpath, "\\");
#else
		strcat(fullpath, "/");
#endif
	}

	strcat(fullpath, file);

#ifdef _MSC_VER
	if(_stat64(fullpath, &file_stats) == -1) {
#else
	if(stat64(fullpath, &file_stats) == -1) {
#endif
		printf("Error: %s is not valid file name\n", fullpath);
		fflush(stdout);
		return -1;
	}

	if(file_stats.st_size == 0) {
		printf("Error: file %s size = 0\n", fullpath);
		fflush(stdout);
		return -1;
	}

	hostname = getdnsname();	

	memset(fullname, 0, MAX_PATH_LENGTH);
	strcpy(fullname, file);

	for(i = 0; i < (int)strlen(fullname); i++) {
		if(fullname[i] == '\\') {
			fullname[i] = '/';
		}
	}

	uri = alloc_uri_struct();

	set_uri_scheme(uri, "file");

	if(user != NULL) {
		set_uri_user(uri, user);
	}	

#ifdef HOSTNAME_TO_FDT
	if(hostname != NULL) {
		set_uri_host(uri, hostname);
	}
#endif

	set_uri_path(uri, fullname);

#ifdef _MSC_VER
	fprintf(fp, "\t<File TOI=\"%I64u\"", toi);
#else
	fprintf(fp, "\t<File TOI=\"%llu\"", toi);
#endif

	uri_str = uri_string(uri);
	
	fprintf(fp, "\n\t\t");
	fprintf(fp, "Content-Location=\"%s\"", uri_str);
	
	free(uri_str);
	
	fprintf(fp, "\n\t\t");
	fprintf(fp, "Content-Length=\"%llu\"", file_stats.st_size);

	if(s->encode_content == 0 || s->encode_content == ZLIB_FDT) {
		if(is_enough_source_block_numbers(s->def_max_sblen, s->def_eslen, file_stats.st_size,
								   s->def_fec_enc_id, s->def_fec_inst_id) < 0) {
			printf("Maximum source block length %i too small for the file: %s\n", s->def_max_sblen, file);
			fflush(stdout);
			if(hostname != NULL) {
				free(hostname);
			}
			free_uri(uri);
			return -1;
		}
	}

	if(s->encode_content == PAD_FILES) {
		padding_length = compute_padding_length(file_stats.st_size, s->def_max_sblen, s->def_eslen);

        if(padding_length) {
        	fprintf(fp, "\n\t\t");
        	fprintf(fp, "Content-Encoding=\"%s\"", "pad");

        	fprintf(fp, "\n\t\t");
            fprintf(fp, "Transfer-Length=\"%llu\"", (file_stats.st_size + padding_length));
        }

		if(is_enough_source_block_numbers(s->def_max_sblen, s->def_eslen, (file_stats.st_size + padding_length),
								   s->def_fec_enc_id, s->def_fec_inst_id) < 0) {
			printf("Maximum source block length %i too small for the file: %s\n", s->def_max_sblen, file);
			fflush(stdout);
			if(hostname != NULL) {
				free(hostname);
			}
			free_uri(uri);
			return -1;
		}
	}

#ifdef USE_ZLIB       	
	else if(s->encode_content == ZLIB_FDT_AND_GZIP_FILES) {
                
		retcode = file_gzip_compress(fullpath, "wb");
                                                                                                                                                              
        	if(retcode == 0) {
                	fprintf(fp, "\n\t\t");
                	fprintf(fp, "Content-Encoding=\"%s\"", "gzip");
                                                                                                                                                              
               		memset(enc_fullpath, 0 , MAX_PATH_LENGTH);
                	strcpy(enc_fullpath, fullpath);
                	strcat(enc_fullpath, GZ_SUFFIX);
#ifdef _MSC_VER                                                                                                                                                      
                	if(_stat64(enc_fullpath, &enc_file_stats) == -1) {
#else
                	if(stat64(enc_fullpath, &enc_file_stats) == -1) {
#endif
                        printf("Error: %s is not valid file name\n", enc_fullpath);
                        fflush(stdout);
						if(hostname != NULL) {
							free(hostname);
						}
						free_uri(uri);
                        return -1;
                }

#ifdef USE_OPENSSL
					if(s->calculate_session_size == FALSE) {
					 md5 = file_md5(enc_fullpath);

					 if(md5 == NULL) {
						if(hostname != NULL) {
							free(hostname);
						}
						free_uri(uri);
						return -1;
					 } 
					
					 fprintf(fp, "\n\t\t");
					 fprintf(fp, "Content-MD5=\"%s\"", md5);
					}
#endif
                                                                                                                                                              
					fprintf(fp, "\n\t\t");
					fprintf(fp, "Transfer-Length=\"%llu\"", enc_file_stats.st_size);

					if(is_enough_source_block_numbers(s->def_max_sblen, s->def_eslen, enc_file_stats.st_size,
								   s->def_fec_enc_id, s->def_fec_inst_id) < 0) {
						printf("Maximum source block length %i too small for the file: %s\n", s->def_max_sblen, file);
						fflush(stdout);
						if(hostname != NULL) {
							free(hostname);
						}
						free_uri(uri);
						return -1;
					}
		}
      	}
#endif
	else {

#ifdef USE_OPENSSL
			if(s->calculate_session_size == FALSE) {
			 md5 = file_md5(fullpath);

			 if(md5 == NULL) {
				if(hostname != NULL) {
					free(hostname);
				}
				free_uri(uri);
				return -1;
			 }

			 fprintf(fp, "\n\t\t");
			 fprintf(fp, "Content-MD5=\"%s\"", md5);
			}
#endif
	}
	
#ifdef FDT_INST_FEC_OTI_FILE
	if(!s->use_fec_oti_ext_hdr) {

		fprintf(fp, "\n\t\t");
		fprintf(fp, "FEC-OTI-FEC-Encoding-ID=\"%u\"", s->def_fec_enc_id);

		if(s->def_fec_enc_id >= 128) {
			fprintf(fp, "\n\t\t");
			fprintf(fp, "FEC-OTI-FEC-Instance-ID=\"%u\"", s->def_fec_inst_id);
		}

		if(s->def_fec_enc_id == RS_FEC_ENC_ID) {
			fprintf(fp, "\n\t");
			fprintf(fp, "FEC-OTI-Finite-Field-Parameter=\"%u\"", GF_BITS);
			fprintf(fp, "\n\t");
			fprintf(fp, "FEC-OTI-Number-of-Encoding-Symbols-per-Group=\"%u\"", 1);
		}

		fprintf(fp, "\n\t\t");
		fprintf(fp, "FEC-OTI-Maximum-Source-Block-Length=\"%u\"", s->def_max_sblen);
		fprintf(fp, "\n\t\t");
		fprintf(fp, "FEC-OTI-Encoding-Symbol-Length=\"%u\"", s->def_eslen);

		if(s->def_fec_enc_id == SB_SYS_FEC_ENC_ID) {
			fprintf(fp, "\n\t\t");
			fprintf(fp, "FEC-OTI-Max-Number-of-Encoding-Symbols=\"%u\"", max_n);	
		}
	}
#endif

	fprintf(fp, "/>\n");
	toi++;
	free_uri(uri);

#ifdef USE_OPENSSL
	if(s->calculate_session_size == FALSE) {
		free(md5);
	}
#endif
	
	if(hostname != NULL) {
		free(hostname);
	}

	return 0;
}

/**
 * This is a private function which parses directory to the FDT.
 *
 * @param directory directory to be parsed
 * @param base_dir base directory for file to be parsed to the FDT
 * @param fp file pointer to the generated FDT
 * @param s_id session identifier
 *
 * @return 0 in success, -1 otherwise
 *
 */

int encode_directory(char *directory, char *base_dir, FILE *fp, int *s_id) {

	int result;
	char fullname[MAX_PATH_LENGTH];
	char fullpath[MAX_PATH_LENGTH];

#ifdef _MSC_VER
	struct __stat64 file_stats;
#else
	struct stat64 file_stats;
#endif

	uri_t *uri = NULL;
	char *hostname = NULL;
	alc_session_t *s = NULL;
	char *user = NULL;

#ifdef USE_ZLIB
	int retcode;
	char enc_fullpath[MAX_PATH_LENGTH];
#ifdef _MSC_VER
	struct __stat64 enc_file_stats;
#else
	struct stat64 enc_file_stats;
#endif
#endif

#ifdef USE_OPENSSL
	char *md5 = NULL;
#endif

#ifdef _MSC_VER
	int i;
	char findfile[MAX_PATH_LENGTH + 3];
	HANDLE dirptr = NULL;
	WIN32_FIND_DATA entry;
#else
	struct dirent *entry;
	DIR *dirptr = NULL;
	char findfile[MAX_PATH_LENGTH];
#endif

#ifdef FDT_INST_FEC_OTI_FILE
	div_t div_max_n;
	int max_n;
#endif

	char *uri_str = NULL;

	hostname = getdnsname();

	s = get_alc_session(*s_id);

#ifdef FDT_INST_FEC_OTI_FILE
	div_max_n = div((s->def_max_sblen * (100 + s->def_fec_ratio)), 100);
	max_n = div_max_n.quot;
#endif

#ifdef _MSC_VER
	user = getenv("USERNAME");

	memset(findfile, 0, (MAX_PATH_LENGTH + 3));

	if(!(strcmp(base_dir, "") == 0)) {
		strcpy(findfile, base_dir);
		strcat(findfile, "\\");
	}

	strcat(findfile, directory);
	strcat(findfile, "\\*");
	
	dirptr = FindFirstFile(findfile, &entry);

	if(dirptr == INVALID_HANDLE_VALUE) {
		printf("Error: %s is not valid directory name\n", directory);
		fflush(stdout);
		free(hostname);
		return -1;
	}

	if(!checkpath(entry.cFileName)) {

		memset(fullname, 0 , MAX_PATH_LENGTH);
		strcpy(fullname, directory);

		if(fullname[strlen(fullname) - 1] != '\\') {
			strcat(fullname, "\\");
		}

		strcat(fullname, entry.cFileName);

		for(i = 0; i < (int)strlen(fullname); i++) {
			if(fullname[i] == '\\') {
				fullname[i] = '/';
			}
		}

		if(entry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			result = encode_directory(fullname, base_dir, fp, s_id);

			if(result < 0) {
				free(hostname);
				return -1;
			}
		}
		else {

			memset(fullpath, 0, MAX_PATH_LENGTH);

			if(!(strcmp(base_dir, "") == 0)) {
				strcpy(fullpath, base_dir);
				strcat(fullpath, "\\");
			}

			strcat(fullpath, fullname);

#ifdef _MSC_VER
			if(_stat64(fullpath, &file_stats) == -1) {
#else
			if(stat64(fullpath, &file_stats) == -1) {
#endif
				printf("Error: %s is not valid file name\n", fullpath);
				fflush(stdout);
				free(hostname);
				return -1;
			}		

			if(file_stats.st_size == 0) {
				printf("Error: file %s size = 0\n", fullpath);
				fflush(stdout);
				free(hostname);
				return -1;
			}
			
			uri = alloc_uri_struct();

			set_uri_scheme(uri, "file");

			if(user != NULL) {
				set_uri_user(uri, user);
			}

#ifdef HOSTNAME_TO_FDT
			if(hostname != NULL) {
				set_uri_host(uri, hostname);
			}
#endif

			set_uri_path(uri, fullname);

			fprintf(fp, "\t<File TOI=\"%I64u\"", toi);
			
			uri_str = uri_string(uri);

			fprintf(fp, "\n\t\t");
			fprintf(fp, "Content-Location=\"%s\"", uri_str);

			free(uri_str);
			uri_str = NULL;

			fprintf(fp, "\n\t\t");
			fprintf(fp, "Content-Length=\"%llu\"", file_stats.st_size);

                        if(s->encode_content == PAD_FILES) {

                                if(compute_padding_length(file_stats.st_size, s->def_max_sblen, s->def_eslen)) {
                                        fprintf(fp, "\n\t\t");
                                        fprintf(fp, "Content-Encoding=\"%s\"", "pad"); 

                                        fprintf(fp, "\n\t\t");
                                        fprintf(fp, "Transfer-Length=\"%llu\"", compute_padding_length(file_stats.st_size, s->def_max_sblen, s->def_eslen) + file_stats.st_size);
								}
/* Not possible to use, because padded file is not in the hard disk in the sender side
#ifdef USE_OPENSSL
                                if(s->calculate_session_size == FALSE) {
								 md5 = file_md5(fullpath);

                                 if(md5 == NULL) {
                                	free(hostname);        
                                        free_uri(uri);           
                                        return -1;
                                 }
                              
                                fprintf(fp, "\n\t\t"); 
                                fprintf(fp, "Content-MD5=\"%s\"", md5);
							   }
#endif
*/
                        }
#ifdef USE_ZLIB
			else if(s->encode_content == ZLIB_FDT_AND_GZIP_FILES) {

				retcode = file_gzip_compress(fullpath, "wb");

				if(retcode == 0) {
					
					memset(enc_fullpath, 0 , MAX_PATH_LENGTH);
					strcpy(enc_fullpath, fullpath);
					strcat(enc_fullpath, GZ_SUFFIX);
#ifdef _MSC_VER
					if(_stat64(enc_fullpath, &enc_file_stats) == -1) {
#else
					if(stat64(enc_fullpath, &enc_file_stats) == -1) {
#endif
						printf("Error: %s is not valid file name\n", enc_fullpath);
						fflush(stdout);
						free(hostname);
						free_uri(uri);
						return -1;
					}
					
					fprintf(fp, "\n\t\t");
					fprintf(fp, "Content-Encoding=\"%s\"", "gzip");
				
#ifdef USE_OPENSSL
					if(s->calculate_session_size == FALSE) {
					 md5 = file_md5(enc_fullpath);

					 if(md5 == NULL) {
						free(hostname);
						free_uri(uri);
						return -1;
					 }

					 fprintf(fp, "\n\t\t");
					 fprintf(fp, "Content-MD5=\"%s\"", md5);
				    }
#endif

					fprintf(fp, "\n\t\t");
					fprintf(fp, "Transfer-Length=\"%llu\"", enc_file_stats.st_size);
				}
			}
#endif
			else {
#ifdef USE_OPENSSL
				if(s->calculate_session_size == FALSE) {
				 md5 = file_md5(fullpath);

				 if(md5 == NULL) {
					free(hostname);
					free_uri(uri);
					return -1;
				 }

				 fprintf(fp, "\n\t\t");
				 fprintf(fp, "Content-MD5=\"%s\"", md5);
				}
#endif
			}

#ifdef FDT_INST_FEC_OTI_FILE
			if(!s->use_fec_oti_ext_hdr) {

				fprintf(fp, "\n\t\t");
				fprintf(fp, "FEC-OTI-FEC-Encoding-ID=\"%u\"", s->def_fec_enc_id);

				if(s->def_fec_enc_id >= 128) {
					fprintf(fp, "\n\t\t");
					fprintf(fp, "FEC-OTI-FEC-Instance-ID=\"%u\"", s->def_fec_inst_id);
				}

				if(s->def_fec_enc_id == RS_FEC_ENC_ID) {
					fprintf(fp, "\n\t");
					fprintf(fp, "FEC-OTI-Finite-Field-Parameter=\"%u\"", GF_BITS);
					fprintf(fp, "\n\t");
					fprintf(fp, "FEC-OTI-Number-of-Encoding-Symbols-per-Group=\"%u\"", 1);
				}

				fprintf(fp, "\n\t\t");
				fprintf(fp, "FEC-OTI-Maximum-Source-Block-Length=\"%u\"", s->def_max_sblen);
				fprintf(fp, "\n\t\t");
				fprintf(fp, "FEC-OTI-Encoding-Symbol-Length=\"%u\"", s->def_eslen);

				if(s->def_fec_enc_id == RS_FEC_ENC_ID || s->def_fec_enc_id == SB_SYS_FEC_ENC_ID) {
					fprintf(fp, "\n\t\t");
					fprintf(fp, "FEC-OTI-Max-Number-of-Encoding-Symbols=\"%u\"", max_n);	
				}
			}
#endif

			fprintf(fp, "/>\n");
			
			toi++;
			free_uri(uri);

#ifdef USE_OPENSSL
			free(md5);
			md5 = NULL;
#endif
		}
	}

	while(FindNextFile(dirptr, &entry)) {

		if(checkpath(entry.cFileName)) {
			continue;
		}

		memset(fullname, 0 , MAX_PATH_LENGTH);
		strcpy(fullname, directory);

		if(fullname[strlen(fullname) - 1] != '\\') {
			strcat(fullname, "\\");
		}

		strcat(fullname, entry.cFileName);

		for(i = 0; i < (int)strlen(fullname); i++) {
			if(fullname[i] == '\\') {
				fullname[i] = '/';
			}
		}

		if(entry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			result = encode_directory(fullname, base_dir, fp, s_id);

			if(result < 0) {
				continue;
			}
		}
		else {
	
			memset(fullpath, 0, MAX_PATH_LENGTH);

			if(!(strcmp(base_dir, "") == 0)) {
				strcpy(fullpath, base_dir);
				strcat(fullpath, "\\");
			}

			strcat(fullpath, fullname);

#ifdef _MSC_VER
			if(_stat64(fullpath, &file_stats) == -1) {
#else
			if(stat64(fullpath, &file_stats) == -1) {
#endif
				printf("Error: %s is not valid file name\n", fullpath);
				fflush(stdout);
				continue;
			}

			if(file_stats.st_size == 0) {
				printf("Error: file %s size = 0\n", fullpath);
				fflush(stdout);
				continue;
			}

			uri = alloc_uri_struct();

			set_uri_scheme(uri, "file");

			if(user != NULL) {
				set_uri_user(uri, user);
			}

#ifdef HOSTNAME_TO_FDT
			if(hostname != NULL) {
				set_uri_host(uri, hostname);
			}
#endif

			set_uri_path(uri, fullname);

            fprintf(fp, "\t<File TOI=\"%I64u\"", toi);

			uri_str = uri_string(uri);

			fprintf(fp, "\n\t\t");
			fprintf(fp, "Content-Location=\"%s\"", uri_str);

			free(uri_str);
			uri_str = NULL;

			fprintf(fp, "\n\t\t");
			fprintf(fp, "Content-Length=\"%llu\"", file_stats.st_size);

                        if(s->encode_content == PAD_FILES) {

                                if(compute_padding_length(file_stats.st_size, s->def_max_sblen, s->def_eslen)) {           
                                        fprintf(fp, "\n\t\t");
                                        fprintf(fp, "Content-Encoding=\"%s\"", "pad");

                                        fprintf(fp, "\n\t\t");
                                        fprintf(fp, "Transfer-Length=\"%llu\"", compute_padding_length(file_stats.st_size, s->def_max_sblen, s->def_eslen) + file_stats.st_size);
                                }
                        }
#ifdef USE_ZLIB
			else if(s->encode_content == ZLIB_FDT_AND_GZIP_FILES) {

				retcode = file_gzip_compress(fullpath, "wb");
			
				if(retcode == 0) {

					memset(enc_fullpath, 0 , MAX_PATH_LENGTH);
					strcpy(enc_fullpath, fullpath);
					strcat(enc_fullpath, GZ_SUFFIX);

#ifdef _MSC_VER
					if(_stat64(enc_fullpath, &enc_file_stats) == -1) {
#else
					if(stat64(enc_fullpath, &enc_file_stats) == -1) {
#endif
						printf("Error: %s is not valid file name\n", enc_fullpath);
						fflush(stdout);
						free_uri(uri);
						continue;
					}
					
					fprintf(fp, "\n\t\t");
					fprintf(fp, "Content-Encoding=\"%s\"", "gzip");

#ifdef USE_OPENSSL
					if(s->calculate_session_size == FALSE) {
					 md5 = file_md5(enc_fullpath);

					 if(md5 == NULL) {
						free(hostname);
						free_uri(uri);
						continue;
					 }

					 fprintf(fp, "\n\t\t");
					 fprintf(fp, "Content-MD5=\"%s\"", md5);
					}
#endif

					fprintf(fp, "\n\t\t");
					fprintf(fp, "Transfer-Length=\"%llu\"", enc_file_stats.st_size);
				}
			}
#endif
			else {
#ifdef USE_OPENSSL
				if(s->calculate_session_size == FALSE) {
				 md5 = file_md5(fullpath);

				 if(md5 == NULL) {
					free(hostname);
					free_uri(uri);
					continue;
				 }

				 fprintf(fp, "\n\t\t");
				 fprintf(fp, "Content-MD5=\"%s\"", md5);
				}
#endif
			}
			
#ifdef FDT_INST_FEC_OTI_FILE
			if(!s->use_fec_oti_ext_hdr) {

				fprintf(fp, "\n\t\t");
				fprintf(fp, "FEC-OTI-FEC-Encoding-ID=\"%u\"", s->def_fec_enc_id);

				if(s->def_fec_enc_id >= 128) {
					fprintf(fp, "\n\t\t");
					fprintf(fp, "FEC-OTI-FEC-Instance-ID=\"%u\"", s->def_fec_inst_id);
				}

				if(s->def_fec_enc_id == RS_FEC_ENC_ID) {
					fprintf(fp, "\n\t");
					fprintf(fp, "FEC-OTI-Finite-Field-Parameter=\"%u\"", GF_BITS);	
					fprintf(fp, "\n\t");
					fprintf(fp, "FEC-OTI-Number-of-Encoding-Symbols-per-Group=\"%u\"", 1);
				}

				fprintf(fp, "\n\t\t");
				fprintf(fp, "FEC-OTI-Maximum-Source-Block-Length=\"%u\"", s->def_max_sblen);
				fprintf(fp, "\n\t\t");
				fprintf(fp, "FEC-OTI-Encoding-Symbol-Length=\"%u\"", s->def_eslen);
				
				if(s->def_fec_enc_id == RS_FEC_ENC_ID || s->def_fec_enc_id == SB_SYS_FEC_ENC_ID) {
					fprintf(fp, "\n\t\t");
					fprintf(fp, "FEC-OTI-Max-Number-of-Encoding-Symbols=\"%u\"", max_n);	
				}
			}
#endif

			fprintf(fp, "/>\n");
			
			toi++;
			free_uri(uri);

#ifdef USE_OPENSSL
			if(s->calculate_session_size == FALSE) {
			  free(md5);
			  md5 = NULL;
			}
#endif
		}
	}
	FindClose(dirptr);

#else
	user = getenv("USER");	

	memset(findfile, 0, MAX_PATH_LENGTH);

	if(!(strcmp(base_dir, "") == 0)) {
		strcpy(findfile, base_dir);
		strcat(findfile, "/");
	}

	strcat(findfile, directory);

	dirptr = opendir(findfile);

	if(dirptr == NULL) {
		printf("%s is not valid directory name\n", findfile);
		fflush(stdout);
		free(hostname);
		return -1;
	}

	entry = readdir(dirptr);

	while(entry != NULL) {
		
		if(checkpath(entry->d_name)) {
			entry = readdir(dirptr);
			continue;
		}

		memset(fullname, 0 , MAX_PATH_LENGTH);
		strcpy(fullname, directory);
		
		if(fullname[strlen(fullname) - 1] != '/') {
			strcat(fullname, "/");
		}

		strcat(fullname, entry->d_name);

		memset(fullpath, 0, MAX_PATH_LENGTH);

		if(!(strcmp(base_dir, "") == 0)) {
			strcpy(fullpath, base_dir);
			strcat(fullpath, "/");
		}

		strcat(fullpath, fullname);

		if(stat64(fullpath, &file_stats) == -1) {
			printf("Error: %s is not valid file name\n", fullpath);
			fflush(stdout);
			entry = readdir(dirptr);
			continue;
		}

		if(S_ISDIR(file_stats.st_mode)) {
			result = encode_directory(fullname, base_dir, fp, s_id);

			if(result < 0) {
				entry = readdir(dirptr);
				continue;
			}
		}
		else {	
			if(file_stats.st_size == 0) {
				printf("Error: file %s size = 0\n", fullpath);
				fflush(stdout);
				entry = readdir(dirptr);
				continue;
			}

			uri = alloc_uri_struct();

			set_uri_scheme(uri, "file");

			if(user != NULL) {
				set_uri_user(uri, user);
			}
			
#ifdef HOSTNAME_TO_FDT
			if(hostname != NULL) {
				set_uri_host(uri, hostname);
			}
#endif

			set_uri_path(uri, fullname);

			fprintf(fp, "\t<File TOI=\"%llu\"", toi);

			uri_str = uri_string(uri);

			fprintf(fp, "\n\t\t");
			fprintf(fp, "Content-Location=\"%s\"", uri_str);

			free(uri_str);
			uri_str = NULL;

			fprintf(fp, "\n\t\t");
			fprintf(fp, "Content-Length=\"%llu\"", file_stats.st_size);

                        if(s->encode_content == PAD_FILES) {

                                if(compute_padding_length(file_stats.st_size, s->def_max_sblen, s->def_eslen)) {           
                                        fprintf(fp, "\n\t\t");
                                        fprintf(fp, "Content-Encoding=\"%s\"", "pad");

                                        fprintf(fp, "\n\t\t");
                                        fprintf(fp, "Transfer-Length=\"%llu\"", compute_padding_length(file_stats.st_size, s->def_max_sblen, s->def_eslen) + file_stats.st_size);
                                }
                        }
#ifdef USE_ZLIB
			else if(s->encode_content == ZLIB_FDT_AND_GZIP_FILES) {
                                                                                                                                              
				retcode = file_gzip_compress(fullpath, "wb");
                                                                                                                                          
				if(retcode == 0) {
					
					memset(enc_fullpath, 0 , MAX_PATH_LENGTH);
					strcpy(enc_fullpath, fullpath);
					strcat(enc_fullpath, GZ_SUFFIX);
                                                                                                                                      
					if(stat64(enc_fullpath, &enc_file_stats) == -1) {
						printf("Error: %s is not valid file name\n", enc_fullpath);
						fflush(stdout);
						entry = readdir(dirptr);
						free_uri(uri);
						continue;
					}

					fprintf(fp, "\n\t\t");
					fprintf(fp, "Content-Encoding=\"%s\"", "gzip");					
#ifdef USE_OPENSSL
					if(s->calculate_session_size == FALSE) {
					 md5 = file_md5(enc_fullpath);

					 if(md5 == NULL) {
						free_uri(uri);
						continue;
					 }
					
					 fprintf(fp, "\n\t\t");
					 fprintf(fp, "Content-MD5=\"%s\"", md5);
					}
#endif
                
					fprintf(fp, "\n\t\t");
					fprintf(fp, "Transfer-Length=\"%llu\"", enc_file_stats.st_size);
				}
			}
#endif
			else {

#ifdef USE_OPENSSL
				if(s->calculate_session_size == FALSE) {
				 md5 = file_md5(fullpath);

				 if(md5 == NULL) {
					free_uri(uri);
					continue;
				 }

				 fprintf(fp, "\n\t\t");
				 fprintf(fp, "Content-MD5=\"%s\"", md5);
				}
#endif
			}
			
#ifdef FDT_INST_FEC_OTI_FILE
			if(!s->use_fec_oti_ext_hdr) {

				fprintf(fp, "\n\t\t");
				fprintf(fp, "FEC-OTI-FEC-Encoding-ID=\"%u\"", s->def_fec_enc_id);

				if(s->def_fec_enc_id >= 128) {
					fprintf(fp, "\n\t\t");
					fprintf(fp, "FEC-OTI-FEC-Instance-ID=\"%u\"", s->def_fec_inst_id);
				}

				if(s->def_fec_enc_id == RS_FEC_ENC_ID) {
					fprintf(fp, "\n\t");
					fprintf(fp, "FEC-OTI-Finite-Field-Parameter=\"%u\"", GF_BITS);	
					fprintf(fp, "\n\t");
					fprintf(fp, "FEC-OTI-Number-of-Encoding-Symbols-per-Group=\"%u\"", 1);
				}

				fprintf(fp, "\n\t\t");
				fprintf(fp, "FEC-OTI-Maximum-Source-Block-Length=\"%u\"", s->def_max_sblen);
				fprintf(fp, "\n\t\t");
				fprintf(fp, "FEC-OTI-Encoding-Symbol-Length=\"%u\"", s->def_eslen);

				if(s->def_fec_enc_id == RS_FEC_ENC_ID || s->def_fec_enc_id == SB_SYS_FEC_ENC_ID) {
					fprintf(fp, "\n\t\t");
					fprintf(fp, "FEC-OTI-Max-Number-of-Encoding-Symbols=\"%u\"", max_n);	
				}
			}
#endif

			fprintf(fp, "/>\n");
			
			toi++;
			free_uri(uri);

#ifdef USE_OPENSSL
			if(s->calculate_session_size == FALSE) {
			 free(md5);
			 md5 = NULL;
			}
#endif
		}
		entry = readdir(dirptr);
	}
	closedir(dirptr);

#endif
	
	if(hostname != NULL) {
		free(hostname);
	}

	if(toi == 1) {
		return -1;
	}

	return 0;
}

int generate_fdt(char *file_token, char *base_dir, int *s_id, char *fdt_file_name,
				 int complete_fdt, int verbosity) {
  int result;
  FILE *fp;
  
#ifdef _MSC_VER
  struct __stat64 file_stats;
#else
  struct stat64 file_stats;
#endif
  alc_session_t *s = NULL;
  char fullpath[MAX_PATH_LENGTH];
  
#ifdef FDT_INST_FEC_OTI_COMMON
  div_t div_max_n;
  int max_n;
#endif

  char *token;
  
  if((fp = fopen(fdt_file_name, "wb")) == NULL) {
    printf("Error: unable to create fdtfile %s\n", fdt_file_name);
    fflush(stdout);
    return -1;
  }
  
  s = get_alc_session(*s_id);
  
#ifdef FDT_INST_FEC_OTI_COMMON
  div_max_n = div((s->def_max_sblen * (100 + s->def_fec_ratio)), 100);
  max_n = div_max_n.quot;
#endif
  
  toi = 1;
  
  fprintf(fp, "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n");
  fprintf(fp, "<FDT-Instance ");
  
#ifdef _MSC_VER
  if(s->stoptime == 0) {
    /* session is not bounded, set 64bits max value */
    fprintf(fp, "Expires=\"%I64u\"", (unsigned long long)0xFFFFFFFFFFFFFFFF);
  }
  else {
    fprintf(fp, "Expires=\"%I64u\"", s->stoptime);
  }
#else
  if(s->stoptime == 0) {
    /* session is not bounded, set 64bits max value */
    fprintf(fp, "Expires=\"%llu\"", 0xFFFFFFFFFFFFFFFFULL);
  }
  else {
    fprintf(fp, "Expires=\"%llu\"", s->stoptime);
  }
#endif
  
  if(complete_fdt > 0) {
    fprintf(fp, "\n\t");
    fprintf(fp, "Complete=\"true\"");
  }
  
#ifdef FDT_INST_FEC_OTI_COMMON
  if(!s->use_fec_oti_ext_hdr) {
    
    fprintf(fp, "\n\t");
    fprintf(fp, "FEC-OTI-FEC-Encoding-ID=\"%u\"", s->def_fec_enc_id);
    
    if(s->def_fec_enc_id >= 128) {
      fprintf(fp, "\n\t");
      fprintf(fp, "FEC-OTI-FEC-Instance-ID=\"%u\"", s->def_fec_inst_id);
    }
    
    if(s->def_fec_enc_id == RS_FEC_ENC_ID) {
      fprintf(fp, "\n\t");
      fprintf(fp, "FEC-OTI-Finite-Field-Parameter=\"%u\"", GF_BITS);
      fprintf(fp, "\n\t");
      fprintf(fp, "FEC-OTI-Number-of-Encoding-Symbols-per-Group=\"%u\"", 1);
    }
    
    fprintf(fp, "\n\t");
    fprintf(fp, "FEC-OTI-Maximum-Source-Block-Length=\"%u\"", s->def_max_sblen);
    fprintf(fp, "\n\t");
    fprintf(fp, "FEC-OTI-Encoding-Symbol-Length=\"%u\"", s->def_eslen);
    
    if(s->def_fec_enc_id == RS_FEC_ENC_ID || s->def_fec_enc_id == SB_SYS_FEC_ENC_ID) {
      fprintf(fp, "\n\t");
      fprintf(fp, "FEC-OTI-Max-Number-of-Encoding-Symbols=\"%u\"", max_n);
    }
  }
#endif
  
  fprintf(fp, ">\n");

  token = strtok(file_token, ",");

  while(token != NULL) {

    memset(fullpath, 0, (MAX_PATH_LENGTH));
    
    if(!(strcmp(base_dir, "") == 0)) {
      strcpy(fullpath, base_dir);
      
#ifdef _MSC_VER
      strcat(fullpath, "\\");
#else
      strcat(fullpath, "/");
#endif
    }
    
    strcat(fullpath, token);
#ifdef _MSC_VER
    if(_stat64(fullpath, &file_stats) == -1) {
#else
    if(stat64(fullpath, &file_stats) == -1) {
#endif
      printf("Error: %s is not valid file name\n", fullpath);
      fflush(stdout);
      return -1;
    }

    if(file_stats.st_mode & S_IFDIR) {
      result = encode_directory(token, base_dir, fp, s_id);
    }
    else {
      result = encode_file(token, base_dir, fp, s_id);
    }

    if(result < 0) {
      fclose(fp);
      remove(fdt_file_name);
      return -1;
    }

    token = strtok(NULL, ",");
  }
    
  fprintf(fp, "</FDT-Instance>\n");
    
  if(verbosity == 4) {
    printf("File: %s created\n", fdt_file_name);
  }
  
  fclose(fp);
  
  return 0;
}