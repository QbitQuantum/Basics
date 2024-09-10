// Author & Date:   Almut Branner    12 May 2003
// Purpose: Replace this static control with this window
// Inputs:
//  rcParentWindow - the window this is going to be placed into
//  rcNewWindow - the window that is to be created
//  nControlID - the ID of the control (from the resource editor)
void ReplaceWindowControl(const CWnd &rcParentWindow, CWnd &rcNewWindow, int nControlID)
{
    CWnd *pStatic = rcParentWindow.GetDlgItem(nControlID);

    // For debug mode
    ASSERT(pStatic != 0);

    // For released code
    if (pStatic == 0)
        return;

    CRect rctWindowSize;

    DWORD frmstyle   = pStatic->GetStyle();
    DWORD frmexstyle = pStatic->GetExStyle();

    pStatic->GetWindowRect(rctWindowSize);      // Get window coord.
    rcParentWindow.ScreenToClient(rctWindowSize);              // change to client coord.
    pStatic->DestroyWindow();

    CWnd *pParent = const_cast<CWnd *>(&rcParentWindow);
    rcNewWindow.CreateEx(frmexstyle, NULL, NULL, frmstyle, rctWindowSize, pParent, nControlID);

    // Use for debugging
    // AllocConsole();
}