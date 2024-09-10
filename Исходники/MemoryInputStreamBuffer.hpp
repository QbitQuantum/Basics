			MemoryInputStreamBuffer(
				std::string const & rfn,
				int64_t const rblocksize,
				uint64_t const rputbackspace = 0
			)
			: 
			  fd(doOpen(rfn)),
			  filesize(fd->getFileSize()),
			  blocksize((rblocksize < 0) ? getDefaultBlockSize() : rblocksize),
			  putbackspace(rputbackspace),
			  buffer(putbackspace + blocksize,false),
			  symsread(0)
			{
				init(false);
			}