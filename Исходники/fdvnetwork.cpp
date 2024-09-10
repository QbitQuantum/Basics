	char const* MTD_FLASHMEM ParameterReplacer::replaceTag(char const* curc)
	{
		char const* tagEnd;
		char const* tagStart = extractTagStr(curc, &tagEnd);
		if (getChar(tagStart) == '#')
		{
			// replace multiple parameters ('0param', '1param', ...)
			++tagStart;			
			uint32_t tagLen = tagEnd - tagStart;
			char tag[tagLen];
			f_memcpy(tag, tagStart, tagLen);
			tag[tagLen] = 0;
			for (uint32_t index = 0; ; ++index)
			{
				char const* fulltagname = f_printf(FSTR("%d%s"), index, tag);
				Params::Item* item = m_params->getItem(fulltagname);
				if (item)
					m_results.last()->addChunks(&item->value); // push parameter content
				else
					break;
			}
		}
		else
		{
			// replace one parameter
			Params::Item* item = m_params->getItem(tagStart, tagEnd);
			if (item)				
				m_results.last()->addChunks(&item->value); // push parameter content
            else if(m_blockParams)
            {
                BlockParams::Item* item = m_blockParams->getItem(tagStart, tagEnd);
                if (item)
                    m_results.last()->addChunks(item->value);   // push block parameter content
            }
		}
		return tagEnd + 2;	// bypass "}}"
	}