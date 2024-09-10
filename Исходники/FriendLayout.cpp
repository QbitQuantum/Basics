	void MessageReceived(BMessage* message)
	{
		switch (message->what) {
			case 'BOOM':
				if (!fBoom) {
					fBoom = _MakeButton("BOOM");
					fLayout2->AddView(fBoom, fLeft, fTop,
						fRight, fBottom);
				} else {
					if (fBoom->IsHidden(fBoom))
						fBoom->Show();
					else
						fBoom->Hide();
				}
				break;
			case 'arcv': {
				BView* view = GetLayout()->View();
				BMessage archive;
				status_t err = view->Archive(&archive, true);
				BWindow* window = new BWindow(BRect(30, 30, 400, 400),
					"ALM Friend Test Clone", B_TITLED_WINDOW,
					B_QUIT_ON_WINDOW_CLOSE | B_AUTO_UPDATE_SIZE_LIMITS);
				window->SetLayout(new BGroupLayout(B_VERTICAL));
				BView* clone;
				if (err == B_OK)
					err = BUnarchiver::InstantiateObject(&archive, clone);
				if (err != B_OK)
					window->AddChild(new BStringView("", "An error occurred!"));
				else {
					window->AddChild(clone);
				}
				window->Show();

				break;
			}
			default:
				BWindow::MessageReceived(message);
		}
	}