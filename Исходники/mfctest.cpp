wxFrame *MyApp::CreateFrame()
{
    MyChild *subframe = new MyChild(NULL, _T("Canvas Frame"), wxPoint(10, 10), wxSize(300, 300),
        wxDEFAULT_FRAME_STYLE);

    subframe->SetTitle(_T("wxWidgets canvas frame"));

    // Give it a status line
    subframe->CreateStatusBar();

    // Make a menubar
    wxMenu *file_menu = new wxMenu;

    file_menu->Append(HELLO_NEW, _T("&New MFC Window"));
    file_menu->Append(HELLO_QUIT, _T("&Close"));

    wxMenuBar *menu_bar = new wxMenuBar;

    menu_bar->Append(file_menu, _T("&File"));

    // Associate the menu bar with the frame
    subframe->SetMenuBar(menu_bar);

    int width, height;
    subframe->GetClientSize(&width, &height);

    MyCanvas *canvas = new MyCanvas(subframe, wxPoint(0, 0), wxSize(width, height));
    canvas->SetCursor(wxCursor(wxCURSOR_PENCIL));
    subframe->canvas = canvas;
    subframe->Show(true);

    // Return the main frame window
    return subframe;
}