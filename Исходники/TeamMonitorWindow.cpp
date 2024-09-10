TeamDescriptionView::TeamDescriptionView()
	:
	BView("description view", B_WILL_DRAW),
	fItem(NULL),
	fSeconds(4),
	fRebootRunner(NULL)
{
	fInfoString = B_TRANSLATE(
		"Select an application from the list above and click one of "
		"the buttons 'Kill application' and 'Quit application' "
		"in order to close it.\n\n"
		"Hold CONTROL+ALT+DELETE for %ld seconds to reboot.");

	fTeamName = new BStringView("team name", "team name");
	fSysComponent = new BStringView("system component", B_TRANSLATE(
		"(This team is a system component)"));
	fQuitOverdue = new BStringView("quit overdue", B_TRANSLATE(
		"If the application will not quit you may have to kill it."));
	fQuitOverdue->SetFont(be_bold_font);

	fInfoTextView = new AllShowingTextView("info text");
	BGroupView* group = new BGroupView(B_VERTICAL);
	BGroupLayoutBuilder(group)
		.Add(fInfoTextView)
		.AddGlue();

	fIconView = new IconView();
	fIconView->SetExplicitAlignment(
		BAlignment(B_ALIGN_HORIZONTAL_UNSET, B_ALIGN_VERTICAL_CENTER));

	BView* teamPropertiesView = new BView("team properties", B_WILL_DRAW);
	teamPropertiesView->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	BGroupLayout* layout = new BGroupLayout(B_HORIZONTAL);
	teamPropertiesView->SetLayout(layout);
	BGroupLayoutBuilder(layout)
		.Add(fIconView)
		.AddGroup(B_VERTICAL)
			.Add(fTeamName)
			.Add(fSysComponent)
			.Add(fQuitOverdue)
		.End()
		.AddGlue();

	fLayout = new BCardLayout();
	SetLayout(fLayout);
	fLayout->AddView(group);
	fLayout->AddView(teamPropertiesView);

	SetItem(NULL);
}