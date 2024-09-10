int NConfig::fromXML(const char *filename, int force)
{
	if (fd < 0)
		return NC_ERR_NFILE;
	if (omode != NC_O_RW)
		return NC_ERR_PERM;
#ifndef HAVE_LIBXML2
	return NC_ERR_NOSUPPORT;
#else
	struct ncParseState state = { noRoot, noRoot, NULL, 0, 0, force, this };
	sh.getEntity = ncXmlGetEntity;
	sh.startElement = ncXmlStartElement;
	sh.endElement = ncXmlEndElement;

	lockFile(NC_L_RW);
	cdir = rdir;
	int ret = ncXmlSAXParseFile(&sh, &state, filename);
	cdir = rdir;
	unLockFile();

	return ret < 0 ? NC_ERR_NVAL : NC_ERR_OK;
#endif /* HAVE_LIBXML2 */
}