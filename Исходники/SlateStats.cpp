void FSlateStatCycleCounter::EndFrame(double CurrentTime)
{
    // Ensure the overhead is tracked at minimum even if all other detail levels are turned off.
    const int32 SLATE_STATS_DETAIL_LEVEL_FORCE_ON = INT_MIN;
    SLATE_CYCLE_COUNTER_SCOPE_FLAT_DETAILED(SLATE_STATS_DETAIL_LEVEL_FORCE_ON, GSlateStatsOverhead);

    // dump stats hierarchy if one was collected this frame.
    if (FSlateStatHierarchy::Get().GetStatEntries().Num() > 0)
    {
        // Place in the <UE4>\<GAME>\Saved\<InFolderName> folder
        FString Filename = FString::Printf(TEXT("%sSlateHierachyStats-%s.csv"), *FPaths::GameSavedDir(), *FDateTime::Now().ToString());
        UE_LOG(LogSlate, Log, TEXT("Dumping Slate Hierarchy Stats to %s..."), *Filename);
        FArchive* OutputStream = IFileManager::Get().CreateFileWriter(*Filename, EFileWrite::FILEWRITE_NoReplaceExisting);

        // some state vars used to print the path of the stat.
        const int kMaxDepth = 100;
        int32 Path[kMaxDepth] = { 0 };
        int32 PathCurrentDepth = -1;
        TCHAR PathStr[4 * kMaxDepth] = { 0 };
        TCHAR* PathStrCurrent = PathStr;
        FSlateStatHierarchy::Get().ComputeExclusiveTimes();

        for (const auto& Entry : FSlateStatHierarchy::Get().GetStatEntries())
        {
            const bool bDescending = Entry.StackDepth > PathCurrentDepth;
            const bool bAscending = Entry.StackDepth < PathCurrentDepth;
            const bool bOverflow = PathCurrentDepth >= (int32)ARRAY_COUNT(Path);
            const int PathPrevDepth = PathCurrentDepth;
            PathCurrentDepth = Entry.StackDepth;

            if (!bOverflow)
            {
                if (bDescending)
                {
                    // we always increment the ordinal, so init to -1 so the first value is zero.
                    Path[PathCurrentDepth] = -1;
                    // put a dot after the current depth and track the new position to put new depths.
                    if (PathCurrentDepth > 0)
                    {
                        while (*PathStrCurrent != 0) ++PathStrCurrent;
                        *PathStrCurrent++ = '.';
                        *PathStrCurrent = 0;
                    }
                }
                else if (bAscending)
                {
                    // back up until we find the dot matching our current depth (or get to depth zero)
                    if (PathCurrentDepth == 0)
                    {
                        // we are at level zero, so just back up all the way. Saves us from checking boundaries in the loop below when we are not at zero depth.
                        PathStrCurrent = PathStr;
                    }
                    else
                    {
                        int LevelsAscended = 0;
                        const int LevelsToAscend = PathPrevDepth - PathCurrentDepth;
                        while (LevelsAscended < LevelsToAscend)
                        {
                            // we are not back to level zero, so we know we will find a '.' eventually.
                            PathStrCurrent -= 2; // back us up before the dot marking this level
                            // keep backing up until we find the dot for the previous level.
                            while (*(PathStrCurrent - 1) != '.')
                            {
                                --PathStrCurrent;
                            }
                            ++LevelsAscended;
                        }
                    }
                }
                // increment the ordinal at this depth
                ++Path[PathCurrentDepth];
                FCString::Sprintf(PathStrCurrent, TEXT("%4d"), Path[PathCurrentDepth]);
            }

            OutputStream->Logf(TEXT("%s,%s,%s,%.8f,%.8f"), PathStr, *Entry.CounterName.ToString(), Entry.CustomName != NAME_None ? *Entry.CustomName.ToString() : TEXT(""), Entry.InclusiveTime*1000, Entry.ExclusiveTime*1000);
            //UE_LOG(LogSlate, Log, TEXT("%s,%s,%s,%.8f,%.8f"), PathStr, *Entry.CounterName.ToString(), Entry.CustomName != NAME_None ? *Entry.CustomName.ToString() : TEXT(""), Entry.InclusiveTime*1000, Entry.ExclusiveTime*1000);
        }
        OutputStream->Close();
        delete OutputStream;
        OutputStream = nullptr;
        UE_LOG(LogSlate, Log, TEXT("Done dumping Slate Hierarchy Stats!"), *Filename);
    }

    // static state for tracking when to re-average the stats
    static double Time = CurrentTime;
    static double LastTime = CurrentTime;
    static double NumFrames = 0.0;
    NumFrames += 1.0;
    Time = CurrentTime;
    const double Delta = Time - LastTime;
    // let things settle down before taking the first real sample
    static double NextDelta = GSlateStatsFlatIntervalWindowSec;
    // ensure this gets reset every frame.
    GAverageInclusiveTimesWereUpdatedThisFrame = false;

    // output flat stats if it's time to do so
    if (Delta > NextDelta)
    {
        LastTime = Time;
        NumFrames = NumFrames / 1000.0; // convert to ms.
        if (GSlateStatsFlatLogOutput > 0)
        {
            UE_LOG(LogSlate, Log, TEXT("Slate Flat Stats"));
            UE_LOG(LogSlate, Log, TEXT("================"));
        }

        // iterate over the counters, outputting their data and resetting them.
        for (const auto Counter : FSlateStatCycleCounter::GetRegisteredCounters())
        {
            Counter->LastComputedAverageInclusiveTime = Counter->InclusiveTime / NumFrames;
            if (GSlateStatsFlatLogOutput > 0)
            {
                UE_LOG(LogSlate, Log, TEXT("%s,%.8f"), *Counter->GetName().ToString(), Counter->LastComputedAverageInclusiveTime);
            }
            Counter->Reset();
        }
        // Frame time is a "virtual stat" so output it like a regular stat.
        if (GSlateStatsFlatLogOutput > 0)
        {
            UE_LOG(LogSlate, Log, TEXT("%s,%.8f"), TEXT("Frame Time"), Delta / NumFrames);
        }

        LastTime = Time;
        NumFrames = 0.0;
        NextDelta = GSlateStatsFlatIntervalWindowSec;
        GAverageInclusiveTimesWereUpdatedThisFrame = true;
    }

    // Clear the hierarchy entries, and tell the system to possibly track hierarchy entries next frame.
    FSlateStatHierarchy::Get().EndFrame(GSlateStatsHierarchyTrigger > 0);
    GSlateStatsHierarchyTrigger = 0;
}