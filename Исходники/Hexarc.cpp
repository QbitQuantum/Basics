void HexarcTest (CUniverse &Universe, CXMLElement *pCmdLine)
	{
	int i, j;

	CString sHostspec = pCmdLine->GetAttribute(OPTION_HOST);
	if (sHostspec.IsBlank())
		sHostspec = HOSTSPEC_DEFAULT;

	CHTTPClientSession Session;

	if (!Connect(sHostspec, Session))
		return;

	//	Read the list of high scores

	for (j = 0; j < 5; j++)
		{
		CJSONValue Payload = CJSONValue(CJSONValue::typeObject);
		Payload.InsertHandoff(FIELD_MAX_GAMES, CJSONValue(100));
		CJSONValue Result;
		if (!ServerCommand(Session, METHOD_OPTIONS, FUNC_HIGH_SCORE_GAMES, Payload, &Result))
			{
			printf("%s\n", Result.AsString().GetASCIIZPointer());
			return;
			}

		//	For each adventure, print high score

		if (Result.GetCount() == 0)
			printf("No game records.\n");
		else
			{
			for (i = 0; i < Result.GetCount(); i++)
				{
				const CJSONValue &Record = Result.GetElement(i);
				DWORD dwAdventure = (DWORD)Record.GetElement(FIELD_ADVENTURE).AsInt32();
				if (dwAdventure == 0)
					continue;

				CGameRecord GameRecord;
				if (GameRecord.InitFromJSON(Record) != NOERROR)
					{
					printf("Unable to parse JSON record.\n");
					continue;
					}

				DWORD dwAdventureUNID = GameRecord.GetAdventureUNID();
				CString sUsername = GameRecord.GetUsername();
				int iScore = GameRecord.GetScore();

				printf("%x %s %d\n", dwAdventureUNID, sUsername.GetASCIIZPointer(), iScore);
				}
			}
		}
	}