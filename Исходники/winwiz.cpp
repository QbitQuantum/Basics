//***********************************************************************
static void do_init_dialog(HWND hwnd)
{
   char msgstr[81] ;
   // hwndTopLevel = hwnd ;   //  do I need this?
   wsprintfA(msgstr, "%s", Version) ;
   SetWindowTextA(hwnd, msgstr) ;

   SetClassLongA(hwnd, GCL_HICON,   (LONG) LoadIcon(g_hinst, (LPCTSTR)WINWIZICO));
   SetClassLongA(hwnd, GCL_HICONSM, (LONG) LoadIcon(g_hinst, (LPCTSTR)WINWIZICO));

   hwndMain = hwnd ;

   set_up_working_spaces(hwnd) ; //  do this *before* tooltips !!
   //***************************************************************************
   //  add tooltips and bitmaps
   //***************************************************************************
   hToolTip = create_tooltips(hwnd, 150, 100, 10000) ;
   add_main_tooltips(hwnd, hToolTip) ;

   // RECT rWindow;
   // unsigned stTop ;
   RECT myRect ;
   // GetWindowRect(hwnd, &myRect) ;
   GetClientRect(hwnd, &myRect) ;
   cxClient = (myRect.right - myRect.left) ;
   cyClient = (myRect.bottom - myRect.top) ;

   center_window() ;
   //****************************************************************
   //  create/configure status bar
   //****************************************************************
   MainStatusBar = new CStatusBar(hwnd) ;
   MainStatusBar->MoveToBottom(cxClient, cyClient) ;
   //  re-position status-bar parts
   {
   int sbparts[3];
   sbparts[0] = (int) (6 * cxClient / 10) ;
   sbparts[1] = (int) (8 * cxClient / 10) ;
   sbparts[2] = -1;
   MainStatusBar->SetParts(3, &sbparts[0]);
   }
   
   //****************************************************************
   //  create/configure terminal
   //****************************************************************
   uint ctrl_bottom = get_bottom_line(hwnd, IDC_MAP_AREA) ;
   uint lvdy = cyClient - ctrl_bottom - MainStatusBar->height() ;

   myTerminal = new CTerminal(hwnd, IDC_TERMINAL, g_hinst, 
      0, ctrl_bottom, cxClient-1, lvdy,
      LVL_STY_VIRTUAL | LVL_STY_NO_HEADER | LVL_STY_PAGE_TO_END ) ;
   myTerminal->set_terminal_font("Courier New", 100, EZ_ATTR_BOLD) ;
   myTerminal->lview_assign_column_headers() ;

   set_local_terminal_colors() ; //  should this be wrapped in the terminal module?

   // Subclass the terminal ListView
   // wpOrigTermProc = (WNDPROC) SetWindowLongPtr(term->hwndSelf, GWL_WNDPROC, (LONG) TermSubclassProc); 
   wpOrigTermProc = (WNDPROC) myTerminal->terminal_lview_subclass((LONG) TermSubclassProc); 
      
   // SetClassLong(this_port->cpterm->hwndSelf, GCL_HCURSOR,(long) 0);  //  disable class cursor
   // termout("terminal size: columns=%u, screen rows=%u", term->cols, term->rows) ;
   termout("terminal size: columns=%u, screen rows=%u",
      myTerminal->get_term_columns(), myTerminal->get_term_rows()) ;

   //****************************************************************
   main_timer_id = SetTimer(hwnd, IDT_TIMER_MAIN, 100, (TIMERPROC) NULL) ;
}