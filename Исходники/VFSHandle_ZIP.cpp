unsigned char * VFSHandle_ZIP::Read(unsigned int &length)
{
	LocalFileHeader *lfh = m_lfh[m_fileid];

	m_stream.clear();
	m_stream.seekg(lfh->file_data_offset,std::ios::beg);

	unsigned char *buffer = NULL;

	if(lfh->compression_method == NO_COMPRESSION){
		//	Files are just stored
		buffer = ReadRaw(m_length);

	}else if(lfh->compression_method == DEFLATE_COMPRESSION){
		//	Files are deflated

		//	Read compressed data from the disk
		unsigned char *src = ReadRaw(lfh->comp_size);

		//	Allocate a buffer for the decompressed data
		buffer = new unsigned char[length];

		//	setup the z_stream structure
		memset(&m_zipstream,0,sizeof(z_stream));

		m_zipstream.avail_in	= lfh->comp_size;
		m_zipstream.next_in		=	src; 

		m_zipstream.avail_out	= m_length;
		m_zipstream.next_out	=	buffer;

		inflateInit2(&m_zipstream,-15);
		inflate(&m_zipstream,Z_FINISH);
		inflateEnd(&m_zipstream);

		delete[] src;
	}

	return buffer;
}