DrivesPage::DrivesPage(WizardView* wizardView, const BootMenuList& menus,
	BMessage* settings, const char* name)
	:
	WizardPageView(settings, name),
	fWizardView(wizardView),
	fHasInstallableItems(false)
{
	BString text;
	text << B_TRANSLATE_COMMENT("Drives", "Title") << "\n"
		<< B_TRANSLATE("Please select the drive you want the boot manager to "
			"be installed to or uninstalled from.");
	BTextView* description = CreateDescription("description", text);
	MakeHeading(description);

	fDrivesView = new BListView("drives", B_SINGLE_SELECTION_LIST,
		B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE | B_FULL_UPDATE_ON_RESIZE);
	fDrivesView->SetSelectionMessage(new BMessage(kMsgSelectionChanged));

	BScrollView* scrollView = new BScrollView("scrollView", fDrivesView, 0,
		false, true);

	SetLayout(new BGroupLayout(B_VERTICAL));

	BLayoutBuilder::Group<>((BGroupLayout*)GetLayout())
		.Add(description, 0.5)
		.Add(scrollView, 1);

	_UpdateWizardButtons(NULL);
	_FillDrivesView(menus);
}