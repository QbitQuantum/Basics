//--------------------------------------------------------------------
// Function:    Cls_OnTimer
// 
// Description: 
//
// Input:       hwnd  - 
//              id    - 
//              
// Modifies:    
//
// Returns:     
//
//--------------------------------------------------------------------
static void Cls_OnTimer(HWND hwnd, UINT id)
{
    HWND                    hwndChild;
    WORD                    percent;

    if (timerCount < NUM_TICKS) 
    {
      
        if (hwndChild = GetDlgItem(hwnd, IDC_CLOCK_ICON))
        {
            Static_SetIcon(hwndChild, hTimers[timerCount % 8]); 
        }

        if (hwndChild = GetDlgItem(hwnd, IDC_PROGRESS_BAR))
        {
            percent = (WORD)((timerCount * 3) + 7);
            SetWindowWord(hwndChild, GWW_TRAYLEVEL, percent);
            InvalidateRect(hwndChild, NULL, FALSE);
        }

        timerCount++;
    }
    else 
    {
        EndDialog(hwnd, id);
    }

}