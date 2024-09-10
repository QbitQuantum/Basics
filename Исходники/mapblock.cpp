void MapBlock::deSerialize(std::istream &is, u8 version)
{
	if(!ser_ver_supported(version))
		throw VersionMismatchException("ERROR: MapBlock format not supported");

	// These have no lighting info
	if(version <= 1)
	{
		setLightingExpired(true);
	}

	// These have no "generated" field
	if(version < 18)
	{
		m_generated = true;
	}

	// These have no compression
	if(version <= 3 || version == 5 || version == 6)
	{
		u32 nodecount = MAP_BLOCKSIZE*MAP_BLOCKSIZE*MAP_BLOCKSIZE;
		char tmp;
		is.read(&tmp, 1);
		if(is.gcount() != 1)
			throw SerializationError
					("MapBlock::deSerialize: no enough input data");
		is_underground = tmp;
		for(u32 i=0; i<nodecount; i++)
		{
			s32 len = MapNode::serializedLength(version);
			SharedBuffer<u8> d(len);
			is.read((char*)*d, len);
			if(is.gcount() != len)
				throw SerializationError
						("MapBlock::deSerialize: no enough input data");
			data[i].deSerialize(*d, version);
		}
	}
	else if(version <= 10)
	{
		u32 nodecount = MAP_BLOCKSIZE*MAP_BLOCKSIZE*MAP_BLOCKSIZE;

		u8 t8;
		is.read((char*)&t8, 1);
		is_underground = t8;

		{
			// Uncompress and set material data
			std::ostringstream os(std::ios_base::binary);
			decompress(is, os, version);
			std::string s = os.str();
			if(s.size() != nodecount)
				throw SerializationError
						("MapBlock::deSerialize: invalid format");
			for(u32 i=0; i<s.size(); i++)
			{
				data[i].param0 = s[i];
			}
		}
		{
			// Uncompress and set param data
			std::ostringstream os(std::ios_base::binary);
			decompress(is, os, version);
			std::string s = os.str();
			if(s.size() != nodecount)
				throw SerializationError
						("MapBlock::deSerialize: invalid format");
			for(u32 i=0; i<s.size(); i++)
			{
				data[i].param1 = s[i];
			}
		}
	
		if(version >= 10)
		{
			// Uncompress and set param2 data
			std::ostringstream os(std::ios_base::binary);
			decompress(is, os, version);
			std::string s = os.str();
			if(s.size() != nodecount)
				throw SerializationError
						("MapBlock::deSerialize: invalid format");
			for(u32 i=0; i<s.size(); i++)
			{
				data[i].param2 = s[i];
			}
		}
	}
	// All other versions (newest)
	else
	{
		u32 nodecount = MAP_BLOCKSIZE*MAP_BLOCKSIZE*MAP_BLOCKSIZE;

		u8 flags;
		is.read((char*)&flags, 1);
		is_underground = (flags & 0x01) ? true : false;
		m_day_night_differs = (flags & 0x02) ? true : false;
		m_lighting_expired = (flags & 0x04) ? true : false;
		if(version >= 18)
			m_generated = (flags & 0x08) ? false : true;

		// Uncompress data
		std::ostringstream os(std::ios_base::binary);
		decompress(is, os, version);
		std::string s = os.str();
		if(s.size() != nodecount*3)
			throw SerializationError
					("MapBlock::deSerialize: decompress resulted in size"
					" other than nodecount*3");

		// deserialize nodes from buffer
		for(u32 i=0; i<nodecount; i++)
		{
			u8 buf[3];
			buf[0] = s[i];
			buf[1] = s[i+nodecount];
			buf[2] = s[i+nodecount*2];
			data[i].deSerialize(buf, version);
		}
		
		/*
			NodeMetadata
		*/
		if(version >= 14)
		{
			// Ignore errors
			try{
				if(version <= 15)
				{
					std::string data = deSerializeString(is);
					std::istringstream iss(data, std::ios_base::binary);
					m_node_metadata->deSerialize(iss, m_gamedef);
				}
				else
				{
					//std::string data = deSerializeLongString(is);
					std::ostringstream oss(std::ios_base::binary);
					decompressZlib(is, oss);
					std::istringstream iss(oss.str(), std::ios_base::binary);
					m_node_metadata->deSerialize(iss, m_gamedef);
				}
			}
			catch(SerializationError &e)
			{
				errorstream<<"WARNING: MapBlock::deSerialize(): Ignoring an error"
						<<" while deserializing node metadata"<<std::endl;
			}
		}
	}
}