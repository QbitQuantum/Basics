bool KContentType::load(std::string mimeFile) {
	FILE *fp = fopen(mimeFile.c_str(),"rb");
	if (fp==NULL) {
		return false;
	}
	fclose(fp);
	KXml xml;
	xml.setEvent(this);
	return xml.parseFile(mimeFile);
}