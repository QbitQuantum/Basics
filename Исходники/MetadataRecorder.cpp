	static inline bool ReadFccCodes(CCryFile& file, TFourCCSet& fccs, uint32 keyword)
	{
		uint32 fcc = 0;
		if ( file.ReadRaw(&fcc, sizeof(fcc)) != sizeof(fcc) )
			return false;
		if (fcc != keyword)
			return false;
		while (true)
		{
			if ( file.ReadRaw(&fcc, sizeof(fcc)) != sizeof(fcc) )
				return false;
			if (fcc == eBK_tags || fcc == eBK_typs)
				return false;
			if (fcc == eBK_void)
				break;
			fccs.insert(fcc);
		}
		return true;
	}