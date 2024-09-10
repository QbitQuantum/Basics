void Keep::execute(Compress& c, std::istream& input)
{
	c.addFileRaw(input, _hdr, _hdr.getFileName());
}