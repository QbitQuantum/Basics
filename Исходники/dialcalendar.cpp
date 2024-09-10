dialCalendar::dialCalendar(const char *inidate, BTextControl *ptr, int32 msg, BHandler *hr) : BWindow(
	BRect(100+20, 100+20, 295+20, 320+20+25),
	NULL,
	B_TITLED_WINDOW,
	B_NOT_RESIZABLE ) {

	msgdc = msg;
	dateField = ptr;
	handler = hr;

	// split inidate into y/m/d
	BString tmp;
	tmp = inidate;
	tmp.Remove(4,tmp.Length()-4);
	year = toint(tmp.String());
	tmp = inidate;
	tmp.Remove(0,5);
	tmp.Remove(2,tmp.Length()-2);
	month = toint(tmp.String());
	tmp = inidate;
	tmp.Remove(0,8);
	day = toint(tmp.String());

	this->SetTitle("Wybierz datę");
	this->SetFeel(B_FLOATING_APP_WINDOW_FEEL);
	view = new BView(this->Bounds(), "calendarView", B_FOLLOW_ALL_SIDES, 0);
	view->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	this->AddChild(view);
	view->AddChild(monthyear = new BStringView(BRect(60,5,135,25), "calendarMonthYear", NULL));
	monthyear->SetAlignment(B_ALIGN_CENTER);
	view->AddChild(but_prevy = new BButton(BRect(10,5,30,25), "calendarButPrevy", "<<", new BMessage(BUT_PREVY)));
	view->AddChild(but_prevm = new BButton(BRect(35,5,55,25), "calendarButPrevm", "<", new BMessage(BUT_PREVM)));
	view->AddChild(but_nextm = new BButton(BRect(140,5,160,25), "calendarButNextm", ">", new BMessage(BUT_NEXTM)));
	view->AddChild(but_nexty = new BButton(BRect(165,5,185,25), "calendarButNexty", ">>", new BMessage(BUT_NEXTY)));

	int i,j;
	for (i=0;i<=6;i++) {
		view->AddChild(new BStringView(BRect(10+i*25,30,30+i*25,50), NULL, shortweekdays[i]));
	}
	BMessage *msg;
	for (j=0;j<=5;j++) {
		for (i=0;i<=6;i++) {
			msg = new BMessage(BUT_CAL);
			msg->AddInt32("_x", i);
			msg->AddInt32("_y", j);
			view->AddChild(caltab[i][j] = new BButton(BRect(10+i*25,55+j*25,30+i*25,75+j*25), NULL, "33", msg));
		}
	}
	view->AddChild(but_ok = new BButton(BRect(120,210,165,230), "calendarButOk", "OK", new BMessage(BUT_OK)));
	but_ok->MakeDefault(true);
	but_ok->ResizeToPreferred();
	RefreshCalendar();
}