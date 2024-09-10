void BuildTree::CreateTreeView(HWND hwndParent,HINSTANCE hInst,LPSTR lpszFileName) 
{ 
	RECT rcClient;
    
    InitCommonControls(); 
    GetClientRect(hwndParent, &rcClient); 
    s_hWndTV = CreateWindowEx(0,
                            WC_TREEVIEW,
                            "Tree View",
							WS_VISIBLE | WS_CHILD | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS, 
                            0, 
                            0, 
                            rcClient.right, 
                            rcClient.bottom,
                            hwndParent, 
                            (HMENU)0, 
                            hInst, 
                            NULL); 

	::ShowWindow(s_hWndTV,SW_SHOW);

	HIMAGELIST himl;  // handle to image list 
    HBITMAP hbmp;     // handle to bitmap 

    // Create the image list. 
	himl = ImageList_Create(16,16,ILC_COLOR32,2, 0);
    

    // Add the open file, closed file, and document bitmaps. 
    hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_BUILD)); 
    ImageList_Add(himl, hbmp, (HBITMAP)NULL); 
    DeleteObject(hbmp); 

    hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_FOLDER)); 
    ImageList_Add(himl, hbmp, (HBITMAP)NULL); 
    DeleteObject(hbmp); 

	int ic = ImageList_GetImageCount(himl);

    // Associate the image list with the tree-view control. 
    TreeView_SetImageList(s_hWndTV, himl, TVSIL_NORMAL); 

} 