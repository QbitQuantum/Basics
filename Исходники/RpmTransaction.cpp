void RpmTransaction::addToTransactionUpgrade(const StringToStringMap& files)
{
  for (StringToStringMap::const_iterator it = files.begin();it != files.end();it++)
    {
      FD_t fd = Fopen(it->second.c_str(), "r.ufdio");
      if (fd == NULL)
	throw PkgBackEndException("Fopen(" + it->second + ")");
      Header hdr;
      int rc = rpmReadPackageHeader(fd, &hdr, 0, NULL, NULL);
      if (rc != 0)
	throw PkgBackEndException("rpmReadPackageHeader()");
      rc = rpmtransAddPackage(m_ts, hdr, NULL, it->second.c_str(), 1, 0);
      if (rc != 0)
	throw PkgBackEndException("rpmtransAddPackage()");
      headerFree(hdr);
      Fclose(fd);
    }
}