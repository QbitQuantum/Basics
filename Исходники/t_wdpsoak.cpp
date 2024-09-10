void CActiveConsole::ProcessKeyPressL(TChar aChar)
	{
	if (aChar == EKeyEscape)
		{
		PRINT(_L("CActiveConsole: ESC key pressed -> stopping active scheduler...\n"));
		CActiveScheduler::Stop();
		return;
		}
	aChar.UpperCase();
	if (iCmdGetValue != 0 && aChar == '\r')
		{
		if (iLastChar == 'K')
			{
			iValue *= iGetHexValue ? 0x400 : 1000;
			}
		if (iLastChar == 'M')
			{
			iValue *= iGetHexValue ? 0x10000 : 1000000;
			}
		PRINT1(_L("CActiveConsole: Value %d\n"),iValue);
		ProcessValue();
		}
	if (iCmdGetValue != 0 )
		{
		if (iGetHexValue)
			{
			if (aChar.IsDigit())
				{
				iValue = iValue * 16 + aChar.GetNumericValue();
			}
			else
				{
				if (aChar.IsHexDigit())
					{
					iValue = iValue * 16 + (TUint)aChar - 'A' + 10;
					}
				else
					{
						if (aChar != 'K' && aChar != 'M')
						{
						PRINT(_L("Illegal hexadecimal character - Enter command\n"));
						iCmdGetValue = 0;
						}
					}
				}
			}
		else
			{
			if (aChar.IsDigit())
				{
				iValue = iValue * 10 + aChar.GetNumericValue();
				}
			else
				{
				if ((aChar == 'X') && (iLastChar == '0') && (iValue == 0))
					iGetHexValue = ETrue;
				else
					{
					if (aChar != 'K' && aChar != 'M')
						{
						test.Printf(_L("Illegal decimal character - Enter command\n"));
						iCmdGetValue = 0;							
						}
					}
				}
			}
		}
	else
		{
		switch (aChar)
			{
			case 'F' :
				TESTNEXT(_L("Flushing Cache"));
				test_KErrNone(DPTest::FlushCache());
				ShowMemoryUse();
				iPrompt = ETrue;
				break;
				
			case 'I' :
				CacheSize(0,0);
				ShowMemoryUse();
				iPrompt = ETrue;
				break;
	
			case 'Q' :
				gQuiet = ETrue;
				iPrompt = ETrue;
				break;

			case 'V' :
				gQuiet = EFalse;
				iPrompt = ETrue;
				break;
				
			case '?' :
				ShowHelp();
				break;

			case '=' :
				iCmdGetValue = iLastChar;
				iGetHexValue = EFalse;
				iValue = 0;
				break;
						
			default :
				if (aChar.IsDigit())
					{
					if (iLastChar == 'R')
						{
						if (aChar.GetNumericValue() < (TInt)gNextChunk)
							{
							ReadChunk (&gChunk[aChar.GetNumericValue()]);			
							}
						else
							{
							for (TUint i = 0; i < gNextChunk; i++)
								ReadChunk (&gChunk[i]);			
							}
						iPrompt = ETrue;
						}				
					if (iLastChar == 'W')
						{
						if (aChar.GetNumericValue() < (TInt)gNextChunk)
							{
							WriteChunk (&gChunk[aChar.GetNumericValue()]);			
							}
						else
							{
							for (TUint i = 0; i < gNextChunk; i++)
								WriteChunk (&gChunk[i]);			
							}
						iPrompt = ETrue;
						}
					if (iLastChar == 'M')
						{
						if (aChar.GetNumericValue() == 0)
							{
							iActions = (TUint16)(iPeriod < KFlushQuietLimit ? EFlushQuiet : EFlush);							
							}
						else
							{
							iActions = (TUint16)(aChar.GetNumericValue() << 4);							
							}
						iPrompt = ETrue;
						}
					}
				break;
			}
		}
	iLastChar = aChar;
	GetCharacter();
	return;
	}