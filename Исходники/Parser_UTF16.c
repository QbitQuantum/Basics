ParseBlocker utf16_parse(
	void *in_out_pParserState, 
	void *in_pReadState, ByteStreamReadInterface_v4 in_readInterface, 
	void *in_pWriteState, ByteStreamWriteInterface_v4 in_writeInterface)
{
	UTF16_State *pUTF16State = (UTF16_State *) in_out_pParserState;
	extern const UnicodeCodePoint cReplacementCharacter;

	assert(in_readInterface.mpfRead != NULL);
	assert(in_readInterface.commonByteStreamInterface.mpfGetStatus != NULL);

	switch (pUTF16State->entryPoint)
	{
	case UTF16_EntryPoint_BeforeReading:
		goto Label_EntryPoint_BeforeReading;
	case UTF16_EntryPoint_BeforeWritingReplacementCharacterAndGotoBegin:
		goto Label_EntryPoint_BeforeWritingReplacementCharacterAndGotoBegin;
	case UTF16_EntryPoint_WriteCodePoint:
		goto Label_EntryPoint_WriteCodePoint;
	case UTF16_EntryPoint_WriteTwoTerminalReplacementCharacters:
		goto Label_EntryPoint_WriteTwoTerminalReplacementCharacters;
	case UTF16_EntryPoint_WriteTerminalReplacementCharacter:
		goto Label_EntryPoint_WriteTerminalReplacementCharacter;
	case UTF16_EntryPoint_Terminated:
		goto Label_EntryPoint_Terminated;
	}

	assert(false);

	while (1)
	{
		size_t rwCount;

		pUTF16State->readCount = 0;

Label_EntryPoint_BeforeReading:
		assert(pUTF16State->readCount < 2);
		rwCount = in_readInterface.mpfRead(in_pReadState, 
			((uint8_t *) &pUTF16State->currentWord) + pUTF16State->readCount, 
			2 - pUTF16State->readCount);

		assert(rwCount <= 2u - pUTF16State->readCount);

		pUTF16State->readCount += (uint8_t) rwCount;

		if (0 == pUTF16State->readCount)
		{
			ByteStreamStatus_v4 status = in_readInterface.
				commonByteStreamInterface.mpfGetStatus(in_pReadState);
			assert(ByteStreamStatus_OK != status);

			if (ByteStreamStatus_Terminated == status)
			{
				if (!pUTF16State->isSecondWord)
					goto terminate;
				else
					goto Label_EntryPoint_WriteTerminalReplacementCharacter;
			}
			else
			{
				pUTF16State->entryPoint = UTF16_EntryPoint_BeforeReading;
				return ParseBlocker_Reader;
			}
		}
		else if (1 == pUTF16State->readCount)
		{
			ByteStreamStatus_v4 status = in_readInterface.
				commonByteStreamInterface.mpfGetStatus(in_pReadState);
			assert(ByteStreamStatus_OK != status);

			if (ByteStreamStatus_Terminated == status)
			{
				if (!pUTF16State->isSecondWord || 
					!pUTF16State->bigEndian || 
					/*
					* Q: Why the bitwise and with 0xFF?
					* A: Because we read only one byte (the lower one), we don't 
					*    know what the value of the higher byte is. It can be
					*    anything.
					*/
					(0xDC <= (pUTF16State->currentWord & 0xFF) && 
					(pUTF16State->currentWord & 0xFF) <= 0xDF))
				{
					goto Label_EntryPoint_WriteTerminalReplacementCharacter;
				}
				else
				{
					assert(pUTF16State->isSecondWord);
					assert(pUTF16State->bigEndian);
					assert((pUTF16State->currentWord & 0xFF) < 0xDC || 
						(pUTF16State->currentWord & 0xFF) > 0xDF);

					goto Label_EntryPoint_WriteTwoTerminalReplacementCharacters;
				}
			}
			else
			{
				pUTF16State->entryPoint = UTF16_EntryPoint_BeforeReading;
				return ParseBlocker_Reader;
			}
		}
		else
		{
			assert(2 == pUTF16State->readCount);

			if (pUTF16State->bigEndian)
				pUTF16State->currentWord = _byteswap_ushort(pUTF16State->currentWord);

			if (!pUTF16State->isSecondWord)
			{
begin_of_S:
				if (pUTF16State->currentWord < 0xD800 || 
					pUTF16State->currentWord >= 0xDC00)
				{
					// 0xDC00 <= pUTF16State->currentWord < 0xE000: low surrogate
					if (0xDC00 <= pUTF16State->currentWord  && 
						pUTF16State->currentWord < 0xE000)
						pUTF16State->currentCodePoint = cReplacementCharacter;
					else
						pUTF16State->currentCodePoint = pUTF16State->currentWord;
				}
				else
				{
					assert(pUTF16State->currentWord >= 0xD800);
					assert(pUTF16State->currentWord <= 0xDBFF);

					pUTF16State->prevWord = pUTF16State->currentWord;
					pUTF16State->isSecondWord = true;

					continue;
				}
			}
			else
			{
				pUTF16State->isSecondWord = false;

				if (pUTF16State->currentWord < 0xDC00 || 0xDFFF < pUTF16State->currentWord)
				{
Label_EntryPoint_BeforeWritingReplacementCharacterAndGotoBegin:
					if (emitCodepoint(in_pWriteState, in_writeInterface, 
						cReplacementCharacter, &pUTF16State->entryPoint, 
						sizeof(UTF16_EntryPoint), 
						UTF16_EntryPoint_BeforeWritingReplacementCharacterAndGotoBegin))
						return ParseBlocker_Writer;

					goto begin_of_S;
				}
				else
				{
					// See http://unicode.org/faq/utf_bom.html#utf16-4
					pUTF16State->currentCodePoint = 
						(pUTF16State->prevWord << 10) + pUTF16State->currentWord + SURROGATE_OFFSET;
				}
			}

Label_EntryPoint_WriteCodePoint:
			if (emitCodepoint(in_pWriteState, in_writeInterface, 
				pUTF16State->currentCodePoint, &pUTF16State->entryPoint, 
				sizeof(UTF16_EntryPoint), 
				UTF16_EntryPoint_WriteCodePoint))
				return ParseBlocker_Writer;
		}
	}

Label_EntryPoint_WriteTwoTerminalReplacementCharacters:
	if (emitCodepoint(in_pWriteState, in_writeInterface, 
		cReplacementCharacter, &pUTF16State->entryPoint, 
		sizeof(UTF16_EntryPoint), 
		UTF16_EntryPoint_WriteTwoTerminalReplacementCharacters))
		return ParseBlocker_Writer;

Label_EntryPoint_WriteTerminalReplacementCharacter:
	assert(ByteStreamStatus_Terminated == in_readInterface.
		commonByteStreamInterface.mpfGetStatus(in_pReadState));

	if (emitCodepoint(in_pWriteState, in_writeInterface, 
		pUTF16State->currentCodePoint, &pUTF16State->entryPoint, 
		sizeof(UTF16_EntryPoint), 
		UTF16_EntryPoint_WriteTerminalReplacementCharacter))
		return ParseBlocker_Writer;

terminate:
	if (!ByteStreamStatus_Error == in_writeInterface.
		commonByteStreamInterface.mpfGetStatus(in_pWriteState))
		in_writeInterface.commonByteStreamInterface.mpfSetStatus(
		in_pWriteState, ByteStreamStatus_Terminated);

	pUTF16State->entryPoint = UTF16_EntryPoint_Terminated;

Label_EntryPoint_Terminated:
	assert(ByteStreamStatus_Terminated == in_readInterface.
		commonByteStreamInterface.mpfGetStatus(in_pReadState));
	return ParseBlocker_Neither;
}