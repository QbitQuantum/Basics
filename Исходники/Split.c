static int
mksplit(const char *file_src, const char *prefix, off_t maxpartsize,
        bool msdos)
{
	int fd_src;
	struct stat st;
	char hash[MD5HASHLEN + 1];
	char *package, *version, *arch;
	int nparts, curpart;
	off_t partsize;
	off_t cur_partsize, last_partsize;
	char *prefixdir = NULL, *msdos_prefix = NULL;
	struct varbuf file_dst = VARBUF_INIT;
	struct varbuf partmagic = VARBUF_INIT;
	struct varbuf partname = VARBUF_INIT;

	fd_src = open(file_src, O_RDONLY);
	if (fd_src < 0)
		ohshite(_("unable to open source file `%.250s'"), file_src);
	if (fstat(fd_src, &st))
		ohshite(_("unable to fstat source file"));
	if (!S_ISREG(st.st_mode))
		ohshit(_("source file `%.250s' not a plain file"), file_src);

	fd_md5(fd_src, hash, -1, "md5hash");
	lseek(fd_src, 0, SEEK_SET);

	/* FIXME: Use libdpkg-deb. */
	package = deb_field(file_src, "Package");
	version = deb_field(file_src, "Version");
	arch = deb_field(file_src, "Architecture");

	partsize = maxpartsize - HEADERALLOWANCE;
	last_partsize = st.st_size % partsize;
	if (last_partsize == 0)
		last_partsize = partsize;
	nparts = (st.st_size + partsize - 1) / partsize;

	setvbuf(stdout, NULL, _IONBF, 0);

	printf(P_("Splitting package %s into %d part: ",
	          "Splitting package %s into %d parts: ", nparts),
	       package, nparts);

	if (msdos) {
		char *t;

		t = m_strdup(prefix);
		prefixdir = m_strdup(dirname(t));
		free(t);

		msdos_prefix = m_strdup(path_basename(prefix));
		prefix = clean_msdos_filename(msdos_prefix);
	}

	for (curpart = 1; curpart <= nparts; curpart++) {
		int fd_dst;

		varbuf_reset(&file_dst);
		/* Generate output filename. */
		if (msdos) {
			char *refname;
			int prefix_max;

			m_asprintf(&refname, "%dof%d", curpart, nparts);
			prefix_max = max(8 - strlen(refname), 0);
			varbuf_printf(&file_dst, "%s/%.*s%.8s.deb",
			              prefixdir, prefix_max, prefix, refname);
			free(refname);
		} else {
			varbuf_printf(&file_dst, "%s.%dof%d.deb",
			              prefix, curpart, nparts);
		}

		if (curpart == nparts)
			cur_partsize = last_partsize;
		else
			cur_partsize = partsize;

		if (cur_partsize > maxpartsize) {
			ohshit(_("Header is too long, making part too long. "
			       "Your package name or version\n"
			       "numbers must be extraordinarily long, "
			       "or something. Giving up.\n"));
		}

		/* Split the data. */
		fd_dst = creat(file_dst.buf, 0644);
		if (fd_dst < 0)
			ohshite(_("unable to open file '%s'"), file_dst.buf);

		/* Write the ar header. */
		dpkg_ar_put_magic(file_dst.buf, fd_dst);

		/* Write the debian-split part. */
		varbuf_printf(&partmagic,
		              "%s\n%s\n%s\n%s\n%jd\n%jd\n%d/%d\n%s\n",
		              SPLITVERSION, package, version, hash,
		              (intmax_t)st.st_size, (intmax_t)partsize,
		              curpart, nparts, arch);
		dpkg_ar_member_put_mem(file_dst.buf, fd_dst, PARTMAGIC,
		                       partmagic.buf, partmagic.used);
		varbuf_reset(&partmagic);

		/* Write the data part. */
		varbuf_printf(&partname, "data.%d", curpart);
		dpkg_ar_member_put_file(file_dst.buf, fd_dst, partname.buf,
		                        fd_src, cur_partsize);
		varbuf_reset(&partname);

		close(fd_dst);

		printf("%d ", curpart);
	}

	varbuf_destroy(&file_dst);
	varbuf_destroy(&partname);
	varbuf_destroy(&partmagic);

	free(prefixdir);
	free(msdos_prefix);

	close(fd_src);

	printf(_("done\n"));

	return 0;
}