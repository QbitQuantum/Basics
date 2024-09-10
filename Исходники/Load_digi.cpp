bool CSoundFile::ReadDIGI(FileReader &file, ModLoadingFlags loadFlags)
//--------------------------------------------------------------------
{
	file.Rewind();

	DIGIFileHeader fileHeader;
	if(!file.ReadConvertEndianness(fileHeader)
		|| memcmp(fileHeader.signature, "DIGI Booster module\0", 20)
		|| !fileHeader.numChannels
		|| fileHeader.numChannels > 8
		|| fileHeader.lastOrdIndex > 127)
	{
		return false;
	} else if(loadFlags == onlyVerifyHeader)
	{
		return true;
	}

	// Globals
	InitializeGlobals();
	InitializeChannels();

	m_nType = MOD_TYPE_DIGI;
	m_nChannels = fileHeader.numChannels;
	m_nSamples = 31;
	m_nSamplePreAmp = 256 / m_nChannels;
	madeWithTracker = mpt::String::Print("Digi Booster %1.%2", fileHeader.versionInt >> 4, fileHeader.versionInt & 0x0F);

	Order.ReadFromArray(fileHeader.orders, fileHeader.lastOrdIndex + 1);

	// Read sample headers
	for(SAMPLEINDEX smp = 0; smp < 31; smp++)
	{
		ModSample &sample = Samples[smp + 1];
		sample.Initialize(MOD_TYPE_MOD);
		sample.nLength = fileHeader.smpLength[smp];
		sample.nLoopStart = fileHeader.smpLoopStart[smp];
		sample.nLoopEnd = sample.nLoopStart + fileHeader.smpLoopLength[smp];
		if(fileHeader.smpLoopLength[smp])
		{
			sample.uFlags.set(CHN_LOOP);
		}
		sample.SanitizeLoops();
	
		sample.nVolume = std::min(fileHeader.smpVolume[smp], uint8(64)) * 4;
		sample.nFineTune = MOD2XMFineTune(fileHeader.smpFinetune[smp]);
	}

	// Read song + sample names
	file.ReadString<mpt::String::maybeNullTerminated>(songName, 32);
	for(SAMPLEINDEX smp = 1; smp <= 31; smp++)
	{
		file.ReadString<mpt::String::maybeNullTerminated>(m_szNames[smp], 30);
	}

	for(PATTERNINDEX pat = 0; pat <= fileHeader.lastPatIndex; pat++)
	{
		FileReader patternChunk;
		if(fileHeader.packEnable)
		{
			patternChunk = file.ReadChunk(file.ReadUint16BE());
		} else
		{
			patternChunk = file.ReadChunk(4 * 64 * GetNumChannels());
		}

		if(!(loadFlags & loadPatternData) || Patterns.Insert(pat, 64))
		{
			continue;
		}

		if(fileHeader.packEnable)
		{
			std::vector<uint8> eventMask;
			patternChunk.ReadVector(eventMask, 64);

			// Compressed patterns are stored in row-major order...
			for(ROWINDEX row = 0; row < 64; row++)
			{
				PatternRow patRow = Patterns[pat].GetRow(row);
				uint8 bit = 0x80;
				for(CHANNELINDEX chn = 0; chn < GetNumChannels(); chn++, bit >>= 1)
				{
					if(eventMask[row] & bit)
					{
						ModCommand &m = patRow[chn];
						ReadDIGIPatternEntry(patternChunk, m, *this);
					}
				}
			}
		} else
		{
			// ...but uncompressed patterns are stored in column-major order. WTF!
			for(CHANNELINDEX chn = 0; chn < GetNumChannels(); chn++)