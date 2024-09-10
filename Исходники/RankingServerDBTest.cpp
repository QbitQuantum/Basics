	virtual void GetHistoryForParticipant_CB(GetHistoryForParticipant_PostgreSQLImpl *callResult, bool wasCancelled, void *context)
	{
		if (wasCancelled)
			printf("GetHistoryForParticipant call cancelled:\n");
		else if (callResult->dbQuerySuccess==false)
		{
			printf("GetHistoryForParticipant call DB failure:\n");
			printf("%s", callResult->rankingServer->GetLastError());
		}
		else
		{
			printf("GetHistoryForParticipant result:\n");
			printf("[in] participantDbId.primaryKey=%i\n", callResult->participantDbId.primaryKey);
			printf("[in] participantDbId.secondaryKey=%i\n", callResult->participantDbId.secondaryKey);
			printf("[in] gameDbId.primaryKey=%i\n", callResult->gameDbId.primaryKey);
			printf("[in] gameDbId.secondaryKey=%i\n", callResult->gameDbId.secondaryKey);
			printf("[out] %i matches found for this participant.\n", callResult->matchHistoryList.Size());
			unsigned i;
			for (i=0; i < callResult->matchHistoryList.Size(); i++)
			{
				printf("[out] %i. participantBDbId.primaryKey (opponent) =%i\n", i+1, callResult->matchHistoryList[i]->participantBDbId.primaryKey);
				printf("[out] %i. participantBDbId.secondaryKey (opponent) =%i\n", i+1, callResult->matchHistoryList[i]->participantBDbId.secondaryKey);
				printf("[out] %i. participantAScore (us) =%f\n", i+1, callResult->matchHistoryList[i]->participantAScore);
				printf("[out] %i. participantBScore (opponent) =%f\n", i+1, callResult->matchHistoryList[i]->participantBScore);
				printf("[out] %i. participantAOldRating (us) =%f\n", i+1, callResult->matchHistoryList[i]->participantAOldRating);
				printf("[out] %i. participantANewRating (us) =%f\n", i+1, callResult->matchHistoryList[i]->participantANewRating);
				printf("[out] %i. participantBOldRating (opponent) =%f\n", i+1, callResult->matchHistoryList[i]->participantBOldRating);
				printf("[out] %i. participantBNewRating (opponent) =%f\n", i+1, callResult->matchHistoryList[i]->participantBNewRating);
				printf("[out] %i. Match Notes=%s\n", i+1, callResult->matchHistoryList[i]->matchNotes.C_String());
				printf("[out] %i. matchBinaryDataLength=%i\n", i+1, callResult->matchHistoryList[i]->matchBinaryDataLength);

				// Copied from the docs
				struct tm *newtime;
				newtime = _localtime64(& callResult->matchHistoryList[i]->matchTime);
				char buff[30];
				asctime_s( buff, sizeof(buff), newtime );
				printf("[out] %i. matchTime (converted) =\n%s\n", i+1, buff );
			}
		}

		printf("\n");
	}