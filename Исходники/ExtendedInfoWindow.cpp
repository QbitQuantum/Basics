ExtendedInfoWindow::ExtendedInfoWindow(PowerStatusDriverInterface* interface)
	:
	BWindow(BRect(100, 150, 500, 500), "Extended battery info", B_TITLED_WINDOW,
		B_NOT_RESIZABLE | B_NOT_ZOOMABLE | B_AVOID_FRONT |
		B_ASYNCHRONOUS_CONTROLS),
	fDriverInterface(interface),
	fSelectedView(NULL)
{
	fDriverInterface->AcquireReference();

	BView *view = new BView(Bounds(), "view", B_FOLLOW_ALL, 0);
	view->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	AddChild(view);

	BGroupLayout* mainLayout = new BGroupLayout(B_VERTICAL);
	mainLayout->SetSpacing(10);
	mainLayout->SetInsets(10, 10, 10, 10);
	view->SetLayout(mainLayout);

	BRect rect = Bounds();
	rect.InsetBy(5, 5);
	BBox *infoBox = new BBox(rect, "Power status box");
	infoBox->SetLabel("Battery info");
	BGroupLayout* infoLayout = new BGroupLayout(B_HORIZONTAL);
	infoLayout->SetInsets(10, infoBox->TopBorderOffset() * 2 + 10, 10, 10);
	infoLayout->SetSpacing(10);
	infoBox->SetLayout(infoLayout);
	mainLayout->AddView(infoBox);

	BGroupView* batteryView = new BGroupView(B_VERTICAL);
	batteryView->GroupLayout()->SetSpacing(10);
	infoLayout->AddView(batteryView);

	// create before the battery views
	fBatteryInfoView = new BatteryInfoView();

	BGroupLayout* batteryLayout = batteryView->GroupLayout();
	BRect batteryRect(0, 0, 50, 30);
	for (int i = 0; i < interface->GetBatteryCount(); i++) {
		ExtPowerStatusView* view = new ExtPowerStatusView(interface,
			batteryRect, B_FOLLOW_NONE, i, this);
		view->SetExplicitMaxSize(BSize(70, 80));
		view->SetExplicitMinSize(BSize(70, 80));

		batteryLayout->AddView(view);
		fBatteryViewList.AddItem(view);
		fDriverInterface->StartWatching(view);
		if (!view->IsCritical())
			fSelectedView = view;
	}

	batteryLayout->AddItem(BSpaceLayoutItem::CreateGlue());

	infoLayout->AddView(fBatteryInfoView);

	if (!fSelectedView && fBatteryViewList.CountItems() > 0)
		fSelectedView = fBatteryViewList.ItemAt(0);
	fSelectedView->Select();

	BSize size = mainLayout->PreferredSize();
	ResizeTo(size.width, size.height);
}