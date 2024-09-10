SettingsView::SettingsView(Core* core)
	:
	BView("SettingsView", B_WILL_DRAW, 0),
	fCore(core)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	// Engines entry
	BBox* audioBox = new BBox("audiobox");
	audioBox->SetLabel("Engines");

	BGroupLayout* audioLayout = new BGroupLayout(B_VERTICAL);
	audioLayout->SetInsets(10, audioBox->TopBorderOffset() * 2 + 10, 10, 10);
	audioBox->SetLayout(audioLayout);

	fEngines[0] = new BRadioButton("sine", "Sine",
		_ButtonMsg(CRONO_SINE_ENGINE));
	audioLayout->AddView(fEngines[0]);

	fEngines[1] = new BRadioButton("triangle", "Triangle",
		_ButtonMsg(CRONO_TRIANGLE_ENGINE));
	audioLayout->AddView(fEngines[1]);

	fEngines[2] = new BRadioButton("sawtooth", "Sawtooth",
		_ButtonMsg(CRONO_SAWTOOTH_ENGINE));
	audioLayout->AddView(fEngines[2]);

	fEngines[3] = new BRadioButton("file", "File Engine",
		_ButtonMsg(CRONO_FILE_ENGINE));
	audioLayout->AddView(fEngines[3]);

	fSoundEntry = new BTextControl("Soundfile", "Soundfile",
		gCronoSettings.SoundFileLocation, new BMessage(MSG_SET), B_WILL_DRAW);
	fSoundEntry->SetDivider(70);
	fSoundEntry->SetAlignment(B_ALIGN_CENTER, B_ALIGN_CENTER);
	audioLayout->AddView(fSoundEntry);
	fSoundEntry->SetEnabled(false);

	fDefaultsButton = new BButton("Defaults", new BMessage(MSG_DEFAULTS));

	BLayoutBuilder::Group<>(this, B_VERTICAL, 5)
		.AddGroup(B_VERTICAL)
			.Add(audioBox, 0)
		.End()
		.AddGroup(B_HORIZONTAL)
			.Add(fDefaultsButton, 0)
		.End();

	_SetEngine(fCore->Engine());
}