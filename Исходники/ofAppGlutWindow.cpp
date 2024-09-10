void HandleFiles(WPARAM wParam)
{
    // DragQueryFile() takes a LPWSTR for the name so we need a TCHAR string
    TCHAR szName[MAX_PATH];

    // Here we cast the wParam as a HDROP handle to pass into the next functions
    HDROP hDrop = (HDROP)wParam;

	POINT pt;
	DragQueryPoint(hDrop, &pt);
	//printf("%i %i \n", pt.x, pt.y);
	
	ofDragInfo info;
	info.position.x = pt.x;
	info.position.y = pt.y;


    // This functions has a couple functionalities.  If you pass in 0xFFFFFFFF in
    // the second parameter then it returns the count of how many filers were drag
    // and dropped.  Otherwise, the function fills in the szName string array with
    // the current file being queried.
    int count = DragQueryFile(hDrop, 0xFFFFFFFF, szName, MAX_PATH);

	
    // Here we go through all the files that were drag and dropped then display them
    for(int i = 0; i < count; i++)
    {
        // Grab the name of the file associated with index "i" in the list of files dropped.
        // Be sure you know that the name is attached to the FULL path of the file.
        DragQueryFile(hDrop, i, szName, MAX_PATH);
		
		wchar_t * s = szName;
		char dfault = '?';
        const std::locale& loc = std::locale();
		std::ostringstream stm;
		while( *s != L'\0' ) {
			stm << std::use_facet< std::ctype<wchar_t> >( loc ).narrow( *s++, dfault );
		}
		info.files.push_back(string(stm.str()));
		
			//toUTF8(udispName, dispName);

        // Bring up a message box that displays the current file being processed
        //MessageBox(GetForegroundWindow(), szName, L"Current file received", MB_OK);
    }

    // Finally, we destroy the HDROP handle so the extra memory
    // allocated by the application is released.
    DragFinish(hDrop);

	ofAppPtr->dragEvent(info);

}