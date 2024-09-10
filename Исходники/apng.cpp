static void writeDat( std::ofstream & os, const std::vector<char> & data ) {
	std::vector<char> cdata( data.size() );
	uLongf len = data.size();
	compress2( (Bytef*)cdata.data(), &len, (const Bytef*)data.data(), data.size(), 9 );
	cdata.resize( len );
	writeChunk( os, "IDAT", cdata );
}