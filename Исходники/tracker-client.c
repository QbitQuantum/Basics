int
getremote(char *filename, peer_t *peer, char *range, CURL *curlhandle)
{
#ifdef	TIMEIT
	struct timeval		start_time, end_time;
	unsigned long long	s, e;
#endif
	CURLcode	curlcode;
	struct in_addr	in;
	struct stat	buf;
	FILE		*file;
	useconds_t	stall;
	char		*tempfilename;
	char		*dirfile, *basefile;
	char		url[PATH_MAX];
	char		*dir;
	char		*ptr;

#ifdef	TIMEIT
	gettimeofday(&start_time, NULL);
#endif

	in.s_addr = peer->ip;

#ifdef	DEBUG
	logmsg("getremote: get file (%s) from (%s)\n", filename, inet_ntoa(in));
#endif

	status = HTTP_OK;

	/*
	 * we know the file is not on the local hard disk (because getlocal()
	 * is called before this function), so try to download the file
	 * from a peer
	 */

	/*
	 * first, let's see if the file systems have been formatted. if
	 * so, then copy over all the files that were downloaded in the
	 * first part of the installation (e.g., stage2.img, product.img)
	 * and set up a symbolic link from the ramdisk area to the disk.
	 */
	if (stat("/mnt/sysimage", &buf) == 0) {
		if (stat("/mnt/sysimage/install", &buf) != 0) {
			if (stat("/install", &buf) == 0) 
			{
				system("/usr/bin/cp -R /install /mnt/sysimage");
				system("/usr/bin/rm -rf /install");
			}
			else
			{
				mkdir("/mnt/sysimage/install", 0755);
			}
			symlink("/mnt/sysimage/install", "/install");
		}
	}

#ifdef	TIMEIT
	gettimeofday(&end_time, NULL);
	s = (start_time.tv_sec * 1000000) + start_time.tv_usec;
	e = (end_time.tv_sec * 1000000) + end_time.tv_usec;
	logmsg("getremote:svc time1: %lld usec\n", (e - s));
#endif

	/*
	 * make sure the destination directory exists
	 */
	if ((dir = strdup(filename)) != NULL) {
		if ((ptr = rindex(dir, '/')) != NULL) {
			*ptr = '\0';
			if (stat(dir, &buf) != 0) {
				createdir(dir);
			}
		}

		free(dir);
	}

#ifdef	TIMEIT
	gettimeofday(&end_time, NULL);
	s = (start_time.tv_sec * 1000000) + start_time.tv_usec;
	e = (end_time.tv_sec * 1000000) + end_time.tv_usec;
	logmsg("getremote:svc time2: %lld usec\n", (e - s));
#endif

	if ((dirfile = strdup(filename)) == NULL) {
		logmsg("getremote:strdup failed:errno (%d)\n", errno);
		return(-1);
	}

	if ((basefile = strdup(filename)) == NULL) {
		logmsg("getremote:strdup failed:errno (%d)\n", errno);
		return(-1);
	}

	if ((tempfilename = tempnam(dirname(dirfile), basename(basefile))) ==
			NULL) {
		free(dirfile);
		free(basefile);
		logmsg("getremote:tempnam():failed\n");
		return(-1);
	}

	free(dirfile);
	free(basefile);

	/*
	 * make a 'http://' url and get the file.
	 */
	if ((file = fopen(tempfilename, "w")) == NULL) {
		logmsg("getremote:fopen():failed\n");
		free(tempfilename);
		return(-1);
	}

#ifdef	TIMEIT
	gettimeofday(&end_time, NULL);
	s = (start_time.tv_sec * 1000000) + start_time.tv_usec;
	e = (end_time.tv_sec * 1000000) + end_time.tv_usec;
	logmsg("getremote:svc time3: %lld usec\n", (e - s));
#endif

	/*
	 * tell curl to save it to disk (save it to the file pointed
	 * to by 'file'
	 */
	if ((curlcode = curl_easy_setopt(curlhandle, CURLOPT_WRITEDATA,
			file)) != CURLE_OK) {
		logmsg("getremote:curl_easy_setopt():failed:(%d)\n", curlcode);
		free(tempfilename);
		return(-1);
	}

	if (makeurl("http://", filename, inet_ntoa(in), url, sizeof(url)) != 0){
		logmsg("getremote:makeurl():failed:(%d)", errno);
		free(tempfilename);
		return(-1);
	}

	if (fromip != NULL) {
		free(fromip);
	}
	fromip = strdup(inet_ntoa(in));


	/*
	 * let's check if this is an rpm file or something else
	 */
	int skip = (int)strlen(filename);
	char * suffix = filename + skip - 4 ;
	if ( strcmp(suffix, ".rpm") != 0 ){
	    //this is not an rpm we should calculate the md5sum
	    isRpm = 0;
#ifdef  DEBUG
	    logmsg("getremote:file %s is not an rpm doing md5sum\n", filename);
#endif
	}
	else{
            isRpm = 1;
#ifdef  DEBUG
	    logmsg("getremote:file %s is an rpm\n", filename);
#endif
	}



#ifdef	TIMEIT
	gettimeofday(&end_time, NULL);
	s = (start_time.tv_sec * 1000000) + start_time.tv_usec;
	e = (end_time.tv_sec * 1000000) + end_time.tv_usec;
	logmsg("getremote:svc time4: %lld usec\n", (e - s));
#endif

	stall = 10000;

	while (stall < 1000000) {
		if (downloadfile(curlhandle, url, tempfilename, file, filename) < 0) {
			status = HTTP_NOT_FOUND;
		}
#ifdef	DEBUG
		logmsg("getremote:download status %d : stall %d\n",
			status, stall);
#endif

		if ((status >= HTTP_OK) && (status <= HTTP_MULTI_STATUS)) {
			/*
			 * success. break out of loop
			 */
			break;
		} else {
			logmsg("getremote:downloadfile:failed:url %s\n", url);

			if (peer->state == DOWNLOADING) {
				stall *= 10;
				usleep(stall);	
			} else {
				/*
				 * don't return on failure here. we still need
				 * to do some cleanup
				 */
				status = HTTP_NOT_FOUND;
				break;
			}
		}
	}


#ifdef	TIMEIT
	gettimeofday(&end_time, NULL);
	s = (start_time.tv_sec * 1000000) + start_time.tv_usec;
	e = (end_time.tv_sec * 1000000) + end_time.tv_usec;
	logmsg("getremote:svc time5: %lld usec\n", (e - s));
#endif

	/*
	 * we downloaded the file from a peer, so read it and output it
	 * to stdout
	 */
	if ((status >= HTTP_OK) && (status <= HTTP_MULTI_STATUS)) {
		/*
		 * now do an atomic move
		 */
		if (rename(tempfilename, filename) < 0) {
			logmsg("getremote:rename():failed:(%d)\n", errno);
			free(tempfilename);
			return(-1);
		}
		
		if (outputfile(filename, range) != 0) {
			logmsg("getremote:outputfile():failed:(%d)\n", errno);
			free(tempfilename);
			return(-1);
		}
	} else {
		/*
		 * on a failure, a zero-byte length file will be
		 * left on the disk -- this is because of the fopen().
		 * remove this zero-length file.
		 */
		unlink(filename);
		unlink(tempfilename);
		free(tempfilename);
		return(-1);	
	}

#ifdef	TIMEIT
	gettimeofday(&end_time, NULL);
	s = (start_time.tv_sec * 1000000) + start_time.tv_usec;
	e = (end_time.tv_sec * 1000000) + end_time.tv_usec;
	logmsg("getremote:svc time6: %lld usec\n", (e - s));
#endif

	free(tempfilename);
	return(0);
}