Id
repo_add_deb(Repo *repo, const char *deb, int flags)
{
  Pool *pool = repo->pool;
  Repodata *data;
  unsigned char buf[4096], *bp;
  int l, l2, vlen, clen, ctarlen;
  unsigned char *ctgz;
  unsigned char pkgid[16];
  unsigned char *ctar;
  int gotpkgid;
  FILE *fp;
  Solvable *s;
  struct stat stb;

  data = repo_add_repodata(repo, flags);
  if ((fp = fopen(flags & REPO_USE_ROOTDIR ? pool_prepend_rootdir_tmp(pool, deb) : deb, "r")) == 0)
    {
      pool_error(pool, -1, "%s: %s", deb, strerror(errno));
      return 0;
    }
  if (fstat(fileno(fp), &stb))
    {
      pool_error(pool, -1, "fstat: %s", strerror(errno));
      fclose(fp);
      return 0;
    }
  l = fread(buf, 1, sizeof(buf), fp);
  if (l < 8 + 60 || strncmp((char *)buf, "!<arch>\ndebian-binary   ", 8 + 16) != 0)
    {
      pool_error(pool, -1, "%s: not a deb package", deb);
      fclose(fp);
      return 0;
    }
  vlen = atoi((char *)buf + 8 + 48);
  if (vlen < 0 || vlen > l)
    {
      pool_error(pool, -1, "%s: not a deb package", deb);
      fclose(fp);
      return 0;
    }
  vlen += vlen & 1;
  if (l < 8 + 60 + vlen + 60)
    {
      pool_error(pool, -1, "%s: unhandled deb package", deb);
      fclose(fp);
      return 0;
    }
  if (strncmp((char *)buf + 8 + 60 + vlen, "control.tar.gz  ", 16) != 0)
    {
      pool_error(pool, -1, "%s: control.tar.gz is not second entry", deb);
      fclose(fp);
      return 0;
    }
  clen = atoi((char *)buf + 8 + 60 + vlen + 48);
  if (clen <= 0 || clen >= 0x100000)
    {
      pool_error(pool, -1, "%s: control.tar.gz has illegal size", deb);
      fclose(fp);
      return 0;
    }
  ctgz = solv_calloc(1, clen + 4);
  bp = buf + 8 + 60 + vlen + 60;
  l -= 8 + 60 + vlen + 60;
  if (l > clen)
    l = clen;
  if (l)
    memcpy(ctgz, bp, l);
  if (l < clen)
    {
      if (fread(ctgz + l, clen - l, 1, fp) != 1)
	{
	  pool_error(pool, -1, "%s: unexpected EOF", deb);
	  solv_free(ctgz);
	  fclose(fp);
	  return 0;
	}
    }
  fclose(fp);
  gotpkgid = 0;
  if (flags & DEBS_ADD_WITH_PKGID)
    {
      Chksum *chk = solv_chksum_create(REPOKEY_TYPE_MD5);
      solv_chksum_add(chk, ctgz, clen);
      solv_chksum_free(chk, pkgid);
      gotpkgid = 1;
    }
  if (ctgz[0] != 0x1f || ctgz[1] != 0x8b)
    {
      pool_error(pool, -1, "%s: control.tar.gz is not gzipped", deb);
      solv_free(ctgz);
      return 0;
    }
  if (ctgz[2] != 8 || (ctgz[3] & 0xe0) != 0)
    {
      pool_error(pool, -1, "%s: control.tar.gz is compressed in a strange way", deb);
      solv_free(ctgz);
      return 0;
    }
  bp = ctgz + 4;
  bp += 6;	/* skip time, xflags and OS code */
  if (ctgz[3] & 0x04)
    {
      /* skip extra field */
      l = bp[0] | bp[1] << 8;
      bp += l + 2;
      if (bp >= ctgz + clen)
	{
          pool_error(pool, -1, "%s: control.tar.gz is corrupt", deb);
	  solv_free(ctgz);
	  return 0;
	}
    }
  if (ctgz[3] & 0x08)	/* orig filename */
    while (*bp)
      bp++;
  if (ctgz[3] & 0x10)	/* file comment */
    while (*bp)
      bp++;
  if (ctgz[3] & 0x02)	/* header crc */
    bp += 2;
  if (bp >= ctgz + clen)
    {
      pool_error(pool, -1, "%s: control.tar.gz is corrupt", deb);
      solv_free(ctgz);
      return 0;
    }
  ctar = decompress(bp, ctgz + clen - bp, &ctarlen);
  solv_free(ctgz);
  if (!ctar)
    {
      pool_error(pool, -1, "%s: control.tar.gz is corrupt", deb);
      return 0;
    }
  bp = ctar;
  l = ctarlen;
  while (l > 512)
    {
      int j;
      l2 = 0;
      for (j = 124; j < 124 + 12; j++)
	if (bp[j] >= '0' && bp[j] <= '7')
	  l2 = l2 * 8 + (bp[j] - '0');
      if (!strcmp((char *)bp, "./control") || !strcmp((char *)bp, "control"))
	break;
      l2 = 512 + ((l2 + 511) & ~511);
      l -= l2;
      bp += l2;
    }
  if (l <= 512 || l - 512 - l2 <= 0 || l2 <= 0)
    {
      pool_error(pool, -1, "%s: control.tar.gz contains no control file", deb);
      free(ctar);
      return 0;
    }
  memmove(ctar, bp + 512, l2);
  ctar = solv_realloc(ctar, l2 + 1);
  ctar[l2] = 0;
  s = pool_id2solvable(pool, repo_add_solvable(repo));
  control2solvable(s, data, (char *)ctar);
  if (!(flags & REPO_NO_LOCATION))
    repodata_set_location(data, s - pool->solvables, 0, 0, deb);
  if (S_ISREG(stb.st_mode))
    repodata_set_num(data, s - pool->solvables, SOLVABLE_DOWNLOADSIZE, (unsigned long long)stb.st_size);
  if (gotpkgid)
    repodata_set_bin_checksum(data, s - pool->solvables, SOLVABLE_PKGID, REPOKEY_TYPE_MD5, pkgid);
  solv_free(ctar);
  if (!(flags & REPO_NO_INTERNALIZE))
    repodata_internalize(data);
  return s - pool->solvables;
}