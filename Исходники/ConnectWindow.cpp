				void Init() {

					cWindow = new Fl_Window(400, 420, 300, 70, "Connect to Host");
					bInput = new Fl_Input(50, 0, 150, 30, "Host: ");
					checkbx = new Fl_Check_Button(50, 40, 100, 14, " Scaling");
					checkbx->align(FL_ALIGN_LEFT);
					checkbx->callback(setscale, this);
					connectbtn = new Fl_Button(200, 0, 80, 30, "Connect");
					connectbtn->callback(try_connect_frm, this);
					cWindow->end();
					cWindow->show();

				}