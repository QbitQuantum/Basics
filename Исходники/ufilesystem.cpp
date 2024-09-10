int wrename(const OsPath& pathnameOld, const OsPath& pathnameNew)
{
	return rename(OsString(pathnameOld).c_str(), OsString(pathnameNew).c_str());
}