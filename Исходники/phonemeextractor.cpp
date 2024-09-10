//-----------------------------------------------------------------------------
// Purpose: Given a wave file and a string of words "text", creates a CFG from the
//  sentence and stores the resulting words/phonemes in CSentence
// Input  : *wavname - 
//			text - 
//			sentence - 
//			(*pfnPrint - 
// Output : SR_RESULT
//-----------------------------------------------------------------------------
SR_RESULT ExtractPhonemes( const char *wavname, CSpDynamicString& text, CSentence& sentence, void (*pfnPrint)( const char *fmt, ...) )
{
	// Assume failure
	SR_RESULT result = SR_RESULT_ERROR;

	if ( text.Length() <= 0 )
	{
		pfnPrint( "Error:  no rule / text specified\n" );
		return result;
	}

	USES_CONVERSION;
	HRESULT hr;
	
	CUtlVector < WORDRULETYPE > wordRules;

	CComPtr<ISpStream> cpInputStream;
	CComPtr<ISpRecognizer> cpRecognizer;
	CComPtr<ISpRecoContext> cpRecoContext;
	CComPtr<ISpRecoGrammar> cpRecoGrammar;
	CComPtr<ISpPhoneConverter>  cpPhoneConv;
    
	// Create basic SAPI stream object
	// NOTE: The helper SpBindToFile can be used to perform the following operations
	hr = cpInputStream.CoCreateInstance(CLSID_SpStream);
	if ( FAILED( hr ) )
	{
		pfnPrint( "Error:  SAPI 5.1 Stream object not installed?\n" );
		return result;
	}

	CSpStreamFormat sInputFormat;
	
	// setup stream object with wav file MY_WAVE_AUDIO_FILENAME
	//   for read-only access, since it will only be access by the SR engine
	hr = cpInputStream->BindToFile(
		T2W(wavname),
		SPFM_OPEN_READONLY,
		NULL,
		sInputFormat.WaveFormatExPtr(),
		SPFEI_ALL_EVENTS );

	if ( FAILED( hr ) )
	{
		pfnPrint( "Error: couldn't open wav file %s\n", wavname );
		return result;
	}
	
	// Create in-process speech recognition engine
	hr = cpRecognizer.CoCreateInstance(CLSID_SpInprocRecognizer);
	if ( FAILED( hr ) )
	{
		pfnPrint( "Error:  SAPI 5.1 In process recognizer object not installed?\n" );
		return result;
	}

	// Create recognition context to receive events
	hr = cpRecognizer->CreateRecoContext(&cpRecoContext);
	if ( FAILED( hr ) )
	{
		pfnPrint( "Error:  SAPI 5.1 Unable to create recognizer context\n" );
		return result;
	}
	
	// Create a grammar
	hr = cpRecoContext->CreateGrammar( EP_GRAM_ID, &cpRecoGrammar );
	if ( FAILED( hr ) )
	{
		pfnPrint( "Error:  SAPI 5.1 Unable to create recognizer grammar\n" );
		return result;
	}

	LANGID englishID = 0x409; // 1033 decimal

	bool userSpecified = false;
	LANGID langID = SpGetUserDefaultUILanguage();

	// Allow commandline override
	if ( CommandLine()->FindParm( "-languageid" ) != 0 )
	{
		userSpecified = true;
		langID = CommandLine()->ParmValue( "-languageid", langID );
	}

	// Create a phoneme converter ( so we can convert to IPA codes )
	hr = SpCreatePhoneConverter( langID, NULL, NULL, &cpPhoneConv );
	if ( FAILED( hr ) )
	{
		if ( langID != englishID )
		{
			if ( userSpecified )
			{
				pfnPrint( "Warning:  SAPI 5.1 Unable to create phoneme converter for command line override -languageid %i\n", langID );
			}
			else
			{
				pfnPrint( "Warning:  SAPI 5.1 Unable to create phoneme converter for default UI language %i\n",langID );
			}

			// Try english!!!
			langID = englishID;
			hr = SpCreatePhoneConverter( langID, NULL, NULL, &cpPhoneConv );
		}

		if ( FAILED( hr ) )
		{
			pfnPrint( "Error:  SAPI 5.1 Unable to create phoneme converter for English language id %i\n", langID );
			return result;
		}
		else
		{
			pfnPrint( "Note:  SAPI 5.1 Falling back to use english -languageid %i\n", langID );
		}
	}
	else if ( userSpecified )
	{
		pfnPrint( "Note:  SAPI 5.1 Using user specified -languageid %i\n",langID );
	}

	SPSTATEHANDLE hStateRoot;
	// create/re-create Root level rule of grammar
	hr = cpRecoGrammar->GetRule(L"Root", 0, SPRAF_TopLevel | SPRAF_Active, TRUE, &hStateRoot);
	if ( FAILED( hr ) )
	{
		pfnPrint( "Error:  SAPI 5.1 Unable to create root rule\n" );
		return result;
	}

	// Inactivate it so we can alter it
	hr = cpRecoGrammar->SetRuleState( NULL, NULL, SPRS_INACTIVE );
	if ( FAILED( hr ) )
	{
		pfnPrint( "Error:  SAPI 5.1 Unable to deactivate grammar rules\n" );
		return result;
	}

	// Create the rule set from the words in text
	{
		CSpDynamicString currentWord;
		WCHAR *pos = ( WCHAR * )text;
		WCHAR str[ 2 ];
		str[1]= 0;

		while ( *pos )
		{
			if ( *pos == L' ' /*|| *pos == L'.' || *pos == L'-'*/ )
			{
				// Add word to rule set
				if ( currentWord.Length() > 0 )
				{
					AddWordRule( cpRecoGrammar, &hStateRoot, &wordRules, currentWord );
					currentWord.Clear();
				}
				pos++;
				continue;
			}

			// Skip anything that's inside a [ xxx ] pair.
			if ( *pos == L'[' )
			{
				while ( *pos && *pos != L']' )
				{
					pos++;
				}

				if ( *pos )
				{
					pos++;
				}
				continue;
			}

			str[ 0 ] = *pos;

			currentWord.Append( str );
			pos++;
		}

		if ( currentWord.Length() > 0 )
		{
			AddWordRule( cpRecoGrammar, &hStateRoot, &wordRules, currentWord );
		}

		if ( wordRules.Size() <= 0 )
		{
			pfnPrint( "Error:  Text %s contained no usable words\n", text );
			return result;
		}

		// Build all word to word transitions in the grammar
		if ( !BuildRules( cpRecoGrammar, &hStateRoot, &wordRules ) )
		{
			pfnPrint( "Error:  Rule set for %s could not be generated\n", text );
			return result;
		}
	}

	// check for recognitions and end of stream event
	const ULONGLONG ullInterest = 
		SPFEI(SPEI_RECOGNITION) | SPFEI(SPEI_END_SR_STREAM) | SPFEI(SPEI_FALSE_RECOGNITION) | 
		SPFEI(SPEI_PHRASE_START ) | SPFEI(SPEI_HYPOTHESIS ) | SPFEI(SPEI_INTERFERENCE) ;
	hr = cpRecoContext->SetInterest( ullInterest, ullInterest );
	if ( FAILED( hr ) )
	{
		pfnPrint( "Error:  SAPI 5.1 Unable to set interest level\n" );
		return result;
	}	
	// use Win32 events for command-line style application
	hr = cpRecoContext->SetNotifyWin32Event();
	if ( FAILED( hr ) )
	{
		pfnPrint( "Error:  SAPI 5.1 Unable to set win32 notify event\n" );
		return result;
	}
	// connect wav input to recognizer
	// SAPI will negotiate mismatched engine/input audio formats using system audio codecs, so second parameter is not important - use default of TRUE
	hr = cpRecognizer->SetInput(cpInputStream, TRUE);
	if ( FAILED( hr ) )
	{
		pfnPrint( "Error:  SAPI 5.1 Unable to associate input stream\n" );
		return result;
	}	

	// Activate the CFG ( rather than using dictation )
	hr = cpRecoGrammar->SetRuleState( NULL, NULL, SPRS_ACTIVE );
	if ( FAILED( hr ) )
	{
		switch ( hr )
		{
		case E_INVALIDARG:
			pfnPrint( "pszName is invalid or bad. Alternatively, pReserved is non-NULL\n" );
			break;
		case SP_STREAM_UNINITIALIZED:
			pfnPrint( "ISpRecognizer::SetInput has not been called with the InProc recognizer\n" );
			break;
		case SPERR_UNINITIALIZED:
			pfnPrint( "The object has not been properly initialized.\n");
			break;
		case SPERR_UNSUPPORTED_FORMAT:
			pfnPrint( "Audio format is bad or is not recognized. Alternatively, the device driver may be busy by another application and cannot be accessed.\n" );
			break;
		case SPERR_NOT_TOPLEVEL_RULE:
			pfnPrint( "The rule pszName exists, but is not a top-level rule.\n" );
			break;
		default:
			pfnPrint( "Unknown error\n" );
			break;
		}
		pfnPrint( "Error:  SAPI 5.1 Unable to activate rule set\n" );
		return result;
	}

	// while events occur, continue processing
	// timeout should be greater than the audio stream length, or a reasonable amount of time expected to pass before no more recognitions are expected in an audio stream
	BOOL fEndStreamReached = FALSE;
	while (!fEndStreamReached && S_OK == cpRecoContext->WaitForNotifyEvent( SR_WAVTIMEOUT ))
	{
		CSpEvent spEvent;
		// pull all queued events from the reco context's event queue
		
		while (!fEndStreamReached && S_OK == spEvent.GetFrom(cpRecoContext))
		{
			// Check event type
			switch (spEvent.eEventId)
			{
			case SPEI_INTERFERENCE:
				{
					SPINTERFERENCE interference = spEvent.Interference();

					switch ( interference )
					{
					case SPINTERFERENCE_NONE:
						pfnPrint( "[ I None ]\r\n" );
						break;
					case SPINTERFERENCE_NOISE:
						pfnPrint( "[ I Noise ]\r\n" );
						break;
					case SPINTERFERENCE_NOSIGNAL:
						pfnPrint( "[ I No Signal ]\r\n" );
						break;
					case SPINTERFERENCE_TOOLOUD:
						pfnPrint( "[ I Too Loud ]\r\n" );
						break;
					case SPINTERFERENCE_TOOQUIET:
						pfnPrint( "[ I Too Quiet ]\r\n" );
						break;
					case SPINTERFERENCE_TOOFAST:
						pfnPrint( "[ I Too Fast ]\r\n" );
						break;
					case SPINTERFERENCE_TOOSLOW:
						pfnPrint( "[ I Too Slow ]\r\n" );
						break;
					default:
						break;
					}
				}
				break;
			case SPEI_PHRASE_START:
				pfnPrint( "Phrase Start\r\n" );
				sentence.MarkNewPhraseBase();
				break;

			case SPEI_HYPOTHESIS:
			case SPEI_RECOGNITION:
			case SPEI_FALSE_RECOGNITION:
				{
                    CComPtr<ISpRecoResult> cpResult;
                    cpResult = spEvent.RecoResult();

                    CSpDynamicString dstrText;
                    if (spEvent.eEventId == SPEI_FALSE_RECOGNITION)
                    {
                        dstrText = L"(Unrecognized)";

						result = SR_RESULT_FAILED;

						// It's possible that the failed recog might have more words, so see if that's the case
						EnumeratePhonemes( cpPhoneConv, cpResult, sentence );
					}
                    else
                    {
						// Hypothesis or recognition success
                        cpResult->GetText( (ULONG)SP_GETWHOLEPHRASE, (ULONG)SP_GETWHOLEPHRASE, TRUE, &dstrText, NULL);

						EnumeratePhonemes( cpPhoneConv, cpResult, sentence );

						if ( spEvent.eEventId == SPEI_RECOGNITION )
						{
							result = SR_RESULT_SUCCESS;
						}

						pfnPrint( va( "%s%s\r\n", spEvent.eEventId == SPEI_HYPOTHESIS ? "[ Hypothesis ] " : "", dstrText.CopyToChar() ) );
					}
                    
                    cpResult.Release();
				}
				break;
				// end of the wav file was reached by the speech recognition engine
            case SPEI_END_SR_STREAM:
				fEndStreamReached = TRUE;
				break;
			}
			
			// clear any event data/object references
			spEvent.Clear();
		}// END event pulling loop - break on empty event queue OR end stream
	}// END event polling loop - break on event timeout OR end stream
	
	// Deactivate rule
	hr = cpRecoGrammar->SetRuleState( NULL, NULL, SPRS_INACTIVE );
	if ( FAILED( hr ) )
	{
		pfnPrint( "Error:  SAPI 5.1 Unable to deactivate rule set\n" );
		return result;
	}

	// close the input stream, since we're done with it
	// NOTE: smart pointer will call SpStream's destructor, and consequently ::Close, but code may want to check for errors on ::Close operation
	hr = cpInputStream->Close();
	if ( FAILED( hr ) )
	{
		pfnPrint( "Error:  SAPI 5.1 Unable to close input stream\n" );
		return result;
	}

	return result;
}