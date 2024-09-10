int main(int argc, char* argv[]){
	Fl_Window *mainw = new Fl_Window(400, 380, "DoConfigure - Doukutsu Monotagari Settings");
	
	Fl_Group *movegroup = new Fl_Group(10, 10, 185, 50);
		movegroup->box(FL_THIN_DOWN_BOX);
		movear = new Fl_Radio_Round_Button(10, 10, 185, 20, "Arrows for Movement");
		movear->setonly();
		movegt = new Fl_Radio_Round_Button(10, 40, 185, 20, "<>? for Movement");
	movegroup->end();
	
	Fl_Group *buttongroup = new Fl_Group(10, 70, 185, 50);
		buttongroup->box(FL_THIN_DOWN_BOX);
		buttonxz = new Fl_Radio_Round_Button(10, 70, 185, 20, "Z=Jump; X=Attack");
		buttonxz->setonly();
		buttonzx = new Fl_Radio_Round_Button(10, 100, 185, 20, "X=Jump; Z=Attack");
	buttongroup->end();
	
	Fl_Group *okaygroup = new Fl_Group(205, 10, 185, 50);
		okaygroup->box(FL_THIN_DOWN_BOX);
		okayjump = new Fl_Radio_Round_Button(205, 10, 185, 20, "Jump=Okay");
		okayjump->setonly();
		okayattack = new Fl_Radio_Round_Button(205, 40, 185, 20, "Attack=Okay");
	okaygroup->end();
	
	displaychoice = new Fl_Choice(205, 70, 185, 20);
	Fl_Menu_Item screens[] = {
		{"Fullscreen 16-bit"},
		{"Windowed 320x240"},
 		{"Windowed 640x480"},
		{"Fullscreen 24-bit"},
		{"Fullscreen 32-bit"},
		{0}};
	displaychoice->menu(screens);
	joychoice = new Fl_Check_Button(205, 100, 185, 20, "Use Joypad");
	joychoice->callback(&activatejoy);
		
	joystuffcontainer = new Fl_Group(10, 130, 380, 200);
		joystuffcontainer->box(FL_THIN_DOWN_BOX);
		for(char i=0;i<8;i++){
			joyRows[i] = new RadioRow(i);
		}
		//There's no Label class alright? I'll switch it as soon as one is introduced.
		for (char i=0;i<6;i++) {
			Fl_Group *labeljump = new Fl_Group(10, 150+i*30, 10, 20);
			char* label=new char[strlen(ActionName(i+1))+2];
			sprintf(label, "%s:", ActionName(i+1));
			labeljump->label(label);
			labeljump->align(FL_ALIGN_RIGHT);
			labeljump->end();
		}
		
#ifdef HAVE_SDL
		if (JoystickSingleton::Instance().NumJoysticks() > 0){
			for (char i=0;i<6;i++){
				Fl_Button* btn = new Fl_Button(345, 150+30*i, 35, 20, "pick");
				btn->callback(&pickJsButton, (void*)(long)(i+1));
			}
		}
#endif

	joystuffcontainer->end();
	
	Fl_Button *okaybutton = new Fl_Button(10, 340, 185, 30, "Okay");
	okaybutton->callback(&write_Config);
	Fl_Button *cancelbutton = new Fl_Button(205, 340, 185, 30, "Cancel");
	cancelbutton->callback(&quit);
	
	mainw->end();
	mainw->show(argc, argv);
	
#ifdef HAVE_SDL
	char joystickLabel[100];
	sprintf(joystickLabel, "%s (%d found)", joychoice->label(), JoystickSingleton::Instance().NumJoysticks());
	joychoice->label(joystickLabel);
#endif

	read_Config();
	Fl::option(Fl::OPTION_VISIBLE_FOCUS, false);
	return Fl::run();
}