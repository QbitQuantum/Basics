SAPI_API SAPI_POST_HANDLER_FUNC(suhosin_rfc1867_post_handler) /* {{{ */
{
	char *boundary, *s = NULL, *boundary_end = NULL, *start_arr = NULL, *array_index = NULL;
	char *lbuf = NULL, *abuf = NULL;
	zend_string *temp_filename = NULL;
	int boundary_len = 0, cancel_upload = 0, is_arr_upload = 0, array_len = 0;
	int64_t total_bytes = 0, max_file_size = 0;
	int skip_upload = 0, anonindex = 0, is_anonymous;
	HashTable *uploaded_files = NULL;
	multipart_buffer *mbuff;
	zval *array_ptr = (zval *) arg;
	int fd = -1;
	zend_llist header;
	void *event_extra_data = NULL;
	unsigned int llen = 0;
	int upload_cnt = INI_INT("max_file_uploads");
	const zend_encoding *internal_encoding = zend_multibyte_get_internal_encoding();
	php_rfc1867_getword_t getword;
	php_rfc1867_getword_conf_t getword_conf;
	php_rfc1867_basename_t _basename;
	zend_long count = 0;

	if (php_rfc1867_encoding_translation() && internal_encoding) {
		getword = php_rfc1867_getword;
		getword_conf = php_rfc1867_getword_conf;
		_basename = php_rfc1867_basename;
	} else {
		getword = php_ap_getword;
		getword_conf = php_ap_getword_conf;
		_basename = php_ap_basename;
	}

	if (SG(post_max_size) > 0 && SG(request_info).content_length > SG(post_max_size)) {
		sapi_module.sapi_error(E_WARNING, "POST Content-Length of " ZEND_LONG_FMT " bytes exceeds the limit of " ZEND_LONG_FMT " bytes", SG(request_info).content_length, SG(post_max_size));
		return;
	}

	/* Get the boundary */
	boundary = strstr(content_type_dup, "boundary");
	if (!boundary) {
		int content_type_len = (int)strlen(content_type_dup);
		char *content_type_lcase = estrndup(content_type_dup, content_type_len);

		php_strtolower(content_type_lcase, content_type_len);
		boundary = strstr(content_type_lcase, "boundary");
		if (boundary) {
			boundary = content_type_dup + (boundary - content_type_lcase);
		}
		efree(content_type_lcase);
	}

	if (!boundary || !(boundary = strchr(boundary, '='))) {
		sapi_module.sapi_error(E_WARNING, "Missing boundary in multipart/form-data POST data");
		return;
	}

	boundary++;
	boundary_len = (int)strlen(boundary);

	if (boundary[0] == '"') {
		boundary++;
		boundary_end = strchr(boundary, '"');
		if (!boundary_end) {
			sapi_module.sapi_error(E_WARNING, "Invalid boundary in multipart/form-data POST data");
			return;
		}
	} else {
		/* search for the end of the boundary */
		boundary_end = strpbrk(boundary, ",;");
	}
	if (boundary_end) {
		boundary_end[0] = '\0';
		boundary_len = boundary_end-boundary;
	}

	/* Initialize the buffer */
	if (!(mbuff = multipart_buffer_new(boundary, boundary_len))) {
		sapi_module.sapi_error(E_WARNING, "Unable to initialize the input buffer");
		return;
	}

	/* Initialize $_FILES[] */
	zend_hash_init(&PG(rfc1867_protected_variables), 8, NULL, NULL, 0);

	ALLOC_HASHTABLE(uploaded_files);
	zend_hash_init(uploaded_files, 8, NULL, free_filename, 0);
	SG(rfc1867_uploaded_files) = uploaded_files;

	if (Z_TYPE(PG(http_globals)[TRACK_VARS_FILES]) != IS_ARRAY) {
		/* php_auto_globals_create_files() might have already done that */
		array_init(&PG(http_globals)[TRACK_VARS_FILES]);
	}

	zend_llist_init(&header, sizeof(mime_header_entry), (llist_dtor_func_t) php_free_hdr_entry, 0);

	if (php_rfc1867_callback != NULL) {
		multipart_event_start event_start;

		event_start.content_length = SG(request_info).content_length;
		if (php_rfc1867_callback(MULTIPART_EVENT_START, &event_start, &event_extra_data) == FAILURE) {
			goto fileupload_done;
		}
	}

	while (!multipart_buffer_eof(mbuff))
	{
		char buff[FILLUNIT];
		char *cd = NULL, *param = NULL, *filename = NULL, *tmp = NULL;
		size_t blen = 0, wlen = 0;
		zend_off_t offset;

		zend_llist_clean(&header);

		if (!multipart_buffer_headers(mbuff, &header)) {
			goto fileupload_done;
		}

		if ((cd = php_mime_get_hdr_value(header, "Content-Disposition"))) {
			char *pair = NULL;
			int end = 0;

			while (isspace(*cd)) {
				++cd;
			}

			while (*cd && (pair = getword(mbuff->input_encoding, &cd, ';')))
			{
				char *key = NULL, *word = pair;

				while (isspace(*cd)) {
					++cd;
				}

				if (strchr(pair, '=')) {
					key = getword(mbuff->input_encoding, &pair, '=');

					if (!strcasecmp(key, "name")) {
						if (param) {
							efree(param);
						}
						param = getword_conf(mbuff->input_encoding, pair);
						if (mbuff->input_encoding && internal_encoding) {
							unsigned char *new_param;
							size_t new_param_len;
							if ((size_t)-1 != zend_multibyte_encoding_converter(&new_param, &new_param_len, (unsigned char *)param, strlen(param), internal_encoding, mbuff->input_encoding)) {
								efree(param);
								param = (char *)new_param;
							}
						}
					} else if (!strcasecmp(key, "filename")) {
						if (filename) {
							efree(filename);
						}
						filename = getword_conf(mbuff->input_encoding, pair);
						if (mbuff->input_encoding && internal_encoding) {
							unsigned char *new_filename;
							size_t new_filename_len;
							if ((size_t)-1 != zend_multibyte_encoding_converter(&new_filename, &new_filename_len, (unsigned char *)filename, strlen(filename), internal_encoding, mbuff->input_encoding)) {
								efree(filename);
								filename = (char *)new_filename;
							}
						}
					}
				}
				if (key) {
					efree(key);
				}
				efree(word);
			}

			/* Normal form variable, safe to read all data into memory */
			if (!filename && param) {
				size_t value_len;
				char *value = multipart_buffer_read_body(mbuff, &value_len);
				size_t new_val_len; /* Dummy variable */

				if (!value) {
					value = estrdup("");
					value_len = 0;
				}

				if (mbuff->input_encoding && internal_encoding) {
					unsigned char *new_value;
					size_t new_value_len;
					if ((size_t)-1 != zend_multibyte_encoding_converter(&new_value, &new_value_len, (unsigned char *)value, value_len, internal_encoding, mbuff->input_encoding)) {
						efree(value);
						value = (char *)new_value;
						value_len = new_value_len;
					}
				}

				if (++count <= PG(max_input_vars) && sapi_module.input_filter(PARSE_POST, param, &value, value_len, &new_val_len)) {
					if (php_rfc1867_callback != NULL) {
						multipart_event_formdata event_formdata;
						size_t newlength = new_val_len;

						event_formdata.post_bytes_processed = SG(read_post_bytes);
						event_formdata.name = param;
						event_formdata.value = &value;
						event_formdata.length = new_val_len;
						event_formdata.newlength = &newlength;
						if (php_rfc1867_callback(MULTIPART_EVENT_FORMDATA, &event_formdata, &event_extra_data) == FAILURE) {
							efree(param);
							efree(value);
							continue;
						}
						new_val_len = newlength;
					}
					safe_php_register_variable(param, value, new_val_len, array_ptr, 0);
				} else {
					if (count == PG(max_input_vars) + 1) {
						php_error_docref(NULL, E_WARNING, "Input variables exceeded " ZEND_LONG_FMT ". To increase the limit change max_input_vars in php.ini.", PG(max_input_vars));
					}

					if (php_rfc1867_callback != NULL) {
						multipart_event_formdata event_formdata;

						event_formdata.post_bytes_processed = SG(read_post_bytes);
						event_formdata.name = param;
						event_formdata.value = &value;
						event_formdata.length = value_len;
						event_formdata.newlength = NULL;
						php_rfc1867_callback(MULTIPART_EVENT_FORMDATA, &event_formdata, &event_extra_data);
					}
				}

				if (!strcasecmp(param, "MAX_FILE_SIZE")) {
#ifdef HAVE_ATOLL
					max_file_size = atoll(value);
#else
					max_file_size = strtoll(value, NULL, 10);
#endif
				}

				efree(param);
				efree(value);
				continue;
			}

			/* If file_uploads=off, skip the file part */
			if (!PG(file_uploads)) {
				skip_upload = 1;
			} else if (upload_cnt <= 0) {
				skip_upload = 1;
				sapi_module.sapi_error(E_WARNING, "Maximum number of allowable file uploads has been exceeded");
			}

			/* Return with an error if the posted data is garbled */
			if (!param && !filename) {
				sapi_module.sapi_error(E_WARNING, "File Upload Mime headers garbled");
				goto fileupload_done;
			}

			if (!param) {
				is_anonymous = 1;
				param = emalloc(MAX_SIZE_ANONNAME);
				snprintf(param, MAX_SIZE_ANONNAME, "%u", anonindex++);
			} else {
				is_anonymous = 0;
			}

			/* New Rule: never repair potential malicious user input */
			if (!skip_upload) {
				long c = 0;
				tmp = param;

				while (*tmp) {
					if (*tmp == '[') {
						c++;
					} else if (*tmp == ']') {
						c--;
						if (tmp[1] && tmp[1] != '[') {
							skip_upload = 1;
							break;
						}
					}
					if (c < 0) {
						skip_upload = 1;
						break;
					}
					tmp++;
				}
				/* Brackets should always be closed */
				if(c != 0) {
					skip_upload = 1;
				}
			}

			total_bytes = cancel_upload = 0;
			temp_filename = NULL;
			fd = -1;

			if (!skip_upload && php_rfc1867_callback != NULL) {
				multipart_event_file_start event_file_start;

				event_file_start.post_bytes_processed = SG(read_post_bytes);
				event_file_start.name = param;
				event_file_start.filename = &filename;
				if (php_rfc1867_callback(MULTIPART_EVENT_FILE_START, &event_file_start, &event_extra_data) == FAILURE) {
					temp_filename = NULL;
					efree(param);
					efree(filename);
					continue;
				}
			}

			if (skip_upload) {
				efree(param);
				efree(filename);
				continue;
			}

			if (filename[0] == '\0') {
#if DEBUG_FILE_UPLOAD
				sapi_module.sapi_error(E_NOTICE, "No file uploaded");
#endif
				cancel_upload = UPLOAD_ERROR_D;
			}

			offset = 0;
			end = 0;

			if (!cancel_upload) {
				/* only bother to open temp file if we have data */
				blen = multipart_buffer_read(mbuff, buff, sizeof(buff), &end);
#if DEBUG_FILE_UPLOAD
				if (blen > 0) {
#else
				/* in non-debug mode we have no problem with 0-length files */
				{
#endif
					fd = php_open_temporary_fd_ex(PG(upload_tmp_dir), "php", &temp_filename, 1);
					upload_cnt--;
					if (fd == -1) {
						sapi_module.sapi_error(E_WARNING, "File upload error - unable to create a temporary file");
						cancel_upload = UPLOAD_ERROR_E;
					}
				}
			}

			while (!cancel_upload && (blen > 0))
			{
				if (php_rfc1867_callback != NULL) {
					multipart_event_file_data event_file_data;

					event_file_data.post_bytes_processed = SG(read_post_bytes);
					event_file_data.offset = offset;
					event_file_data.data = buff;
					event_file_data.length = blen;
					event_file_data.newlength = &blen;
					if (php_rfc1867_callback(MULTIPART_EVENT_FILE_DATA, &event_file_data, &event_extra_data) == FAILURE) {
						cancel_upload = UPLOAD_ERROR_X;
						continue;
					}
				}

				if (PG(upload_max_filesize) > 0 && (zend_long)(total_bytes+blen) > PG(upload_max_filesize)) {
#if DEBUG_FILE_UPLOAD
					sapi_module.sapi_error(E_NOTICE, "upload_max_filesize of " ZEND_LONG_FMT " bytes exceeded - file [%s=%s] not saved", PG(upload_max_filesize), param, filename);
#endif
					cancel_upload = UPLOAD_ERROR_A;
				} else if (max_file_size && ((zend_long)(total_bytes+blen) > max_file_size)) {
#if DEBUG_FILE_UPLOAD
					sapi_module.sapi_error(E_NOTICE, "MAX_FILE_SIZE of " ZEND_LONG_FMT " bytes exceeded - file [%s=%s] not saved", max_file_size, param, filename);
#endif
					cancel_upload = UPLOAD_ERROR_B;
				} else if (blen > 0) {
#ifdef PHP_WIN32
					wlen = write(fd, buff, (unsigned int)blen);
#else
					wlen = write(fd, buff, blen);
#endif

					if (wlen == -1) {
						/* write failed */
#if DEBUG_FILE_UPLOAD
						sapi_module.sapi_error(E_NOTICE, "write() failed - %s", strerror(errno));
#endif
						cancel_upload = UPLOAD_ERROR_F;
					} else if (wlen < blen) {
#if DEBUG_FILE_UPLOAD
						sapi_module.sapi_error(E_NOTICE, "Only %d bytes were written, expected to write %d", wlen, blen);
#endif
						cancel_upload = UPLOAD_ERROR_F;
					} else {
						total_bytes += wlen;
					}
					offset += wlen;
				}

				/* read data for next iteration */
				blen = multipart_buffer_read(mbuff, buff, sizeof(buff), &end);
			}

			if (fd != -1) { /* may not be initialized if file could not be created */
				close(fd);
			}

			if (!cancel_upload && !end) {
#if DEBUG_FILE_UPLOAD
				sapi_module.sapi_error(E_NOTICE, "Missing mime boundary at the end of the data for file %s", filename[0] != '\0' ? filename : "");
#endif
				cancel_upload = UPLOAD_ERROR_C;
			}
#if DEBUG_FILE_UPLOAD
			if (filename[0] != '\0' && total_bytes == 0 && !cancel_upload) {
				sapi_module.sapi_error(E_WARNING, "Uploaded file size 0 - file [%s=%s] not saved", param, filename);
				cancel_upload = 5;
			}
#endif
			if (php_rfc1867_callback != NULL) {
				multipart_event_file_end event_file_end;

				event_file_end.post_bytes_processed = SG(read_post_bytes);
				event_file_end.temp_filename = ZSTR_VAL(temp_filename);
				event_file_end.cancel_upload = cancel_upload;
				if (php_rfc1867_callback(MULTIPART_EVENT_FILE_END, &event_file_end, &event_extra_data) == FAILURE) {
					cancel_upload = UPLOAD_ERROR_X;
				}
			}

			if (cancel_upload) {
				if (temp_filename) {
					if (cancel_upload != UPLOAD_ERROR_E) { /* file creation failed */
						unlink(ZSTR_VAL(temp_filename));
					}
					zend_string_release(temp_filename);
				}
				temp_filename = NULL;
			} else {
				zend_hash_add_ptr(SG(rfc1867_uploaded_files), temp_filename, temp_filename);
			}

			/* is_arr_upload is true when name of file upload field
			 * ends in [.*]
			 * start_arr is set to point to 1st [ */
			is_arr_upload =	(start_arr = strchr(param,'[')) && (param[strlen(param)-1] == ']');

			if (is_arr_upload) {
				array_len = (int)strlen(start_arr);
				if (array_index) {
					efree(array_index);
				}
				array_index = estrndup(start_arr + 1, array_len - 2);
			}

			/* Add $foo_name */
			if (llen < strlen(param) + MAX_SIZE_OF_INDEX + 1) {
				llen = (int)strlen(param);
				lbuf = (char *) safe_erealloc(lbuf, llen, 1, MAX_SIZE_OF_INDEX + 1);
				llen += MAX_SIZE_OF_INDEX + 1;
			}

			if (is_arr_upload) {
				if (abuf) efree(abuf);
				abuf = estrndup(param, strlen(param)-array_len);
				snprintf(lbuf, llen, "%s_name[%s]", abuf, array_index);
			} else {
				snprintf(lbuf, llen, "%s_name", param);
			}

			/* The \ check should technically be needed for win32 systems only where
			 * it is a valid path separator. However, IE in all it's wisdom always sends
			 * the full path of the file on the user's filesystem, which means that unless
			 * the user does basename() they get a bogus file name. Until IE's user base drops
			 * to nill or problem is fixed this code must remain enabled for all systems. */
			s = _basename(internal_encoding, filename);
			if (!s) {
				s = filename;
			}

			if (!is_anonymous) {
				safe_php_register_variable(lbuf, s, strlen(s), NULL, 0);
			}

			/* Add $foo[name] */
			if (is_arr_upload) {
				snprintf(lbuf, llen, "%s[name][%s]", abuf, array_index);
			} else {
				snprintf(lbuf, llen, "%s[name]", param);
			}
			register_http_post_files_variable(lbuf, s, &PG(http_globals)[TRACK_VARS_FILES], 0);
			efree(filename);
			s = NULL;

			/* Possible Content-Type: */
			if (cancel_upload || !(cd = php_mime_get_hdr_value(header, "Content-Type"))) {
				cd = "";
			} else {
				/* fix for Opera 6.01 */
				s = strchr(cd, ';');
				if (s != NULL) {
					*s = '\0';
				}
			}

			/* Add $foo_type */
			if (is_arr_upload) {
				snprintf(lbuf, llen, "%s_type[%s]", abuf, array_index);
			} else {
				snprintf(lbuf, llen, "%s_type", param);
			}
			if (!is_anonymous) {
				safe_php_register_variable(lbuf, cd, strlen(cd), NULL, 0);
			}

			/* Add $foo[type] */
			if (is_arr_upload) {
				snprintf(lbuf, llen, "%s[type][%s]", abuf, array_index);
			} else {
				snprintf(lbuf, llen, "%s[type]", param);
			}
			register_http_post_files_variable(lbuf, cd, &PG(http_globals)[TRACK_VARS_FILES], 0);

			/* Restore Content-Type Header */
			if (s != NULL) {
				*s = ';';
			}
			s = "";

			{
				/* store temp_filename as-is (in case upload_tmp_dir
				 * contains escapeable characters. escape only the variable name.) */
				zval zfilename;

				/* Initialize variables */
				add_protected_variable(param);

				/* if param is of form xxx[.*] this will cut it to xxx */
				if (!is_anonymous) {
					if (temp_filename) {
						ZVAL_STR_COPY(&zfilename, temp_filename);
					} else {
						ZVAL_EMPTY_STRING(&zfilename);
					}
					safe_php_register_variable_ex(param, &zfilename, NULL, 1);
				}

				/* Add $foo[tmp_name] */
				if (is_arr_upload) {
					snprintf(lbuf, llen, "%s[tmp_name][%s]", abuf, array_index);
				} else {
					snprintf(lbuf, llen, "%s[tmp_name]", param);
				}
				add_protected_variable(lbuf);
				if (temp_filename) {
					ZVAL_STR_COPY(&zfilename, temp_filename);
				} else {
					ZVAL_EMPTY_STRING(&zfilename);
				}
				register_http_post_files_variable_ex(lbuf, &zfilename, &PG(http_globals)[TRACK_VARS_FILES], 1);
			}

			{
				zval file_size, error_type;
				int size_overflow = 0;
				char file_size_buf[65];

				ZVAL_LONG(&error_type, cancel_upload);

				/* Add $foo[error] */
				if (cancel_upload) {
					ZVAL_LONG(&file_size, 0);
				} else {
					if (total_bytes > ZEND_LONG_MAX) {
#ifdef PHP_WIN32
						if (_i64toa_s(total_bytes, file_size_buf, 65, 10)) {
							file_size_buf[0] = '0';
							file_size_buf[1] = '\0';
						}
#else
						{
							int __len = snprintf(file_size_buf, 65, "%lld", total_bytes);
							file_size_buf[__len] = '\0';
						}
#endif
						size_overflow = 1;

					} else {
						ZVAL_LONG(&file_size, total_bytes);
					}
				}

				if (is_arr_upload) {
					snprintf(lbuf, llen, "%s[error][%s]", abuf, array_index);
				} else {
					snprintf(lbuf, llen, "%s[error]", param);
				}
				register_http_post_files_variable_ex(lbuf, &error_type, &PG(http_globals)[TRACK_VARS_FILES], 0);

				/* Add $foo_size */
				if (is_arr_upload) {
					snprintf(lbuf, llen, "%s_size[%s]", abuf, array_index);
				} else {
					snprintf(lbuf, llen, "%s_size", param);
				}
				if (!is_anonymous) {
					if (size_overflow) {
						ZVAL_STRING(&file_size, file_size_buf);
					}
					safe_php_register_variable_ex(lbuf, &file_size, NULL, size_overflow);
				}

				/* Add $foo[size] */
				if (is_arr_upload) {
					snprintf(lbuf, llen, "%s[size][%s]", abuf, array_index);
				} else {
					snprintf(lbuf, llen, "%s[size]", param);
				}
				if (size_overflow) {
					ZVAL_STRING(&file_size, file_size_buf);
				}
				register_http_post_files_variable_ex(lbuf, &file_size, &PG(http_globals)[TRACK_VARS_FILES], size_overflow);
			}
			efree(param);
		}
	}

fileupload_done:
	if (php_rfc1867_callback != NULL) {
		multipart_event_end event_end;

		event_end.post_bytes_processed = SG(read_post_bytes);
		php_rfc1867_callback(MULTIPART_EVENT_END, &event_end, &event_extra_data);
	}

	if (lbuf) efree(lbuf);
	if (abuf) efree(abuf);
	if (array_index) efree(array_index);
	zend_hash_destroy(&PG(rfc1867_protected_variables));
	zend_llist_destroy(&header);
	if (mbuff->boundary_next) efree(mbuff->boundary_next);
	if (mbuff->boundary) efree(mbuff->boundary);
	if (mbuff->buffer) efree(mbuff->buffer);
	if (mbuff) efree(mbuff);
}