char *
win32_ls_file(const char *name, LPWIN32_FIND_DATA file, int remote, int si_units)
{
	int ulen, glen, sz = 0;
	//struct tm *ltime = localtime(&st->st_mtime);
	char *user, *group;
	char buf[1024], mode[11+1], tbuf[12+1], ubuf[11+1], gbuf[11+1];
	char sbuf[FMT_SCALED_STRSIZE];
	SYSTEMTIME now;
	SYSTEMTIME ftime;
	
	time_t mtime = filetime_to_time_t( file->ftLastWriteTime );
	BOOL time_conv_ok = FileTimeToSystemTime( &file->ftLastWriteTime, &ftime);
	struct tm *ltime = localtime( &mtime );
	
    if (!time_conv_ok) {
		error("Failed to convert file time to localtime");
	}
	
	strmode(0644, mode);
	if (!remote) {
		user = user_from_uid(0, 0);
	} else {
		snprintf(ubuf, sizeof ubuf, "%u", 0);
		user = ubuf;
	}
	
	if (!remote) {
		group = group_from_gid(0, 0);
	} else {
		snprintf(gbuf, sizeof gbuf, "%u", 0);
		group = gbuf;
	}
	
	if (time_conv_ok) {
		//now = time(NULL);
		GetSystemTime(&now);
		
		if ( (time_diff(now, ftime) / 10000000ULL) < (365*24*60*60) ) {
		//if (now - (365*24*60*60)/2 < st->st_mtime &&
		  //  now >= st->st_mtime)
			sz = strftime(tbuf, sizeof tbuf, "%b %e %H:%M", ltime);
		} else {
			sz = strftime(tbuf, sizeof tbuf, "%b %e  %Y", ltime);
		}
	}
	if (sz == 0)
		tbuf[0] = '\0';
	ulen = MAX(strlen(user), 8);
	glen = MAX(strlen(group), 8);
	long long size = (file->nFileSizeHigh * (MAXDWORD+1)) + file->nFileSizeLow;
		
	if (si_units) {
		fmt_scaled(size, sbuf);
		snprintf(buf, sizeof buf, "%s %3u %-*s %-*s %8s %s %s", mode,
		    1 /*nlink -- FIXME */, ulen, user, glen, group,
		    sbuf, tbuf, name);
	} else {
		snprintf(buf, sizeof buf, "%s %3u %-*s %-*s %8llu %s %s", mode,
		    1 /*nlink -- FIXME */, ulen, user, glen, group,
		    size, tbuf, name);
	}
	return xstrdup(buf);
}