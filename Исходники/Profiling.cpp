	//Generate a log file with the current results, this will also reset the counters
	void GenerateLog   ( void )
	{
		stdstr LogFileName;
		{
			CLog Log;
			Log.Open("RSP Profiling.txt");
			LogFileName = Log.FileName();

			//Get the total time
			__int64 TotalTime = 0;
			for (PROFILE_ENRTY itemTime = m_Entries.begin(); itemTime != m_Entries.end(); itemTime++ )
			{
				TotalTime += itemTime->second;
			}

			//Create a sortable list of items
			std::vector<PROFILE_VALUE *> ItemList;
			for (PROFILE_ENRTY Entry = m_Entries.begin(); Entry != m_Entries.end(); Entry++ )
			{
				ItemList.push_back(&(*Entry));
			}

			//sort the list with a basic bubble sort
			if (ItemList.size() > 0)
			{
				for (size_t OuterPass = 0; OuterPass < (ItemList.size() - 1); OuterPass++ )
				{
					for (size_t InnerPass = 0; InnerPass < (ItemList.size() - 1); InnerPass++ )
					{
						if (ItemList[InnerPass]->second < ItemList[InnerPass + 1]->second)
						{
							PROFILE_VALUE * TempPtr = ItemList[InnerPass];
							ItemList[InnerPass] = ItemList[InnerPass + 1];
							ItemList[InnerPass + 1] = TempPtr;
						}
					}
				}
			}

			TIMER_NAME TimerNames[] = {
				{Timer_Compiling,     "RSP: Compiling"},
				{Timer_RSP_Running,   "RSP: Running"},
				{Timer_R4300_Running, "R4300: Running"},
				{Timer_RDP_Running,   "RDP: Running"},
			};

			for (size_t count = 0; count < ItemList.size(); count++ )
			{
				char Buffer[255];
				float CpuUsage = (float)(((double)ItemList[count]->second / (double)TotalTime) * 100);

				if (CpuUsage <= 0.2) { continue; }
				sprintf(Buffer, "Func 0x%08X", ItemList[count]->first);
				for (int NameID = 0; NameID < (sizeof(TimerNames) / sizeof(TIMER_NAME)); NameID++)
				{
					if (ItemList[count]->first == (DWORD)TimerNames[NameID].Timer)
					{
						strcpy(Buffer,TimerNames[NameID].Name);
						break;
					}
				}
				Log.LogF("%s\t%2.2f",Buffer,  CpuUsage);
			}
		}

		ShellExecute(NULL,"open",LogFileName.c_str(),NULL,NULL,SW_SHOW);
		ResetCounters();
	}