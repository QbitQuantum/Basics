void MyFrame::OnNewWindow(wxCommandEvent& WXUNUSED(event))
{
      // Make another frame, containing a canvas
      MyChild *subframe = new MyChild(frame, wxT("Canvas Frame"),
                                      wxPoint(10, 10), wxSize(300, 300),
                                      wxDEFAULT_FRAME_STYLE |
                                      wxNO_FULL_REPAINT_ON_RESIZE);

      subframe->SetTitle(wxString::Format(wxT("Canvas Frame %d"), winNumber));
      winNumber ++;

      // Give it an icon (this is ignored in MDI mode: uses resources)
#ifdef __WXMSW__
      subframe->SetIcon(wxIcon(wxT("sashtest_icn")));
#endif

#if wxUSE_STATUSBAR
      // Give it a status line
      subframe->CreateStatusBar();
#endif // wxUSE_STATUSBAR

      // Make a menubar
      wxMenu *file_menu = new wxMenu;

      file_menu->Append(SASHTEST_NEW_WINDOW, wxT("&New window"));
      file_menu->Append(SASHTEST_CHILD_QUIT, wxT("&Close child"));
      file_menu->Append(SASHTEST_QUIT, wxT("&Exit"));

      wxMenu *option_menu = new wxMenu;

      // Dummy option
      option_menu->Append(SASHTEST_REFRESH, wxT("&Refresh picture"));

      wxMenu *help_menu = new wxMenu;
      help_menu->Append(SASHTEST_ABOUT, wxT("&About"));

      wxMenuBar *menu_bar = new wxMenuBar;

      menu_bar->Append(file_menu, wxT("&File"));
      menu_bar->Append(option_menu, wxT("&Options"));
      menu_bar->Append(help_menu, wxT("&Help"));

      // Associate the menu bar with the frame
      subframe->SetMenuBar(menu_bar);

      int width, height;
      subframe->GetClientSize(&width, &height);
      MyCanvas *canvas = new MyCanvas(subframe, wxPoint(0, 0), wxSize(width, height));
      canvas->SetCursor(wxCursor(wxCURSOR_PENCIL));
      subframe->canvas = canvas;

      // Give it scrollbars
      canvas->SetScrollbars(20, 20, 50, 50);

      subframe->Show(true);
}