UnicodeBlockSet::UnicodeBlockSet()
{
	int last_block = UBLOCK_INVALID_CODE;
	for(UChar32 u=0; u<=0x110000; ++u)
	{
		int block = ublock_getCode(u);
		if (block != last_block)
		{
			// last block end
			m_block_map[last_block].second = u-1;

			// current block begin
			m_block_map[block].first = u;
		}
		last_block = block;
	}

	m_block_map.erase(UBLOCK_INVALID_CODE);
	m_block_map.erase(UBLOCK_NO_BLOCK);

	InitBlockDescriptions();
}