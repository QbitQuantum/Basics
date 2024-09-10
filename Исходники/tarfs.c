void
populate(char *name)
{
	char longname[Maxlongname+1];
	char *nextname = nil;
	long chksum, linkflg, namelen;
	vlong blkno;
	char *fname;
	Fileinf f;
	Hdr *hp;

	tapefile = open(name, OREAD);
	if (tapefile < 0)
		error("Can't open argument file");
	replete = 1;
	hp = &dblock;
	for (blkno = 0; ; blkno++) {
		seek(tapefile, Tblock*blkno, 0);
		if (readn(tapefile, hp->dummy, sizeof hp->dummy) < sizeof hp->dummy)
			break;
		fname = nextname, nextname = nil;
		if(fname == nil || fname[0] == '\0')
			fname = tarname(hp);
		if (fname[0] == '\0')
			break;

		/* crack header */
		f.addr = blkno + 1;
		f.mode = strtoul(hp->mode, 0, 8);
		f.uid  = strtoul(hp->uid, 0, 8);
		f.gid  = strtoul(hp->gid, 0, 8);
		if((uchar)hp->size[0] == 0x80)
			f.size = b8byte(hp->size+3);
		else
			f.size = strtoull(hp->size, 0, 8);
		f.mdate = strtoul(hp->mtime, 0, 8);
		chksum  = strtoul(hp->chksum, 0, 8);
		/* the mode test is ugly but sometimes necessary */
		if (hp->linkflag == LF_DIR || (f.mode&0170000) == 040000 ||
		    strrchr(fname, '\0')[-1] == '/'){
			f.mode |= DMDIR;
			f.size = 0;
		}
		f.mode &= DMDIR | 0777;

		/* make file name safe, canonical and free of . and .. */
		while (fname[0] == '/')		/* don't allow absolute paths */
			++fname;
		cleanname(fname);
		while (strncmp(fname, "../", 3) == 0)
			fname += 3;

		/* reject links */
		linkflg = hp->linkflag == LF_SYMLINK1 ||
			hp->linkflag == LF_SYMLINK2 || hp->linkflag == LF_LINK;
		if (chksum != checksum()){
			fprint(2, "%s: bad checksum on %.28s at offset %lld\n",
				argv0, fname, Tblock*blkno);
			exits("checksum");
		}
		if (linkflg) {
			/*fprint(2, "link %s->%s skipped\n", fname, hp->linkname);*/
			f.size = 0;
		} else if (hp->linkflag == LF_LONGLINK) {
			;
		} else if (hp->linkflag == LF_LONGNAME) {
			namelen = Maxlongname;
			if(f.size < namelen)
				namelen = f.size;
			namelen = readn(tapefile, longname, namelen);
			if(namelen < 0) namelen = 0;
			longname[namelen] = '\0';
			nextname = longname;
		} else {
			/* accept this file */
			f.name = fname;
			if (f.name[0] == '\0')
				fprint(2, "%s: null name skipped\n", argv0);
			else
				poppath(f, 1);
		}
		blkno += (f.size + Tblock - 1)/Tblock;
	}
}