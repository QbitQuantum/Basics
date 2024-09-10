void  MTConnectStreamsParser::DumpData(DataDictionary data)
{
	for(DataDictionary::iterator it = data.begin(); it!=data.end(); it++)
	{
		AtlTrace("%s = %s\n", (*it).first.c_str(), (*it).second.c_str());
	}
}