void CProfiling::GenerateLog()
{
    stdstr LogFileName;
    {
        CLog Log;
        Log.Open("Profiling.txt");
        LogFileName = Log.FileName();

        //Get the total time
        int64_t TotalTime = 0;
        for (PROFILE_ENRTY itemTime = m_Entries.begin(); itemTime != m_Entries.end(); itemTime++)
        {
            TotalTime += itemTime->second;
        }

        //Create a sortable list of items
        std::vector<PROFILE_VALUE *> ItemList;
        for (PROFILE_ENRTY Entry = m_Entries.begin(); Entry != m_Entries.end(); Entry++)
        {
            ItemList.push_back(&(*Entry));
        }

        //sort the list with a basic bubble sort
        for (size_t OuterPass = 0; OuterPass < (ItemList.size() - 1); OuterPass++)
        {
            for (size_t InnerPass = 0; InnerPass < (ItemList.size() - 1); InnerPass++)
            {
                if (ItemList[InnerPass]->second < ItemList[InnerPass + 1]->second)
                {
                    PROFILE_VALUE * TempPtr = ItemList[InnerPass];
                    ItemList[InnerPass] = ItemList[InnerPass + 1];
                    ItemList[InnerPass + 1] = TempPtr;
                }
            }
        }

        TIMER_NAME TimerNames[] =
        {
            { Timer_R4300, "R4300" },
            { Timer_RSP_Dlist, "RSP: Dlist" },
            { Timer_RSP_Alist, "RSP: Alist" },
            { Timer_RSP_Unknown, "RSP: Unknown" },
            { Timer_RefreshScreen, "Refresh Screen" },
            { Timer_UpdateScreen, "Update Screen" },
            { Timer_UpdateFPS, "Update FPS" },
            { Timer_FuncLookup, "Function Lookup" },
            { Timer_Done, "Timer_Done" },
            { Timer_GetBlockInfo, "Timer_GetBlockInfo" },
            { Timer_AnalyseBlock, "Timer_AnalyseBlock" },
            { Timer_CompileBlock, "Timer_CompileBlock" },
            { Timer_CompileDone, "Timer_CompileDone" },
        };

        for (size_t count = 0; count < ItemList.size(); count++)
        {
            char Buffer[255];
            double CpuUsage = ((double)ItemList[count]->second / (double)TotalTime) * 100;
            if (CpuUsage <= 0.2) { continue; }
            sprintf(Buffer, "Func 0x%08X", ItemList[count]->first);
            for (int NameID = 0; NameID < (sizeof(TimerNames) / sizeof(TIMER_NAME)); NameID++)
            {
                if (ItemList[count]->first == TimerNames[NameID].Timer)
                {
                    strcpy(Buffer, TimerNames[NameID].Name);
                    break;
                }
            }
            Log.LogF("%s\t%2.2f", Buffer, CpuUsage);
        }
    }

    ResetCounters();
}