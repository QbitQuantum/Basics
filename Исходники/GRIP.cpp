/**
 * @function OnInit
 * @brief Initialize GRIP window
 * @date 2011-10-13
 */
bool GRIPApp::OnInit()
{
#ifdef WIN32
	// --- Console ---
	FILE* pFile;
    AllocConsole();
    SetConsoleTitle(L"GRIP Console");
    freopen_s( &pFile, "conin$", "r", stdin );
    freopen_s( &pFile, "conout$", "w", stdout );
    freopen_s( &pFile, "conout$", "w", stderr );
#endif
	// --- Console ---

    if ( !wxApp::OnInit() )
        return false;
    frame = new GRIPFrame(wxT("GRIP"));
	frame->SetFocus();

	AddTabs();

	wxInitAllImageHandlers();
	wxImage gripimg = wxImage(robot_xpm);
	char r,g,b;
	gripimg.InitAlpha();
	for(int i=0; i<16; i++)for(int j=0; j<16; j++){
			r=gripimg.GetRed(i,j);g=gripimg.GetBlue(i,j);b=gripimg.GetGreen(i,j);
			if(r == g && g == b) gripimg.SetAlpha(i,j,255-r);
	}
	wxIcon ico;
	ico.CopyFromBitmap(wxBitmap(gripimg));
	frame->SetIcon(ico);
    frame->Show(true);

    return true;
}