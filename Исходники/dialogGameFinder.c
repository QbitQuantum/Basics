/*********************************************************
*NAME:          dialogGameFinderBuildList
*AUTHOR:        John Morrison
*Creation Date: 18/1/00
*Last Modified: 23/1/00
*PURPOSE:
* Fills the list box with the current games
*
*ARGUMENTS:
*  hWnd   - Handle to the window
*********************************************************/
void dialogGameFinderBuildList(HWND hWnd) {
    HWND hList; /* The list box handle */
    HWND hJoin; /* The join button */
    int count; /* Looping variable */
    int total; /* Total number of games found */
    char server[FILENAME_MAX]; /* Server name */

    total = currentGamesItemCount(&cg);
    hJoin = GetDlgItem(hWnd, ID_JOIN);
    EnableWindow(hJoin, FALSE);
    EnableWindow(GetDlgItem(hWnd, ID_REJOIN), FALSE);
    if (total > 0) {
        count = 1;
        hList = GetDlgItem(hWnd, IDC_LIST);
        while (count <= total) {
            currentGamesGetServerName(&cg, count, server);
            SendMessage(hList, LB_ADDSTRING, 0, (LPARAM) server);
            SendMessage(hList, LB_SETITEMDATA, count-1, (LPARAM) count-1);
            count++;
        }
    } else {
        /* Display no games found message */
        SetDlgItemTextA(hWnd, IDC_STATUS, langGetText(STR_DLGGAMEFINDER_NOGAMESINPROGRESS));
    }
}