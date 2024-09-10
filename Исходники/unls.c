int
UnLslR(const FTPCIPtr cip, FTPFileInfoListPtr filp, FTPLineListPtr llp, int serverType)
{
	char curdir[512];
	char line[512];
	int len;
	size_t curdirlen = 0;
	char fname[256];
	char linkto[256];
	char *cp;
	longest_int fsize;
	int ftype;
	time_t ftime, now;
	int thisyear;
	struct tm nowtm;
	int rc;
	FTPLinePtr lp;
	FTPFileInfo fi;
	int linesread = 0;
	int linesconverted = 0;
	size_t maxFileLen = 0;
	size_t maxPlugLen = 0;
	size_t fileLen;
	int plugend;
	int skipdir = 0;
	size_t cwdlen;

	if (Localtime(time(&now), &nowtm) == NULL)
		thisyear = 1970;	/* should never happen */
	else
		thisyear = nowtm.tm_year + 1900;

	curdir[0] = '\0';
	cip->buf[0] = '\0';
	cwdlen = 0;

	InitFileInfoList(filp);
	for (lp = llp->first; lp != NULL; lp = lp->next) {
		len = (int) strlen(STRNCPY(line, lp->line));
		for (cp = line; ; cp++) {
			if ((*cp == '\0') || (!isspace((int) *cp)))
				break;
		}
		if (*cp == '\0') {
			/* Entire line was blank. */
			/* separator line between dirs */
			continue;
		}

		if (serverType == kServerTypeMicrosoftFTP) {
			/* IIS runs on WinNT only, and NT
			 * can use / as a separator rather
			 * that \.  We will convert them
			 * here.
			 */
			for (cp = line; *cp != '\0'; cp++) {
				if (*cp == '\\')
					*cp = '/';
			}
		}

		linesread++;
		rc = UnLslRLine(line, curdir, curdirlen, fname, sizeof(fname), linkto, sizeof(linkto), &ftype, &fsize, &ftime, now, thisyear, &plugend);
		if ((rc < 0) && (serverType == kServerTypeMicrosoftFTP)) {
			rc = UnDosLine(line, curdir, curdirlen, fname, sizeof(fname), &ftype, &fsize, &ftime);
			if (rc == 0) {
				*linkto = '\0';
				plugend = 0;
			}
		}

		if (rc == 0) {
			if (skipdir != 0)
				continue;
			cp = fname + curdirlen;
			if ((cp[0] == '.') && ((cp[1] == '\0') || ((cp[1] == '.') && (cp[2] == '\0'))))
				continue;	/* ignore . and .. */
			linesconverted++;
			cp = fname;
			if ((cp[0] == '.') && ((cp[1] == '/') || (cp[1] == '\\')))
				cp += 2;
			if ((*cp == '/') || (*cp == '\\')) {
				/* Absolute pathnames not allowed unless
				 * they are in the cwd.
				 */
				if (cip->buf[0] == '\0') {
					(void) FTPGetCWD(cip, cip->buf, cip->bufSize);
					cwdlen = strlen(cip->buf);
				}
				/* In root directory (cwdlen == 1), paths
				 * from root are OK.
				 */
				if (cwdlen > 1) {
					if (memcmp(cp, cip->buf, cwdlen) == 0) {
						/* Abs path prefixed with cwd */
						cp += cwdlen;
						if ((*cp == '/') || (*cp == '\\'))
							cp++;
					} else {
						/* Abs path not prefixed with cwd */
						continue;
					}
				}
			}
			if (PathContainsIntermediateDotDotSubDir(cp))
				continue;
			fileLen = strlen(cp);
			if (fileLen > maxFileLen)
				maxFileLen = fileLen;
			fi.relnameLen = fileLen;
			fi.relname = StrDup(cp);
			fi.rname = NULL;
			fi.lname = NULL;
			fi.rlinkto = (linkto[0] == '\0') ? NULL : StrDup(linkto);
			fi.mdtm = ftime;
			fi.size = (longest_int) fsize;
			fi.type = ftype;
			fi.mode = -1;
			if (plugend > 0) {
				fi.plug = (char *) malloc((size_t) plugend + 1);
				if (fi.plug != NULL) {
					(void) memcpy(fi.plug, line, (size_t) plugend);
					fi.plug[plugend] = '\0';
					if ((size_t) plugend > maxPlugLen)
						maxPlugLen = (size_t) plugend;
				}
			} else {
				fi.plug = (char *) malloc(32 + 1);
				if (fi.plug != NULL) {
					(void) strcpy(fi.plug, "----------   1 ftpuser  ftpusers");
					fi.plug[0] = (char) ftype;
					if (32 > maxPlugLen)
						maxPlugLen = (size_t) 32;
				}
			}
			(void) AddFileInfo(filp, &fi);
		} else if ((rc < 0) && (line[len - 1] == ':')) {
			if ((line[0] == '.') && (line[1] == '/')) {
				line[len - 1] = '/';
				(void) memcpy(curdir, line + 2, (size_t) len + 1 - 2);
				curdirlen = (size_t) (len - 2);
			} else if ((line[0] == '.') && (line[1] == '\\')) {
				line[len - 1] = '\\';
				(void) memcpy(curdir, line + 2, (size_t) len + 1 - 2);
				curdirlen = (size_t) (len - 2);
			} else {
				line[len - 1] = '/';
				(void) memcpy(curdir, line, (size_t) len + 1);
				curdirlen = (size_t) len;
			}
			skipdir = 0;
			cp = curdir;
			if ((*cp == '/') || (*cp == '\\')) {
				skipdir = 1;	/* absolute pathnames not allowed */
				if (cip->buf[0] == '\0') {
					(void) FTPGetCWD(cip, cip->buf, cip->bufSize);
					cwdlen = strlen(cip->buf);
				}
				if (cwdlen == 1) {
					/* In root directory, so paths
					 * from root are OK.
					 */
					skipdir = 0;
				} else {
					if (memcmp(cp, cip->buf, cwdlen) == 0) {
						cp += cwdlen;
						if ((*cp == '/') || (*cp == '\\'))
							cp++;
						memmove(curdir, cp, strlen(cp) + 1);
						skipdir = 0;
						cp = curdir;
					}
				}
			}
			if (PathContainsIntermediateDotDotSubDir(cp)) {
				skipdir = 1;
			}
		}
	}

	filp->maxFileLen = maxFileLen;
	filp->maxPlugLen = maxPlugLen;
	if (linesread == 0)
		return (0);
	return ((linesconverted > 0) ? linesconverted : (-1));
}	/* UnLslR */