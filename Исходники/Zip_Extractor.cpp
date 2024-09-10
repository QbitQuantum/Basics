blargg_err_t Zip_Extractor::open_v()
{
	if ( arc().size() < end_entry_size )
		return blargg_err_file_type;
	
	isZIP64 = false;
	if (arc().size() > 0xffffffff)
		isZIP64 = true;

	// Read final end_read_size bytes of file
	//BOOST::uint64_t file_pos = max( (BOOST::uint64_t) 0, arc().size() - end_read_size );
    BOOST::int64_t file_pos = max( (BOOST::int64_t) 0, (BOOST::int64_t) arc().size() - end_read_size );
	file_pos -= file_pos % disk_block_size;
	RETURN_ERR( catalog.resize( (size_t)(arc().size() - file_pos) ) );
	RETURN_ERR( arc().seek( file_pos ) );
	RETURN_ERR( arc().read( catalog.begin(), catalog.size() ) );
	
	BOOST::int64_t end_pos = 0;
	
	if (!isZIP64)
	{
		// Find end-of-catalog entry
		end_pos = catalog.size() - end_entry_size;
		while (end_pos >= 0 && memcmp(&catalog[(size_t)end_pos], "PK\5\6", 4))
			end_pos--;
		if (end_pos < 0)
			return blargg_err_file_type;
		end_entry_t const& end_entry = (end_entry_t&)catalog[(size_t)end_pos];
		catalog_begin = get_le32(end_entry.dir_offset);
	}

	if (isZIP64)
	{
		// Find end64-of-catalog entry
		end_pos = catalog.size() - end64_entry_size;
		while (end_pos >= 0 && memcmp(&catalog[(size_t)end_pos], "PK\6\6", 4))
			end_pos--;
		if (end_pos < 0)
			return blargg_err_file_type;
		end64_entry_t const& end_entry = (end64_entry_t&)catalog[(size_t)end_pos];
		catalog_begin = get_le64(end_entry.dir_offset);
	}

	end_pos += file_pos;

	// some idiotic zip compressors add data to end of zip without setting comment len
	//  check( arc().size() == end_pos + end_entry_size + get_le16( end_entry.comment_len ) );
	
    BOOST::int64_t catalog_size = end_pos - catalog_begin;
	if ( catalog_size < 0 )
		return blargg_err_file_corrupt;

	if (isZIP64)
		catalog_size += end64_entry_size;
	else
		catalog_size += end_entry_size;

	// See if catalog is entirely contained in bytes already read
	BOOST::int64_t begin_offset = catalog_begin - file_pos;
	if ( begin_offset >= 0 )
		memmove( catalog.begin(), &catalog [(size_t)begin_offset], (size_t)catalog_size );

	RETURN_ERR( catalog.resize( (size_t)catalog_size ) );
	if ( begin_offset < 0 )
	{
		// Catalog begins before bytes read, so it needs to be read
		RETURN_ERR( arc().seek( catalog_begin ) );
		RETURN_ERR( arc().read( catalog.begin(), catalog.size() ) );
	}

	// First entry in catalog should be a file or end of archive
	if ( memcmp( catalog.begin(), "PK\1\2", 4 ) && memcmp( catalog.begin(), "PK\5\6", 4 ) )
		return blargg_err_file_type;
	
	reorder_entry_header( 0 );
	return rewind_v();
}