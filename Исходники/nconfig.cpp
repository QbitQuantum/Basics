int NConfig::open(int how)
{
	if (!fname)
		return NC_ERR_NFILE;
	if (how != NC_O_RO && how != NC_O_RW)
		return NC_ERR_TYPE;
	if (fd > -1)
		close();

	int ff;
	if ((ff = ::open(fname, how)) == -1)
		return NC_ERR_PERM;

	struct stat sbuf;
	fstat(ff, &sbuf);

	if (!sbuf.st_size)
		return NC_ERR_CORRUPT;

#ifdef NO_MAP_SHARED
	if ((data = (char *) mmap(NULL, sbuf.st_size, how == NC_O_RO ? PROT_READ : (PROT_READ|PROT_WRITE), MAP_PRIVATE, ff, 0)) == MAP_FAILED) {
#else
	if ((data = (char *) mmap(NULL, sbuf.st_size, how == NC_O_RO ? PROT_READ : (PROT_READ|PROT_WRITE), MAP_SHARED, ff, 0)) == MAP_FAILED) {
#endif
		::close(ff);
		return NC_ERR_NMEM;
	}
	if (memcmp(((struct nc_sb_s *) data)->magic, NC_SB_MAGIC, 4)) {
		munmap(data, sbuf.st_size);
		::close(ff);
		return NC_ERR_CORRUPT;
	}
	fd = ff;
	omode = how;
	sb = SB;
	lsize = 0;
	cname = strdup("/");

	lockFile(NC_L_RO, TRUE);
	rdir = DE(sb->root);
	unLockFile();
	return NC_ERR_OK;
}

struct nc_de_s *NConfig::getDirEnt(const char *name, struct nc_de_s *cc)
{
	struct nc_de_s *ret = cc ? cc : ((*name == '/') ? rdir : cdir);
	char *c = canonize(name), *can;

	if (!(can = c))
		return ret;
	while (*c) {
		if (!strcmp(c, ".."))
			ret = DE(ret->parent);
		else
			if (strcmp(c, ".")) {
				struct nc_de_s *re = ret;
				int left = 0, right = ret->pages-1, p, r;

				ret = NULL;
				while (left <= right) {
					p = (left + right) / 2;
					r = strcmp(c, data+IDE(re, p)->name);
					if (r < 0) {
						left = p + 1;
						continue;
					}
					if (!r) {
						ret = IDE(re, p);
						break;
					}
					right = p - 1;
				}
			}
		c += strlen(c)+1;
		if (!ret || (*c && ret->type != NC_DIR)) {
			ret = NULL;
			break;
		}
	}
	free(can);
	return ret;
}

char *NConfig::canonize(const char *name)
{
	if (*name == '/')
		name++;
	size_t i = strlen(name);
	char *ret = (char *)calloc(1, i+3);
	memcpy(ret, name, i);
	for (size_t j=0; j<i; j++)
		if (ret[j] == '/')
			ret[j] = 0;
	return ret;
}

void NConfig::lockFile(int type, int force)
{
#ifdef NC_DEBUG_LOCK
	fprintf(stderr, "Lock called type=%d force=%d lock=%d olck=%u\n", type, force, lock, olck);
#endif
	if (lock == NC_L_RO && type == NC_L_RW) {
		fprintf(stderr, "Lock promotion is not possible.\n");
		abort();
	}
	if (lock != NC_L_NONE) {
		olck++;
		return;
	}
	
	struct flock flc = { type == NC_L_RW ? F_WRLCK : F_RDLCK, SEEK_SET, 0, 0, 0 };
	while (fcntl(fd, F_SETLKW, &flc)) {
		sched_yield();
		flc.l_type = type == NC_L_RW ? F_WRLCK : F_RDLCK;
		flc.l_whence = SEEK_SET;
		flc.l_len = flc.l_start = 0;
	}

#ifdef NC_DEBUG_LOCK
	fprintf(stderr, "Locked %u %u %s\n", sb->modtime, update, force ? "forced." : "");
#endif
	if (careful && type == NC_L_RW)
		mprotect(data, sb->size, PROT_READ | PROT_WRITE);
	lock = type;
	olck = 0;
	if (sb->modtime != update || force) {
		// refresh memory mapping
		if (lsize != sb->size) {
			_remap(lsize, sb->size);
			lsize = sb->size;
			chunks = CM(sb->chunk);
		}
		cdir = getDirEnt(cname);
		update = sb->modtime;
	}
}