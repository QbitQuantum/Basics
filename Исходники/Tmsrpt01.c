BOOL FAR TMSRPT01(TMSRPTPassedDataDef *pPassedData)
{
  REPORTPARMSDef REPORTPARMS;
  HFILE hfOutputFile;
  BOOL  bKeepGoing = FALSE;
  BOOL  bRC;
  int   maxSelectedPatternNodes = 100;
  int   nI;
  int   nJ;
  int   nK;
  int   nL;
  int   numSelectedPatternNodes;
  int   rcode2;

  long  *pSelectedPatternNodes = NULL;

  pPassedData->nReportNumber = 0;
  pPassedData->numDataFiles = 1;
//
//  See what he wants
//
  REPORTPARMS.nReportNumber = pPassedData->nReportNumber;
  REPORTPARMS.ROUTESrecordID = m_RouteRecordID;
  REPORTPARMS.SERVICESrecordID = m_ServiceRecordID;
  REPORTPARMS.PATTERNNAMESrecordID = NO_RECORD;
  REPORTPARMS.COMMENTSrecordID = NO_RECORD;
  REPORTPARMS.pRouteList = NULL;
  REPORTPARMS.pServiceList = NULL;
  REPORTPARMS.flags = RPFLAG_ROUTES | RPFLAG_SERVICES | RPFLAG_PATTERNNAMES | RPFLAG_COMMENTS;
  bRC = DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_RPTPARMS),
        hWndMain, (DLGPROC)RPTPARMSMsgProc, (LPARAM)&REPORTPARMS);
  if(!bRC)
  {
    return(FALSE);
  }
//
//  Check the list of routes and services
//
  if(REPORTPARMS.numRoutes == 0 || REPORTPARMS.numServices == 0)
  {
    goto deallocate;
  }
//
//  Open the output file
//
  strcpy(tempString, szReportsTempFolder);
  strcat(tempString, "\\tmsrpt01.txt");
  hfOutputFile = _lcreat(tempString, 0);
  if(hfOutputFile == HFILE_ERROR)
  {
    LoadString(hInst, ERROR_202, szFormatString, sizeof(szFormatString));
    sprintf(szarString, szFormatString, tempString);
    MessageBeep(MB_ICONSTOP);
    MessageBox((HWND)NULL, szarString, TMS, MB_ICONSTOP);
    goto deallocate;
  }
  strcpy(pPassedData->szReportDataFile[0], tempString);
//
//  Allocate the nodes arrays
//
  pSelectedPatternNodes = (long *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(long) * maxSelectedPatternNodes); 
  if(pSelectedPatternNodes == NULL)
  {
    AllocationError(__FILE__, __LINE__, FALSE);
    goto deallocate;
  }
//
//  Load any header and trailer special characters
//
  LoadHeadersAndTrailers01();
//
//  Loop through the routes
//
  SetCursor(hCursorWait);
  for(nI = 0; nI < REPORTPARMS.numRoutes; nI++)
  {
    ROUTESKey0.recordID = REPORTPARMS.pRouteList[nI];
    rcode2 = btrieve(B_GETEQUAL, TMS_ROUTES, &ROUTES, &ROUTESKey0, 0);
    if(rcode2 != 0)
    {
      continue;
    }
//
//  Loop through the services
//
    for(nJ = 0; nJ < REPORTPARMS.numServices; nJ++)
    {
      SERVICESKey0.recordID = REPORTPARMS.pServiceList[nJ];
      rcode2 = btrieve(B_GETEQUAL, TMS_SERVICES, &SERVICES, &SERVICESKey0, 0);
      if(rcode2 != 0)
      {
        continue;
      }
//
//  Loop through the directions
//
      for(nK = 0; nK < 2; nK++)
      {
        if(ROUTES.DIRECTIONSrecordID[nK] == NO_RECORD)
        {
          continue;
        }
//
//  Find the selected pattern nodes
//
        numSelectedPatternNodes = 0;
        PATTERNNAMESKey0.recordID = REPORTPARMS.PATTERNNAMESrecordID;
        rcode2 = btrieve(B_GETEQUAL, TMS_PATTERNNAMES, &PATTERNNAMES, &PATTERNNAMESKey0, 0);
        if(rcode2 == 0)
        {
          PATTERNSKey2.ROUTESrecordID = REPORTPARMS.pRouteList[nI];
          PATTERNSKey2.SERVICESrecordID = REPORTPARMS.pServiceList[nJ];
          PATTERNSKey2.directionIndex = nK;
          PATTERNSKey2.PATTERNNAMESrecordID = PATTERNNAMES.recordID;
          PATTERNSKey2.nodeSequence = NO_RECORD;
          rcode2 = btrieve(B_GETGREATEROREQUAL, TMS_PATTERNS, &PATTERNS, &PATTERNSKey2, 2);
          while(rcode2 == 0 &&
                PATTERNS.ROUTESrecordID == REPORTPARMS.pRouteList[nI] &&
                PATTERNS.SERVICESrecordID == REPORTPARMS.pServiceList[nJ] &&
                PATTERNS.directionIndex == nK &&
                PATTERNS.PATTERNNAMESrecordID == PATTERNNAMES.recordID)
          {
            if(!(PATTERNS.flags & PATTERNS_FLAG_BUSSTOP))
            {
              pSelectedPatternNodes[numSelectedPatternNodes++] = PATTERNS.NODESrecordID;
              if(numSelectedPatternNodes >= maxSelectedPatternNodes)
              {
                maxSelectedPatternNodes += 50;
                pSelectedPatternNodes = (long *)HeapReAlloc(GetProcessHeap(),
                      HEAP_ZERO_MEMORY, pSelectedPatternNodes, sizeof(long) * maxSelectedPatternNodes); 
                if(pSelectedPatternNodes == NULL)
                {
                  AllocationError(__FILE__, __LINE__, TRUE);
                  goto deallocate;
                }
              }
            }
            rcode2 = btrieve(B_GETNEXT, TMS_PATTERNS, &PATTERNS, &PATTERNSKey2, 2);
          }
        }
        if(numSelectedPatternNodes == 0)
        {
          continue;
        }
//
//  Write out the id record
//
        strcpy(tempString, szRSDHeader);
        strncpy(szarString, ROUTES.number, ROUTES_NUMBER_LENGTH);
        trim(szarString, ROUTES_NUMBER_LENGTH);
        strcat(tempString, szarString);
        strcat(tempString, " ");
        strncpy(szarString, ROUTES.name, ROUTES_NAME_LENGTH);
        trim(szarString, ROUTES_NAME_LENGTH);
        strcat(tempString, szarString);
        strcat(tempString, " ");
        DIRECTIONSKey0.recordID = ROUTES.DIRECTIONSrecordID[nK];
        btrieve(B_GETEQUAL, TMS_DIRECTIONS, &DIRECTIONS, &DIRECTIONSKey0, 0);
        strncpy(szarString, DIRECTIONS.abbrName, DIRECTIONS_ABBRNAME_LENGTH);
        trim(szarString, DIRECTIONS_ABBRNAME_LENGTH);
        strcat(tempString, szarString);
        strcat(tempString, " ");
        strncpy(szarString, SERVICES.name, SERVICES_NAME_LENGTH);
        trim(szarString, SERVICES_NAME_LENGTH);
        strcat(tempString, szarString);
        strcat(tempString, szRSDTrailer);
        strcat(tempString, "\r\n");
        _lwrite(hfOutputFile, tempString, strlen(tempString));
//
//  Write out the number of nodes record
//
        strcpy(tempString, szNumNodesHeader);
        if(strcmp(szNumNodesHeader, "") != 0)
        {
          strcat(tempString, " ");
        }
        sprintf(szarString, "%d", numSelectedPatternNodes);
        strcat(tempString, szarString);
        strcat(tempString, szNumNodesTrailer);
        strcat(tempString, "\r\n");
        _lwrite(hfOutputFile, tempString, strlen(tempString));
//
//  Cycle through, and write out, the pattern nodes
//
        for(nL = 0; nL < numSelectedPatternNodes; nL++)
        {
          strcpy(tempString, szEachNodeHeader);
          NODESKey0.recordID = pSelectedPatternNodes[nL];
          btrieve(B_GETEQUAL, TMS_NODES, &NODES, &NODESKey0, 0);
          strncpy(szarString, NODES.intersection, NODES_INTERSECTION_LENGTH);
          trim(szarString, NODES_INTERSECTION_LENGTH);
          strcat(tempString, szarString);
          strcat(tempString, szEachNodeTrailer);
          strcat(tempString, "\r\n");
          _lwrite(hfOutputFile, tempString, strlen(tempString));
        }  // nL
      }  // nK
    }  // nJ
  }  // nI
  bKeepGoing = TRUE;
//
//  Free allocated memory
//
  deallocate:
    TMSHeapFree(REPORTPARMS.pRouteList);
    TMSHeapFree(REPORTPARMS.pServiceList);
    TMSHeapFree(pSelectedPatternNodes);
    _lclose(hfOutputFile);
    SetCursor(hCursorArrow);
    if(!bKeepGoing)
    {
      return(FALSE);
    }
//
//  All done
//
  return(TRUE);
}