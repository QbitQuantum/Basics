static void OnMultiSelectListPaintListItem(WindowControl * Sender, LKSurface& Surface) {

    #define PICTO_WIDTH 50
    
    Surface.SetTextColor(RGB_BLACK);
    if ((DrawListIndex < iNO_ELEMENTS) &&(DrawListIndex >= 0)) {
        int j;
        static CAirspaceBase airspace_copy;
        int i = DrawListIndex;
        LKASSERT(i < MAX_LIST_ITEMS);
        PixelRect rc = {
            0, 
            0, 
            DLGSCALE(PICTO_WIDTH), 
            static_cast<PixelScalar>(Sender->GetHeight())
        };

        const CAirspace* pAS = NULL;
        int HorDist, Bearing, VertDist;
        double Distance;
        unsigned int idx = 0;
        TCHAR text1[180] = {TEXT("empty")};
        TCHAR text2[180] = {TEXT("empty")};
        TCHAR Comment[80] = {TEXT("")};
        TCHAR Comment1[80] = {TEXT("")};
        Surface.SetBkColor(LKColor(0xFF, 0xFF, 0xFF));
        LKASSERT(i < MAX_LIST_ITEMS);

        switch (Elements[i].type) {
        case IM_AIRSPACE:
            pAS = (CAirspace*) Elements[i].ptr;
            if (pAS) {
                /***********************************************************************
                 * here we use a local copy of the airspace, only common property exists
                 ***********************************************************************/
                airspace_copy = CAirspaceManager::Instance().GetAirspaceCopy(pAS);

                // airspace type already in name?
                if (_tcsnicmp(airspace_copy.Name(), airspace_copy.TypeName(), _tcslen(airspace_copy.TypeName())) == 0) {
                    _stprintf(text1, TEXT("%s"), airspace_copy.Name()); // yes, take name only
                } else {
                    // fixed strings max. 20 NAME_SIZE 30 => max. 30 char
                    _stprintf(text1, TEXT("%s %s"), airspace_copy.TypeName(), airspace_copy.Name());
                }

                CAirspaceManager::Instance().GetSimpleAirspaceAltText(Comment, sizeof (Comment) / sizeof (Comment[0]), airspace_copy.Top());
                CAirspaceManager::Instance().GetSimpleAirspaceAltText(Comment1, sizeof (Comment1) / sizeof (Comment1[0]), airspace_copy.Base());

                CAirspaceManager::Instance().AirspaceCalculateDistance((CAirspace*) pAS, &HorDist, &Bearing, &VertDist);
                _stprintf(text2, TEXT("%3.1f%s (%s - %s)"), (double) HorDist*DISTANCEMODIFY, Units::GetDistanceName(), Comment1, Comment); //8 + 8+3   21

                /****************************************************************
                 * for drawing the airspace pictorial, we need the original data.
                 * copy contain only base class property, not geo data,
                 * original data are shared ressources !
                 * for that we need to grant all called methods are thread safe
                 ****************************************************************/
                pAS->DrawPicto(Surface, rc);
            }
            break;


        case IM_TASK_PT:
        case IM_WAYPOINT:
            idx = -1;
            LockTaskData(); // protect from external task changes

            if (Elements[i].type == IM_TASK_PT) {
                if(ValidTaskPointFast(Elements[i].iIdx)) {
                    idx = Task[Elements[i].iIdx].Index;
                }
            } else {
                if(ValidWayPointFast(Elements[i].iIdx)) {
                    idx = Elements[i].iIdx;
                }
            }

            // This is not a solution. It will avoid a crash but the solution is to understand
            // why we are getting a wrong idx, eventually. If ever we got a wrong idx!
            // And then this "fix" should be changed to something more useful, instead of 
            // adopting a totally wrong waypoint for task.
            assert(idx < WayPointList.size());
            if(idx < WayPointList.size()) {

                if (WayPointList[idx].Comment != NULL) {
                    LK_tcsncpy(Comment, WayPointList[idx].Comment, 30);
                } else {
                    _tcscpy(Comment, TEXT(""));
                }

                DistanceBearing(GPS_INFO.Latitude, GPS_INFO.Longitude, WayPointList[idx].Latitude,
                                WayPointList[idx].Longitude, &Distance, NULL);

                if (Elements[i].type != IM_TASK_PT) {
                    if (WayPointCalc[idx].IsLandable) {
                        MapWindow::DrawRunway(Surface, &WayPointList[idx], rc, nullptr, 1.5, true);

                        if (WayPointCalc[idx].IsAirport) {
                            // remove spaces from frequency
                            for (j = 1; j < (CUPSIZE_FREQ); j++)
                                if (WayPointList[idx].Freq[CUPSIZE_FREQ - j] == ' ')
                                    WayPointList[idx].Freq[CUPSIZE_FREQ - j] = '\0';

                            if (_tcslen(WayPointList[idx].Freq) > 2)
                                _stprintf(text1, TEXT("%s %s MHz"), WayPointList[idx].Name,
                                          WayPointList[idx].Freq);
                            else
                                _stprintf(text1, TEXT("%s"), WayPointList[idx].Name);
                        } else {
                            if (WayPointList[idx].Comment != NULL)
                                _stprintf(text1, TEXT("%s %s"), WayPointList[idx].Name, Comment);
                            else
                                _stprintf(text1, TEXT("%s"), WayPointList[idx].Name);
                        }

                        if ((WayPointList[idx].RunwayLen >= 10) ||
                            (WayPointList[idx].RunwayDir > 0)) {
                            _stprintf(text2, TEXT("%3.1f%s (%i%s  %02i/%02i  %i%s)"),
                                      Distance * DISTANCEMODIFY, Units::GetDistanceName(),
                                      (int) (WayPointList[idx].Altitude * ALTITUDEMODIFY),
                                      Units::GetAltitudeName(),
                                      (int) (WayPointList[idx].RunwayDir / 10.0 + 0.5),
                                      (int) (AngleLimit360(WayPointList[idx].RunwayDir + 180.0) /
                                             10.0 + 0.5),
                                      (int) ((double) WayPointList[idx].RunwayLen * ALTITUDEMODIFY),
                                      Units::GetAltitudeName());
                        } else {
                            _stprintf(text2, TEXT("%3.1f%s (%i%s) "), Distance * DISTANCEMODIFY,
                                      Units::GetDistanceName(),
                                      (int) (WayPointList[idx].Altitude * ALTITUDEMODIFY),
                                      Units::GetAltitudeName());
                        }

                    }// waypoint isLandable
                    else {
                        MapWindow::DrawWaypointPicto(Surface, rc, &WayPointList[idx]);
                        _stprintf(text1, TEXT("%s %s"), WayPointList[idx].Name, Comment);

                        _stprintf(text2, TEXT("%3.1f%s (%i%s)"), Distance * DISTANCEMODIFY,
                                  Units::GetDistanceName(),
                                  (int) (WayPointList[idx].Altitude * ALTITUDEMODIFY),
                                  Units::GetAltitudeName());
                    }

                }// Elements IM_TASK
                else {
                    int iTaskIdx = Elements[i].iIdx;
                    MapWindow::DrawTaskPicto(Surface, iTaskIdx, rc, 3000);
                    int iLastTaskPoint = 0;

                    while (ValidTaskPoint(iLastTaskPoint))
                        iLastTaskPoint++;

                    iLastTaskPoint--;

                    if (iTaskIdx == 0) {
                        // _@M2301_  "S"    # S = Start Task point
                        _stprintf(text1, TEXT("%s: (%s)"), MsgToken(2301), WayPointList[idx].Name);
                        _stprintf(text2, TEXT("Radius %3.1f%s (%i%s)"),
                                  StartRadius * DISTANCEMODIFY, Units::GetDistanceName(),
                                  (int) (WayPointList[idx].Altitude * ALTITUDEMODIFY),
                                  Units::GetAltitudeName());
                    } else {
                        if (iTaskIdx == iLastTaskPoint) {
                            //	_@M2303_  "F"                 // max 30         30 => max 60 char
                            _stprintf(text1, TEXT("%s: (%s) "), MsgToken(2303),
                                      WayPointList[idx].Name);
                            _stprintf(text2, TEXT("Radius %3.1f%s (%i%s)"),
                                      FinishRadius * DISTANCEMODIFY, Units::GetDistanceName(),
                                      (int) (WayPointList[idx].Altitude * ALTITUDEMODIFY),
                                      Units::GetAltitudeName());
                        } else {
                            //   _@M2302_  "T"    # F = Finish point            // max 30         30 => max 60 char
                            _stprintf(text1, TEXT("%s%i: (%s) "), MsgToken(2302), iTaskIdx,
                                      WayPointList[idx].Name);
                            double SecRadius = 0;

                            SecRadius = SectorRadius;
                            if (AATEnabled) {
                                if (Task[iTaskIdx].AATType == SECTOR)
                                    SecRadius = Task[iTaskIdx].AATSectorRadius;
                                else
                                    SecRadius = Task[iTaskIdx].AATCircleRadius;
                            }

                            _stprintf(text2, TEXT("Radius %3.1f%s (%i%s)"),
                                      SecRadius * DISTANCEMODIFY, Units::GetDistanceName(),
                                      (int) (WayPointList[idx].Altitude * ALTITUDEMODIFY),
                                      Units::GetAltitudeName());
                        }
                    }

                }
            }
            UnlockTaskData(); // protect from external task changes
            break;
        }

        /********************
         * show text
         ********************/
        Surface.SetBackgroundTransparent();
        Surface.SetTextColor(RGB_BLACK);
        Surface.DrawText(rc.right + DLGSCALE(2), DLGSCALE(2), text1);
        int ytext2 = Surface.GetTextHeight(text1);
        Surface.SetTextColor(RGB_DARKBLUE);
        Surface.DrawText(rc.right + DLGSCALE(2), ytext2, text2);

    }
}