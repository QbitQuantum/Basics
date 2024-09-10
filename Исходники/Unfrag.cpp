// Main Initialization
int wmain (int argc, wchar_t **argv)
{
    vector<wstring>       Drives;
    vector<Defragment *> Defrags;
    DefragType           DefragMode = DefragInvalid;

    PrintBanner ();

    // Parse command line arguments
    bool ValidCmdLine = false;
    for (int c = 0; c < argc; c++)
    {
        if (wcslen(argv[c]) == 2  &&  argv[c][1] == L':')
        {
            Drives.push_back (wcsupr(argv[c]));
        }
        else
        if (argv[c][0] == L'-'  ||  argv[c][0] == L'/'  &&  wcslen(argv[c]) == 2)
        {
            switch (tolower(argv[c][1]))
            {
                case L'?' :
                case L'h' :
                    FraggerHelp ();
                    return (0);

                case L'f' :
                    if (DefragMode != DefragInvalid)
                    {
                        ValidCmdLine = false;
                        break;
                    }
                    DefragMode = DefragFast;
                    ValidCmdLine = true;
                    break;

                case L'e' :
                    if (DefragMode != DefragInvalid)
                    {
                        ValidCmdLine = false;
                        break;
                    }
                    DefragMode = DefragExtensive;
                    ValidCmdLine = true;
                    break;

            }
        }
    }

    if (DefragMode == DefragInvalid)
        ValidCmdLine = false;

    if (!ValidCmdLine)
    {
        wprintf (L"Invalid command-line options. Use '%s -?' for help.\n", argv[0]);
        return (0);
    }

    // Check OS requirements
    if (!CheckWinVer())
    {
        wprintf (L"Fatal Error: This program requires Windows 2000.\n");
        return (0);
    }

	for (size_t d = 0; d < Drives.size (); d++)
    {
        HANDLE TossMe;
        Defrags.push_back (StartDefragThread (Drives[d], DefragMode, TossMe));
    }

    for (size_t d = 0; d < Drives.size () - 1; d++)
        wprintf (L"\n ");

    bool Continue = true;
    HANDLE Screen;

    Screen = GetStdHandle (STD_OUTPUT_HANDLE);
    while (Continue)
    {
        Sleep (25);

        // Get current screen coords
        CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;

        GetConsoleScreenBufferInfo (Screen, &ScreenInfo);

        // Now set back to the beginning
        ScreenInfo.dwCursorPosition.X = 0;
        ScreenInfo.dwCursorPosition.Y -= Drives.size();
        SetConsoleCursorPosition (Screen, ScreenInfo.dwCursorPosition);

        for (size_t d = 0; d < Drives.size (); d++)
        {
            wprintf (L"\n%6.2f%% %-70s", Defrags[d]->GetStatusPercent(), Defrags[d]->GetStatusString().c_str());
        }

        // Determine if we should keep going
        Continue = false;
        for (size_t d = 0; d < Drives.size (); d++)
        {
            if (!Defrags[d]->IsDoneYet()  &&  !Defrags[d]->HasError())
                Continue = true;
        }
    }

#if 0
    // Loop through the drives list
    for (int d = 0; d < Drives.size(); d++)
    {
        DriveVolume *Drive;

        Drive = new DriveVolume;

        // First thing: build a file list.
        wprintf (L"Opening volume %s ...", Drives[d].c_str());
        if (!Drive->Open (Drives[d]))
        {
            wprintf (L"FAILED\n\n");
            delete Drive;
            continue;
        }
        wprintf (L"\n");

        wprintf (L"    Getting drive bitmap ...");
        if (!Drive->GetBitmap ())
        {
            wprintf (L"FAILED\n\n");
            delete Drive;
            continue;
        }
        wprintf (L"\n");

        wprintf (L"    Obtaining drive geometry ...");
        if (!Drive->ObtainInfo ())
        {
            wprintf (L"FAILED\n\n");
            delete Drive;
            continue;
        }
        wprintf (L"\n");

        wprintf (L"    Building file database for drive %s ...", Drives[d].c_str());
        if (!Drive->BuildFileList ())
        {
            wprintf (L"FAILED\n\n");
            delete Drive;
            continue;
        }
        wprintf (L"\n");

        wprintf (L"    %u files\n", Drive->GetDBFileCount ());

        // Analyze only?
        if (DefragMode == DefragAnalyze)
        {
            uint64 UsedBytes  = 0;  // total bytes used, with cluster size considerations
            uint64 TotalBytes = 0;  // total bytes used
            uint64 SlackBytes = 0;  // wasted space due to slack
            uint32 Fragged    = 0;  // fragmented files

            wprintf (L"    Analyzing ...");
            if (VerboseMode)
                wprintf (L"\n");

            for (int i = 0; i < Drive->GetDBFileCount(); i++)
            {
                uint64 Used;
                uint64 Slack;
                FileInfo Info;

                Info = Drive->GetDBFile (i);

                // Compute total used disk space
                Used = ((Info.Size + Drive->GetClusterSize() - 1) / Drive->GetClusterSize()) * Drive->GetClusterSize();
                Slack = Used - Info.Size;

                UsedBytes += Used;
                SlackBytes += Slack;
                TotalBytes += Info.Size;

                if (VerboseMode)
                {
                    wprintf (L"    %s%s, ", Drive->GetDBDir (Info.DirIndice).c_str(), Info.Name.c_str());

                    if (Info.Attributes.AccessDenied)
                        wprintf (L"access was denied\n");
                    else
                    {
                        if (Info.Attributes.Unmovable == 1)
                            wprintf (L"unmovable, ");

                        wprintf (L"%I64u bytes, %I64u bytes on disk, %I64u bytes slack, %u fragments\n",
                            Info.Size, Used, Slack, Info.Fragments.size());
                    }
                }

                if (Info.Fragments.size() > 1)
                    Fragged++;
            }

            if (!VerboseMode)
                wprintf (L"\n");

            // TODO: Make it not look like ass
            wprintf (L"\n");
            wprintf (L"    Overall Analysis\n");
            wprintf (L"    ----------------\n");
            wprintf (L"    %u clusters\n", Drive->GetClusterCount ());
            wprintf (L"    %u bytes per cluster\n", Drive->GetClusterSize());
            wprintf (L"    %I64u total bytes on drive\n", (uint64)Drive->GetClusterCount() * (uint64)Drive->GetClusterSize());
            wprintf (L"\n");
            wprintf (L"    %u files\n", Drive->GetDBFileCount ());
            wprintf (L"    %u contiguous files\n", Drive->GetDBFileCount () - Fragged);
            wprintf (L"    %u fragmented files\n", Fragged);
            wprintf (L"\n");
            wprintf (L"    %I64u bytes\n", TotalBytes);
            wprintf (L"    %I64u bytes on disk\n", UsedBytes);
            wprintf (L"    %I64u bytes slack\n", SlackBytes);
        }

        // Fast defragment!
        if (DefragMode == DefragFast  ||  DefragMode == DefragExtensive)
        {
            uint32 i;
            uint64 FirstFreeLCN;
            wchar_t PrintName[80];
            int Width = 66;

            if (DefragMode == DefragFast)
                wprintf (L"    Performing fast file defragmentation ...\n");
            else
            if (DefragMode == DefragExtensive)
                wprintf (L"    Performing extensive file defragmentation\n");

            // Find first free LCN for speedier searches ...
            Drive->FindFreeRange (0, 1, FirstFreeLCN);

            for (i = 0; i < Drive->GetDBFileCount(); i++)
            {
                FileInfo Info;
                bool Result;
                uint64 TargetLCN;

                wprintf (L"\r");

                Info = Drive->GetDBFile (i);

                FitName (PrintName, Drive->GetDBDir (Info.DirIndice).c_str(), Info.Name.c_str(), Width);
                wprintf (L"    %6.2f%% %-66s", (float)i / (float)Drive->GetDBFileCount() * 100.0f, PrintName);

                // Can't defrag 0 byte files :)
                if (Info.Fragments.size() == 0)
                    continue;

                // If doing fast defrag, skip non-fragmented files
                if (Info.Fragments.size() == 1  &&  DefragMode == DefragFast)
                    continue;

                // Find a place that can fit the file
                Result = Drive->FindFreeRange (FirstFreeLCN, Info.Clusters, TargetLCN);

                // If we're doing an extensive defrag and the file is already defragmented
                // and if its new location would be after its current location, don't
                // move it.
                if (DefragMode == DefragExtensive  &&  Info.Fragments.size() == 1)
                {
                    if (TargetLCN > Info.Fragments[0].StartLCN)
                        continue;
                }

                // Otherwise, defrag0rize it!
                if (Result)
                {
                    bool Success = false;

                    if (Drive->MoveFileDumb (i, TargetLCN))
                        Success = true;
                    else
                    {   // hmm, look for another area to move it to
                        Result = Drive->FindFreeRange (TargetLCN + 1, Info.Clusters, TargetLCN);
                        if (Result)
                        {
                            if (Drive->MoveFileDumb (i, TargetLCN))
                                Success = true;
                            else
                            {   // Try updating the drive bitmap
                                if (Drive->GetBitmap ())
                                {
                                    Result = Drive->FindFreeRange (0, Info.Clusters, TargetLCN);
                                    if (Result)
                                    {
                                        if (Drive->MoveFileDumb (i, TargetLCN))
                                            Success = true;
                                    }
                                }
                            }
                        }
                    }

                    if (!Success)
                        wprintf (L"\n        -> failed\n");

                    Drive->FindFreeRange (0, 1, FirstFreeLCN);
                }
            }

            wprintf (L"\n");
        }
        wprintf (L"Closing volume %s ...", Drives[d].c_str());
        delete Drive;
        wprintf (L"\n");
    }
#endif

    return (0);
}