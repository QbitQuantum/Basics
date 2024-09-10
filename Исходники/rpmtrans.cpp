void RpmTransaction::addToTransactionUpgrade(const StringVector& files)
{
  for (StringVector::size_type i = 0;i < files.size();i++)
    {
      FD_t fd = Fopen(files[i].c_str(), "r.ufdio");
      if (fd == NULL)
	RPMSTOP("Fopen()");
      Header hdr;
      int rc = rpmReadPackageHeader(fd, &hdr, 0, NULL, NULL);
      if (rc != 0)
	RPMSTOP("rpmReadPackageHeader()");
      rc = rpmtransAddPackage(m_ts, hdr, NULL, files[i].c_str(), 1, 0);
      if (rc != 0)
	RPMSTOP("rpmtransAddPackage()");
      headerFree(hdr);
      Fclose(fd);
    }
}