//************************************
// Method:    LoadProcessWindow
// FullName:  ProcessWindowCollection::LoadProcessWindow
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: HWND hNewWindow_i
// Parameter: const DWORD dwWindowThreadId_i
//************************************
bool ProcessWindowCollection::LoadProcessWindow( HWND hNewWindow_i )
{
    // Prepare window data
    PWindow pWindow = new Window;

    // Window details
    pWindow->ExtractWindowDetails( hNewWindow_i );

    // Get parent child map
    WindowMap& wmWndMap = GetWindowMap();

    PWindow pParentWindow = 0;
    if( wmWndMap.Lookup( pWindow->GetParentHandle(), pParentWindow ) && pParentWindow )
    {
        // Add this window to the list of child windows of parent window
        pParentWindow->GetChildWindowList().AddTail( pWindow );
    }
    else
    {
        // Add to main window list
        GetProcessWindowList().AddTail( pWindow );
    }// End if

    // Insert item to map
    wmWndMap[pWindow->GetHandle()] = pWindow;

    // Get all child windows for this window
    EnumChildWindows( hNewWindow_i, 
					  EnumerateChildWindowsCB, 
					  reinterpret_cast<LPARAM>( &wmWndMap ));

    // We want more
    return TRUE;
}