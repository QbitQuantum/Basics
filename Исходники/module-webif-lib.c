/*
 * function for sending files.
 */
void send_file(FILE *f, char *filename, char *subdir, time_t modifiedheader, uint32_t etagheader, char *extraheader)
{
	int8_t filen = 0;
	int32_t size = 0;
	char *mimetype = "", *result = " ", *allocated = NULL;
	time_t moddate;
	char path[255];
	char *CSS = NULL;
	char *JSCRIPT = NULL;
	char *JQUERY = NULL;
	char *TOUCH_CSS = NULL;
	char *TOUCH_JSCRIPT = NULL;

	if(!strcmp(filename, "CSS"))
	{
		filename = cfg.http_css ? cfg.http_css : "";
		if(subdir && strlen(subdir) > 0)
		{
			filename = tpl_getFilePathInSubdir(cfg.http_tpl ? cfg.http_tpl : "", subdir, "site", ".css", path, 255);
		}
		mimetype = "text/css";
		filen = 1;
	}
	else if(!strcmp(filename, "JS"))
	{
		filename = cfg.http_jscript ? cfg.http_jscript : "";
		if(subdir && strlen(subdir) > 0)
		{
			filename = tpl_getFilePathInSubdir(cfg.http_tpl ? cfg.http_tpl : "", subdir, "oscam", ".js", path, 255);
		}
		mimetype = "text/javascript";
		filen = 2;
	}
	else if(!strcmp(filename, "JQ"))
	{
		if(subdir && strlen(subdir) > 0)
		{
			filename = tpl_getFilePathInSubdir(cfg.http_tpl ? cfg.http_tpl : "", subdir, "jquery", ".js", path, 255);
		}
		mimetype = "text/javascript";
		filen = 3;
	}

	if(strlen(filename) > 0 && file_exists(filename))
	{
		struct stat st;
		stat(filename, &st);
		moddate = st.st_mtime;
		// We need at least size 1 or keepalive gets problems on some browsers...
		if(st.st_size > 0)
		{
			FILE *fp;
			int32_t readen;
			if((fp = fopen(filename, "r")) == NULL) { return; }
			if(!cs_malloc(&allocated, st.st_size + 1))
			{
				send_error500(f);
				fclose(fp);
				return;
			}
			if((readen = fread(allocated, 1, st.st_size, fp)) == st.st_size)
			{
				allocated[readen] = '\0';
			}
			fclose(fp);
		}

		if(filen == 1 && cfg.http_prepend_embedded_css)    // Prepend Embedded CSS
		{
			char separator [255];
			snprintf(separator, 255, "\n/* Beginn embedded CSS File: %s */\n", cfg.http_css);
			char *oldallocated = allocated;
			CSS = tpl_getUnparsedTpl("CSS", 1, "");
			int32_t newsize = strlen(CSS) + strlen(separator) + 2;
			if(oldallocated) { newsize += strlen(oldallocated) + 1; }
			if(!cs_malloc(&allocated, newsize))
			{
				if(oldallocated) { NULLFREE(oldallocated); }
				NULLFREE(CSS);
				send_error500(f);
				return;
			}
			if (CSS){
				snprintf(allocated, newsize, "%s\n%s\n%s", CSS, separator, (oldallocated != NULL ? oldallocated : ""));
			}
			if(oldallocated) { NULLFREE(oldallocated); }
		}

		if(allocated) { result = allocated; }

	}
	else
	{
		CSS = tpl_getUnparsedTpl("CSS", 1, "");
		JSCRIPT = tpl_getUnparsedTpl("JSCRIPT", 1, "");
		JQUERY = tpl_getUnparsedTpl("JQUERY", 1, "");
#ifdef TOUCH
		TOUCH_CSS = tpl_getUnparsedTpl("TOUCH_CSS", 1, "");
		TOUCH_JSCRIPT = tpl_getUnparsedTpl("TOUCH_JSCRIPT", 1, "");

		if(!subdir || strcmp(subdir, TOUCH_SUBDIR)) {
			if( filen == 1 && strlen(CSS)){ result = CSS; }
			else if ( filen == 2 && strlen(JSCRIPT)){ result = JSCRIPT; }
			else if ( filen == 3 && strlen(JQUERY)){ result = JQUERY; }
		} else {
			if( filen == 1 && strlen(TOUCH_CSS)){ result = TOUCH_CSS; }
			else if ( filen == 2 && strlen(TOUCH_JSCRIPT)){ result = TOUCH_JSCRIPT; }
			else if ( filen == 3 && strlen(JQUERY)){ result = JQUERY; }
		}
#else
		if(filen == 1 && strlen(CSS) > 0){ result = CSS;}
		else if(filen == 2 && strlen(JSCRIPT) > 0){result = JSCRIPT;}
		else if(filen == 3 && strlen(JQUERY) > 0){result = JQUERY;}
#endif
		moddate = first_client->login;
	}

	size = strlen(result);

	if((etagheader == 0 && moddate < modifiedheader) || (etagheader > 0 && (uint32_t)crc32(0L, (uchar *)result, size) == etagheader))
	{
		send_header304(f, extraheader);
	}
	else
	{
		send_headers(f, 200, "OK", NULL, mimetype, 1, size, result, 0);
		webif_write(result, f);
	}
	if(allocated) { NULLFREE(allocated); }
	NULLFREE(CSS);
	NULLFREE(JSCRIPT);
	NULLFREE(JQUERY);
	NULLFREE(TOUCH_CSS);
	NULLFREE(TOUCH_JSCRIPT);
}