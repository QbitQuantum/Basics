CronoView::CronoView()
	:
	BView("CronoView", B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE),
	fAccentsList(false)
{
    fReplicated = false;

	// Core
	fCore = new Core();

	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	rgb_color barColor = { 0, 200, 0 };
	rgb_color fillColor = { 240, 240, 240 };


	_BuildMenu();

	// Volume slider
	BBox* volBox = new BBox("volbox");
	volBox->SetLabel("Volume");

	BGroupLayout* volLayout = new BGroupLayout(B_VERTICAL);
	volLayout->SetInsets(10, volBox->TopBorderOffset() * 2 + 10, 10, 10);
	volBox->SetLayout(volLayout);
	
	fVolumeSlider = new VolumeSlider("",
		0, 1000, DEFAULT_VOLUME, new BMessage(MSG_VOLUME));

	fVolumeSlider->SetLimitLabels("Min", "Max");
	fVolumeSlider->SetHashMarks(B_HASH_MARKS_BOTTOM);
	fVolumeSlider->SetHashMarkCount(20);
	fVolumeSlider->SetValue((int32)fCore->Volume()*10);
	fVolumeSlider->UseFillColor(true, &fillColor);
	fVolumeSlider->SetPosition(gCronoSettings.CronoVolume);
	fVolumeSlider->SetLabel(BString() << gCronoSettings.CronoVolume);
	volLayout->AddView(fVolumeSlider);

	// Speed Slider & TextControl
	BBox* speedBox = new BBox("speedbox");
	speedBox->SetLabel("BPM");
	BGroupLayout* speedLayout = new BGroupLayout(B_HORIZONTAL);
	speedLayout->SetInsets(10, speedBox->TopBorderOffset() * 2 + 10, 10, 10);
	speedBox->SetLayout(speedLayout);

	fSpeedSlider = new VolumeSlider("",
		MIN_SPEED, MAX_SPEED, DEFAULT_SPEED, new BMessage(MSG_SPEED_SLIDER));

	fSpeedSlider->SetLimitLabels(BString() << MIN_SPEED,
		BString() << MAX_SPEED);

	fSpeedSlider->SetKeyIncrementValue(5);
	fSpeedSlider->SetHashMarks(B_HASH_MARKS_BOTTOM);
	fSpeedSlider->SetHashMarkCount(15);
	fSpeedSlider->SetValue(fCore->Speed());
	fSpeedSlider->UseFillColor(true, &fillColor);
	_UpdateTempoName(gCronoSettings.Speed);

	fSpeedEntry = new BTextControl("", "", BString() << gCronoSettings.Speed,
		new BMessage(MSG_SPEED_ENTRY), B_WILL_DRAW);

	fSpeedEntry->SetDivider(70);
	fSpeedEntry->SetAlignment(B_ALIGN_RIGHT, B_ALIGN_RIGHT);
	fSpeedEntry->SetExplicitSize(BSize(35, 20));

	speedLayout->AddView(fSpeedSlider);
	speedLayout->AddView(fSpeedEntry);

	// Meter buttons
	BBox* tempoBox = new BBox("tempoBox");
	tempoBox->SetLabel("Tempo");

	for(int i = 0; i < 5; i++)
		fTempoRadios[i] = new BRadioButton("", "",
			new BMessage(MSG_METER_RADIO));

	fTempoRadios[0]->SetLabel("1/4");
	fTempoRadios[1]->SetLabel("2/4");
	fTempoRadios[2]->SetLabel("3/4");
	fTempoRadios[3]->SetLabel("4/4");
	fTempoRadios[4]->SetLabel("Other");

	fTempoRadios[fCore->Meter()]->SetValue(1);

	fTempoEntry = new BTextControl("", "", "4",
		new BMessage(MSG_METER_ENTRY), B_WILL_DRAW);

	fTempoEntry->SetDivider(70);

	if (fTempoRadios[4]->Value() == 1)
		fTempoEntry->SetEnabled(true);
	else
		fTempoEntry->SetEnabled(false);		

	fAccentsView = new BGroupView(B_HORIZONTAL, 0);

	BLayoutBuilder::Group<>(tempoBox, B_VERTICAL, 0)
		.SetInsets(10, tempoBox->TopBorderOffset() * 2 + 10, 10, 10)
		.AddGroup(B_HORIZONTAL, 0)
			.Add(fTempoRadios[0])
			.Add(fTempoRadios[1])
			.Add(fTempoRadios[2])
			.Add(fTempoRadios[3])
			.Add(fTempoRadios[4])
			.Add(fTempoEntry)
			.AddGlue()
		.End()
		.Add(fAccentsView)
		.AddGlue()
	.End();

	if (gCronoSettings.AccentTable == true)
		_ShowTable(true);

	fStartButton = new BButton("Start", new BMessage(MSG_START));						
	fStartButton->MakeDefault(true);	
	fStopButton = new BButton("Stop", new BMessage(MSG_STOP));							

#ifdef CRONO_REPLICANT_ACTIVE
	// Dragger
	BRect frame(Bounds());
	frame.left = frame.right - 7;
	frame.top = frame.bottom - 7;
	BDragger *dragger = new BDragger(frame, this,
		B_FOLLOW_RIGHT | B_FOLLOW_TOP); 
#endif

	// Create view
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.Add(fMenuBar)
		.Add(volBox)
		.Add(speedBox)
		.Add(tempoBox)
		.AddGroup(B_HORIZONTAL)
			.Add(fStartButton)
			.Add(fStopButton)
		.End()
#ifdef CRONO_REPLICANT_ACTIVE
		.Add(dragger)
#endif
		.End();
}