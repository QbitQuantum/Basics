/*
============================================================================
Class constructor
============================================================================
*/
VTTpddServerLog::VTTpddServerLog(int w, int h, const char* title) :
	Fl_Double_Window(w, h, title)
{
	Fl_Box*				o;
	Fl_Button*			b;
	Fl_Group*			g;

	// Initialize everything
	m_pServer = NULL;
	m_enabled = TRUE;
	m_lastWasRx = FALSE;
	m_rxCount = m_txCount = 0;
	m_maxLogEntries = 8192;
	m_nextRef = 1;
	m_callbackActive = FALSE;
	m_autoScroll = TRUE;

	// Define our default colors
	m_colors.background = FL_BLACK;
	m_colors.ref = FL_WHITE;
	m_colors.rxLabel = FL_YELLOW;
	m_colors.txLabel = (Fl_Color) 221;
	m_colors.rxHex = fl_color_average(FL_DARK_GREEN, FL_WHITE, (float) 0.8);
	m_colors.txHex = fl_color_average((Fl_Color) 221, FL_WHITE, (float) 0.5);
	m_colors.rxAscii = FL_GREEN;
	m_colors.txAscii = (Fl_Color) 221;
	m_fontSize = 14;

	fl_font(FL_COURIER, m_fontSize);
	m_height = fl_height();
	m_width = (int) fl_width("W");

	// ===============================
	// Now create the controls we need
	// ===============================

	// Create a menu
	m_pMenu = new Fl_Menu_Bar(0, 0, w, MENU_HEIGHT-2);
	m_pMenu->menu(gServerLog_menuitems);

	// Create a window for the log
	m_pLog = new Fl_Double_Window(10, MENU_HEIGHT+10, w-20-15, h-MENU_HEIGHT-50, "");
	//m_pLog->color(FL_BLACK);
	m_pLog->end();
	m_pLog->hide();

	// Create a scrollbar
	m_pScroll = new Fl_Scrollbar(w-10-15, MENU_HEIGHT+10, 15, h-MENU_HEIGHT-50, "");
	m_pScroll->callback(cb_scroll_log, this);

	// Create a resizing group
	g = new Fl_Group(0, h-35, w, 35, "");

	// Create an auto scroll checkbox
	m_pAutoScroll = new Fl_Check_Button(20, h-37, 110, 20, "Auto scroll");
	m_pAutoScroll->callback(cb_autoscroll, this);

	// Create a disable log checkbox
	m_pDisable = new Fl_Check_Button(20, h-21, 110, 20, "Disable log");
	m_pDisable->callback(cb_disable_log, this);

	// Create a Save button
	b = new Fl_Button(150, h-30, 80, 20, "Save");
	b->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
	b->callback(cb_save_log, this);

	// Create a Load button
	b = new Fl_Button(250, h-30, 80, 20, "Load");
	b->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
	b->callback(cb_load_log, this);

	// Create a clear button
	b = new Fl_Button(350, h-30, 80, 20, "Clear");
	b->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
	b->callback(cb_clear_log, this);
	
	// Make the group resizable
	o = new Fl_Box(440, 350, 5, 5, "");
	g->resizable(o);
	g->end();

	// Make the window resizable
	o = new Fl_Box(20, MENU_HEIGHT + 30, 5, 5, "");
	resizable(o);

	// Set the scrollbar size
	SetScrollSizes();
}