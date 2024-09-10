	StatusWindow(const char* text)
		:
		BWindow(BRect(0, 0, 10, 10), B_TRANSLATE("status"), B_MODAL_WINDOW_LOOK,
			B_MODAL_APP_WINDOW_FEEL, B_NO_WORKSPACE_ACTIVATION | B_NOT_ZOOMABLE
				| B_AVOID_FRONT | B_NOT_RESIZABLE)
	{
		BView* rootView = new BView(Bounds(), "root", B_FOLLOW_ALL,
			B_WILL_DRAW);
		AddChild(rootView);
		rootView->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
		float spacing = be_control_look->DefaultItemSpacing();
		BALMLayout* layout = new BALMLayout(spacing);
		rootView->SetLayout(layout);
		layout->SetInset(spacing);

		BStringView* string = new BStringView("text", text);
		layout->AddView(string, layout->Left(), layout->Top(), layout->Right(),
			layout->Bottom());
		BSize min = layout->MinSize();
		ResizeTo(min.Width(), min.Height());
		CenterOnScreen();
	}