/*
================
rvGEApp::HandleCommand

Handles the WM_COMMAND message
================
*/
int rvGEApp::HandleCommand ( WPARAM wParam, LPARAM lParam )
{
    HWND		   active;
    rvGEWorkspace* workspace = GetActiveWorkspace ( &active );

    // The recent file list needs to be handled specially
    if ( LOWORD(wParam) >= ID_GUIED_FILE_MRU1 && LOWORD(wParam) < ID_GUIED_FILE_MRU1 + rvGEOptions::MAX_MRU_SIZE )
    {
        OpenFile ( mOptions.GetRecentFile ( mOptions.GetRecentFileCount() - (LOWORD(wParam)-ID_GUIED_FILE_MRU1) - 1 ) );
        return 0;
    }

    switch ( LOWORD ( wParam ) )
    {
    case ID_GUIED_SOURCECONTROL_CHECKIN:
        assert ( workspace );
        HandleCommandSave ( workspace, workspace->GetFilename ( ) );
        workspace->CheckIn ( );
        break;

    case ID_GUIED_SOURCECONTROL_CHECKOUT:
        assert ( workspace );
        workspace->CheckOut ( );
        break;

    case ID_GUIED_SOURCECONTROL_UNDOCHECKOUT:
        assert ( workspace );
        if ( IDYES == MessageBox ( va("Are you sure you want to undo the checkout of the file '%s'?",workspace->GetFilename()), MB_YESNO|MB_ICONQUESTION) )
        {
            workspace->UndoCheckout ( );
        }
        break;

    case ID_GUIED_TOOLS_RELOADMATERIALS:
        SetCursor ( LoadCursor ( NULL, MAKEINTRESOURCE(IDC_WAIT) ) );
        cmdSystem->BufferCommandText( CMD_EXEC_NOW, "reloadImages\n" );
        cmdSystem->BufferCommandText( CMD_EXEC_NOW, "reloadMaterials\n" );
        SetCursor ( LoadCursor ( NULL, MAKEINTRESOURCE(IDC_ARROW) ) );
        break;

    case ID_GUIED_EDIT_COPY:
        assert ( workspace );
        workspace->Copy  ( );
        break;

    case ID_GUIED_EDIT_PASTE:
        assert ( workspace );
        workspace->Paste  ( );
        break;

    case ID_GUIED_HELP_ABOUT:
        DialogBox ( GetInstance(), MAKEINTRESOURCE(IDD_GUIED_ABOUT), mMDIFrame, AboutDlg_WndProc );
        break;

    case ID_GUIED_TOOLS_VIEWER:
    {
        if ( mViewer )
        {
            break;
        }

        mViewer = new rvGEViewer;
        if ( !mViewer->Create ( mMDIFrame ) )
        {
            delete mViewer;
            mViewer = NULL;
        }

        if ( workspace )
        {
            if ( !workspace->IsModified () || HandleCommand ( MAKELONG(ID_GUIED_FILE_SAVE,0), 0 ) )
            {
                mViewer->OpenFile ( workspace->GetFilename ( ) );
            }
        }

        SetActiveWindow ( mViewer->GetWindow ( ) );
        break;
    }

    case ID_GUIED_ITEM_MAKESAMESIZEWIDTH:
        assert ( workspace );
        workspace->MakeSelectedSameSize ( true, false );
        break;

    case ID_GUIED_ITEM_MAKESAMESIZEBOTH:
        assert ( workspace );
        workspace->MakeSelectedSameSize ( true, true );
        break;

    case ID_GUIED_ITEM_MAKESAMESIZEHEIGHT:
        assert ( workspace );
        workspace->MakeSelectedSameSize ( false, true );
        break;

    case ID_GUIED_ITEM_ALIGNLEFTS:
        assert ( workspace );
        workspace->AlignSelected ( rvGEWorkspace::ALIGN_LEFTS );
        break;

    case ID_GUIED_ITEM_ALIGNCENTERS:
        assert ( workspace );
        workspace->AlignSelected ( rvGEWorkspace::ALIGN_CENTERS );
        break;

    case ID_GUIED_ITEM_ALIGNRIGHTS:
        assert ( workspace );
        workspace->AlignSelected ( rvGEWorkspace::ALIGN_RIGHTS );
        break;

    case ID_GUIED_ITEM_ALIGNTOPS:
        assert ( workspace );
        workspace->AlignSelected ( rvGEWorkspace::ALIGN_TOPS );
        break;

    case ID_GUIED_ITEM_ALIGNMIDDLES:
        assert ( workspace );
        workspace->AlignSelected ( rvGEWorkspace::ALIGN_MIDDLES );
        break;

    case ID_GUIED_ITEM_ALIGNBOTTOMS:
        assert ( workspace );
        workspace->AlignSelected ( rvGEWorkspace::ALIGN_BOTTOMS );
        break;

    case ID_GUIED_ITEM_ARRANGESENDBACKWARD:
        assert ( workspace );
        workspace->SendSelectedBackward ( );
        break;

    case ID_GUIED_ITEM_ARRANGESENDTOBACK:
        assert ( workspace );
        workspace->SendSelectedToBack( );
        break;

    case ID_GUIED_ITEM_ARRANGEBRINGFORWARD:
        assert ( workspace );
        workspace->BringSelectedForward ( );
        break;

    case ID_GUIED_ITEM_ARRANGEBRINGTOFRONT:
        assert ( workspace );
        workspace->BringSelectedToFront ( );
        break;

    case ID_GUIED_ITEM_ARRANGEMAKECHILD:
        assert ( workspace );
        workspace->MakeSelectedAChild ( );
        break;

    case ID_GUIED_ITEM_PROPERTIES:
        assert ( workspace );
        workspace->EditSelectedProperties ( );
        break;

    case ID_GUIED_ITEM_SCRIPTS:
        assert ( workspace );
        workspace->EditSelectedScripts ( );
        break;

    case ID_GUIED_ITEM_NEWWINDOWDEF:
        assert ( workspace );
        workspace->AddWindow ( rvGEWindowWrapper::WT_NORMAL );
        break;

    case ID_GUIED_ITEM_NEWEDITDEF:
        assert ( workspace );
        workspace->AddWindow ( rvGEWindowWrapper::WT_EDIT );
        break;

    case ID_GUIED_ITEM_NEWHTMLDEF:
        assert ( workspace );
        workspace->AddWindow ( rvGEWindowWrapper::WT_HTML );
        break;

    case ID_GUIED_ITEM_NEWCHOICEDEF:
        assert ( workspace );
        workspace->AddWindow ( rvGEWindowWrapper::WT_CHOICE );
        break;

    case ID_GUIED_ITEM_NEWSLIDERDEF:
        assert ( workspace );
        workspace->AddWindow ( rvGEWindowWrapper::WT_SLIDER );
        break;

    case ID_GUIED_ITEM_NEWLISTDEF:
        assert ( workspace );
        workspace->AddWindow ( rvGEWindowWrapper::WT_LIST );
        break;

    case ID_GUIED_ITEM_NEWBINDDEF:
        assert ( workspace );
        workspace->AddWindow ( rvGEWindowWrapper::WT_BIND );
        break;

    case ID_GUIED_ITEM_NEWRENDERDEF:
        assert ( workspace );
        workspace->AddWindow ( rvGEWindowWrapper::WT_RENDER );
        break;

    case ID_GUIED_WINDOW_TILE:
        SendMessage ( mMDIClient, WM_MDITILE, 0, 0 );
        break;

    case ID_GUIED_WINDOW_CASCADE:
        SendMessage ( mMDIClient, WM_MDICASCADE, 0, 0 );
        break;

    case ID_GUIED_VIEW_STATUSBAR:
    {
        RECT rWindow;

        mStatusBar.Show ( mOptions.GetStatusBarVisible()?false:true );

        GetWindowRect ( mMDIFrame, &rWindow );
        SendMessage ( mMDIFrame, WM_SIZE, 0, MAKELONG ( rWindow.right-rWindow.left, rWindow.bottom-rWindow.top ) );
        break;
    }

    case ID_GUIED_WINDOW_SHOWNAVIGATOR:
        mNavigator.Show ( mOptions.GetNavigatorVisible()?false:true );
        break;

    case ID_GUIED_WINDOW_SHOWPROPERTIES:
        mProperties.Show ( mOptions.GetPropertiesVisible()?false:true );
        break;

    case ID_GUIED_WINDOW_SHOWTRANSFORMER:
        mTransformer.Show ( mOptions.GetTransformerVisible()?false:true  );
        break;

    case ID_GUIED_EDIT_DELETE:
        assert ( workspace );
        workspace->DeleteSelected ( );
        break;

    case ID_GUIED_VIEW_HIDESELECTED:
        assert ( workspace );
        workspace->HideSelected ( );
        break;

    case ID_GUIED_VIEW_UNHIDESELECTED:
        assert ( workspace );
        workspace->UnhideSelected ( );
        break;

    case ID_GUIED_VIEW_SHOWHIDDEN:
        assert ( workspace );
        workspace->ShowHidden ( );
        break;

    case ID_GUIED_EDIT_UNDO:
        assert ( workspace );
        workspace->GetModifierStack().Undo ( );
        mNavigator.Update ( );
        mTransformer.Update ( );
        break;

    case ID_GUIED_EDIT_REDO:
        assert ( workspace );
        workspace->GetModifierStack().Redo ( );
        mNavigator.Update ( );
        mTransformer.Update ( );
        break;

    case ID_GUIED_VIEW_OPTIONS:
        GEOptionsDlg_DoModal ( mMDIFrame );
        break;

    case ID_GUIED_VIEW_SHOWGRID:
        mOptions.SetGridVisible ( mOptions.GetGridVisible()?false:true );
        break;

    case ID_GUIED_VIEW_SNAPTOGRID:
        mOptions.SetGridSnap ( mOptions.GetGridSnap ()?false:true );
        break;

    case ID_GUIED_VIEW_ZOOMIN:
        assert ( workspace );
        workspace->ZoomIn ( );
        break;

    case ID_GUIED_VIEW_ZOOMOUT:
        assert ( workspace );
        workspace->ZoomOut ( );
        break;

    case ID_GUIED_FILE_EXIT:
        DestroyWindow ( mMDIFrame );
        break;

    case ID_GUIED_FILE_CLOSE:
        if ( active )
        {
            assert ( workspace );
            SendMessage ( active, WM_CLOSE, 0, 0 );
        }
        break;

    case ID_GUIED_FILE_NEW:
        NewFile ( );
        break;

    case ID_GUIED_FILE_SAVE:
        assert ( workspace );
        HandleCommandSave ( workspace, workspace->GetFilename ( ) );
        break;

    case ID_GUIED_FILE_SAVEAS:
        assert ( workspace );
        HandleCommandSave ( workspace, NULL );
        break;

    case ID_GUIED_FILE_OPEN:
    {
        OPENFILENAME ofn;
        char		 szFile[MAX_PATH] = "";

        // Initialize OPENFILENAME
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = mMDIFrame;
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = "GUI Files\0*.GUI\0All Files\0*.*\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        // Display the Open dialog box.
        if (GetOpenFileName(&ofn)==TRUE)
        {
            OpenFile ( ofn.lpstrFile );
        }
        break;
    }
    }

    return -1;
}