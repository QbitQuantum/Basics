int TMainForm::FindPath()
{
    Image1->Picture->Assign(Image2->Picture);

    String str =
        "Finding path from " +
        (String)startX + ":" + (String)startY +
        " to " +
        (String)endX + ":" + (String)endY +
        " . . .";
    Memo1->Lines->Add(str);

	double start_ms = 0;

    if (HighPerformanceTimerSupport)
    {
		LARGE_INTEGER nTime;
        QueryPerformanceCounter(&nTime);
        start_ms = (nTime.QuadPart) * performanceCounterToMs;
    }
	else
		start_ms = GetTickCount();

    bool finded = false;

    if (startX>=0 && startX<Pathfinder.mapWidth &&
        endX>=0 && endX<Pathfinder.mapWidth &&
        startY>=0 && startY<Pathfinder.mapHeight &&
        endY>=0 && endY<Pathfinder.mapHeight
        )
    {
        // Finds a path using A*
        finded = Pathfinder.FindPath( startX, startY, endX, endY )==CPathfinder::found;
    }
    else
    {
        str.sprintf(
            " Out of data bounds!"
            );        
        Memo1->Lines->Add(str);
    }

    //////////////////////////////////////////////////////////////////////

    double end_ms = 0;

	if (HighPerformanceTimerSupport)
    {
		LARGE_INTEGER nTime;
        QueryPerformanceCounter(&nTime);
        end_ms = (nTime.QuadPart) * performanceCounterToMs;
    }
	else
		end_ms = GetTickCount();

    if (finded)
    {
        // storing finded path

        for (s32 p=0; p<2*Pathfinder.pathLength; p+=2)
        {
            int x = Pathfinder.pathBank[p];
            int y = Pathfinder.pathBank[p+1];

            Image1->Canvas->Pixels[x][y] = 0x00ff0000;     
        }

        str.sprintf( " Finded!" );
        Memo1->Lines->Add(str);
    }
    else
    {
        str.sprintf( " Can't find!" );
        Memo1->Lines->Add(str);
    }

    str.sprintf(
        " Elapsed %.4f ms",
        end_ms-start_ms
        );   
    Memo1->Lines->Add(str);
}