BOOL CQuestInfo::LoadQuestInfo(char* Buffer, int iSize)
{

	CWzMemScript WzMemScript;
	int Token;
	int n;

	WzMemScript.SetBuffer(Buffer, iSize);
	this->Init();

	n = 0;

	while ( true )
	{
		Token = WzMemScript.GetToken();

		if ( Token == 2 )
		{
			break;
		}
		else
		{
			if ( Token == 1 )
			{
				int Type = WzMemScript.GetNumber();

				if ( Type == 0 )
				{
					Token = WzMemScript.GetToken();
					auto int iQuestIndex = WzMemScript.GetNumber();
					this->QuestInfo[iQuestIndex].QuestIndex = iQuestIndex;

					Token = WzMemScript.GetToken();
					this->QuestInfo[iQuestIndex].QuestStartType = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					this->QuestInfo[iQuestIndex].QuestStartSubType = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					strcpy( this->QuestInfo[iQuestIndex].Name, WzMemScript.GetString());

					this->QuestInfo[iQuestIndex].QuestSubInfoCount = 0;

					while ( true )
					{
						int iSubInfoCount = this->QuestInfo[iQuestIndex].QuestSubInfoCount;

						Token = WzMemScript.GetToken();

						if ( Token == 0 )
						{
							if ( strcmp("end", WzMemScript.GetString()) == 0 )
							{
								break;
							}
						}
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].QuestType = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].NeedType = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].NeedSubType = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].ItemLevel = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].NeedNumber = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].NeedTargetMinLevel = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].NeedTargetMaxLevel = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].NeedDropRate = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].RewardType = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].RewardSubType = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].RewardCount = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].LinkConditionIndex = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].ContextBeforeReg = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].ContextAfterReg = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].ContextCompleteQuest = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].ContextQuestClear = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].RequireClass[0] = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].RequireClass[1] = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].RequireClass[2] = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].RequireClass[3] = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						this->QuestInfo[iQuestIndex].QuestSubInfo[iSubInfoCount].RequireClass[4] = WzMemScript.GetNumber();

						this->QuestInfo[iQuestIndex].QuestSubInfoCount++;

					
					}
					
					LogAdd("[Quest] (%s) Load : Index %d, SubInfoCount %d",
						this->QuestInfo[iQuestIndex].Name, iQuestIndex,
						this->QuestInfo[iQuestIndex].QuestSubInfoCount );
						this->m_QuestCount++;
				}
				else if ( Type == 1 )
				{
					Token = WzMemScript.GetToken();
					auto int iQuestIndex = WzMemScript.GetNumber();

					while ( true )
					{
						auto int iFailInfoCount = this->QuestInfo[iQuestIndex].QuestConditionCount;
						Token = WzMemScript.GetToken();

						if ( Token == 0 )
						{
							if ( strcmp("end", WzMemScript.GetString()) == 0 )
							{
								break;
							}
						}	
							this->QuestInfo[iQuestIndex].QuestCondition[iFailInfoCount].Index = WzMemScript.GetNumber();

							Token = WzMemScript.GetToken();
							this->QuestInfo[iQuestIndex].QuestCondition[iFailInfoCount].NeedQuestIndex = WzMemScript.GetNumber();

							Token = WzMemScript.GetToken();
							this->QuestInfo[iQuestIndex].QuestCondition[iFailInfoCount].MinLevel = WzMemScript.GetNumber();

							Token = WzMemScript.GetToken();
							this->QuestInfo[iQuestIndex].QuestCondition[iFailInfoCount].MaxLevel = WzMemScript.GetNumber();

							Token = WzMemScript.GetToken();
							this->QuestInfo[iQuestIndex].QuestCondition[iFailInfoCount].ReqStr = WzMemScript.GetNumber();

							Token = WzMemScript.GetToken();
							this->QuestInfo[iQuestIndex].QuestCondition[iFailInfoCount].NeedZen = WzMemScript.GetNumber();

							Token = WzMemScript.GetToken();
							this->QuestInfo[iQuestIndex].QuestCondition[iFailInfoCount].StartContext = WzMemScript.GetNumber();

							this->QuestInfo[iQuestIndex].QuestConditionCount++;
						
					}
				}
				else
				{
					MsgBox("Quest Info Read Fail");
					fclose(SMDFile);
					return false;
				}
			}
		}
	}

	this->InitQuestItem();
	return true;
}