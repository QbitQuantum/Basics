void MyFrame::OnNewWindow(wxCommandEvent& WXUNUSED(event) )
{
    // Make another frame, containing a canvas
    MyChild *subframe = new MyChild(frame, _T("Canvas Frame"));

    wxString title;
    title.Printf(_T("Canvas Frame %d"), ++gs_nFrames);

    subframe->SetTitle(title);

    // Give it an icon
#ifdef __WXMSW__
    subframe->SetIcon(wxIcon(_T("chrt_icn")));
#else
    subframe->SetIcon(wxIcon( mondrian_xpm ));
#endif

    // Make a menubar
    wxMenu *file_menu = new wxMenu;

    file_menu->Append(MDI_NEW_WINDOW, _T("&New window"));
    file_menu->Append(MDI_CHILD_QUIT, _T("&Close child"), _T("Close this window"));
    file_menu->Append(MDI_QUIT, _T("&Exit"));

    wxMenu *option_menu = new wxMenu;

    option_menu->Append(MDI_REFRESH, _T("&Refresh picture"));
    option_menu->Append(MDI_CHANGE_TITLE, _T("Change &title...\tCtrl-T"));
    option_menu->AppendSeparator();
    option_menu->Append(MDI_CHANGE_POSITION, _T("Move frame\tCtrl-M"));
    option_menu->Append(MDI_CHANGE_SIZE, _T("Resize frame\tCtrl-S"));

    wxMenu *help_menu = new wxMenu;
    help_menu->Append(MDI_ABOUT, _T("&About"));

    wxMenuBar *menu_bar = new wxMenuBar;

    menu_bar->Append(file_menu, _T("&File"));
    menu_bar->Append(option_menu, _T("&Child"));
    menu_bar->Append(help_menu, _T("&Help"));

    // Associate the menu bar with the frame
    subframe->SetMenuBar(menu_bar);

#if wxUSE_STATUSBAR
    subframe->CreateStatusBar();
    subframe->SetStatusText(title);
#endif // wxUSE_STATUSBAR

    int width, height;
    subframe->GetClientSize(&width, &height);
    MyCanvas *canvas = new MyCanvas(subframe, wxPoint(0, 0), wxSize(width, height));
    canvas->SetCursor(wxCursor(wxCURSOR_PENCIL));
    subframe->canvas = canvas;

    // Give it scrollbars
    canvas->SetScrollbars(20, 20, 50, 50);

    subframe->Show(true);
}