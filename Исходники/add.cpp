void Add::execute(Compress& c, std::istream& input)
{
	c.addFile(Poco::Path(_localPath), Poco::Path(_zipPath), _cm, _cl);
}