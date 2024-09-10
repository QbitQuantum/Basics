result
CreateProfileForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	Header* pHeader = GetHeader();
	AppAssert(pHeader);
	pHeader->SetStyle(HEADER_STYLE_TITLE);
	String getProfileCreationTitle;
	Application::GetInstance()->GetAppResource()->GetString(IDS_CREATE_TITLE, getProfileCreationTitle);
	pHeader->SetTitleText(getProfileCreationTitle);

	Footer* pFooter = GetFooter();
	AppAssert(pFooter);
	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);

	FooterItem footerSave;
	footerSave.Construct(ID_BUTTON_SAVE);
	String getSave;
	Application::GetInstance()->GetAppResource()->GetString(IDS_SAVE, getSave);
	footerSave.SetText(getSave);
	pFooter->AddItem(footerSave);
	pFooter->AddActionEventListener(*this);

	SetFormBackEventListener(this);

	static const unsigned int COLOR_BACKGROUND_LABEL = 0xFFEFEDE5;
	static const unsigned int COLOR_TITLE_LABEL = 0xFF808080;

	static const int UI_X_POSITION_GAP = 20;
	static const int UI_WIDTH = GetClientAreaBounds().width - 40;
	static const int UI_X_POSITION_MIDDLE = UI_WIDTH / 4;
	static const int UI_HEIGHT = 112;
	static const int UI_SPACE = 26;
	int yPosition = 0;

	__pScrollPanel = new (std::nothrow) ScrollPanel();
	__pScrollPanel->Construct(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height));

	// Subject
	__pSubjectEditField = new (std::nothrow) EditField();
	__pSubjectEditField->Construct(Rectangle(UI_X_POSITION_GAP, yPosition, UI_WIDTH, UI_HEIGHT), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, EDIT_FIELD_TITLE_STYLE_TOP);
	String getProfileName, getProfileNameGuid;
	Application::GetInstance()->GetAppResource()->GetString(IDS_PROFILE_NAME, getProfileName);
	Application::GetInstance()->GetAppResource()->GetString(IDS_PROFILE_GUIDE, getProfileNameGuid);
	__pSubjectEditField->SetGuideText(getProfileNameGuid);
	__pSubjectEditField->SetName(L"Subject");
	__pSubjectEditField->SetTitleText(getProfileName);
	__pSubjectEditField->SetOverlayKeypadCommandButtonVisible(false);
	__pScrollPanel->AddControl(__pSubjectEditField);

	// Start Date
	int minYear = Calendarbook::GetMinDateTime().GetYear() + 1;
	int maxYear = Calendarbook::GetMaxDateTime().GetYear() - 1;

	Label* pStartDateLabel = new (std::nothrow) Label();
	String getStartDateTime, getEndDateTime;
	Application::GetInstance()->GetAppResource()->GetString(IDS_START_DATETIME, getStartDateTime);
	Application::GetInstance()->GetAppResource()->GetString(IDS_END_DATETIME, getEndDateTime);
	pStartDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), getStartDateTime);
	pStartDateLabel->SetTextVerticalAlignment(ALIGNMENT_TOP);
	pStartDateLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pStartDateLabel->SetTextColor(COLOR_TITLE_LABEL);
	pStartDateLabel->SetBackgroundColor(COLOR_BACKGROUND_LABEL);
	__pScrollPanel->AddControl(pStartDateLabel);

	__pStartEditDate = new (std::nothrow) EditDate();
	__pStartEditDate->Construct(Point(UI_X_POSITION_GAP, yPosition + 10));
	__pStartEditDate->SetCurrentDate();
	__pStartEditDate->SetYearRange(minYear, maxYear);
	__pStartEditDate->AddDateChangeEventListener(*this);
	__pScrollPanel->AddControl(__pStartEditDate);

	__pStartEditTime = new (std::nothrow) EditTime();
	__pStartEditTime->Construct(Point(UI_X_POSITION_MIDDLE * 2 + UI_SPACE, yPosition + 10));
	__pStartEditTime->SetCurrentTime();
	__pStartEditTime->AddTimeChangeEventListener(*this);
	__pScrollPanel->AddControl(__pStartEditTime);

	// Due Date
	Label* pDueDateLabel = new (std::nothrow) Label();
	pDueDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), getEndDateTime);
	pDueDateLabel->SetTextVerticalAlignment(ALIGNMENT_TOP);
	pDueDateLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pDueDateLabel->SetTextColor(COLOR_TITLE_LABEL);
	pDueDateLabel->SetBackgroundColor(COLOR_BACKGROUND_LABEL);
	__pScrollPanel->AddControl(pDueDateLabel);

	__pDueEditDate = new (std::nothrow) EditDate();
	__pDueEditDate->Construct(Point(UI_X_POSITION_GAP, yPosition + 10));
	__pDueEditDate->SetCurrentDate();
	__pDueEditDate->SetYearRange(minYear, maxYear);
	__pDueEditDate->AddDateChangeEventListener(*this);
	__pScrollPanel->AddControl(__pDueEditDate);

	DateTime endTime;
	endTime = __pStartEditTime->GetTime();
	endTime.AddHours(1);

	__pDueEditTime = new (std::nothrow) EditTime();
	__pDueEditTime->Construct(Point(UI_X_POSITION_MIDDLE * 2 + UI_SPACE, yPosition + 10));
	__pDueEditTime->SetTime(endTime);
	__pDueEditTime->AddTimeChangeEventListener(*this);
	__pScrollPanel->AddControl(__pDueEditTime);

	// Location
	String  getLocationGuide;
	Application::GetInstance()->GetAppResource()->GetString(IDS_LOCATION_GUIDE, getLocationGuide);

	__pLocationButton = new (std::nothrow) Button();
	__pLocationButton->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), getLocationGuide);
	__pLocationButton->SetActionId(ID_LOCATION_BUTTON);
	__pLocationButton->AddActionEventListener(*this);
	__pScrollPanel->AddControl(__pLocationButton);

	// Volume
	String getVolume;
	Application::GetInstance()->GetAppResource()->GetString(IDS_VOLUME, getVolume);
	__pVolumeSlider = new (std::nothrow) Slider();
	__pVolumeSlider->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH/*GetClientAreaBounds().width*/, UI_HEIGHT + 30), BACKGROUND_STYLE_DEFAULT, true, 0, 15);
	__pVolumeSlider->SetValue(5);
	__pVolumeSlider->SetTitleText(getVolume);
	__pVolumeSlider->AddAdjustmentEventListener(*this);
	__pScrollPanel->AddControl(__pVolumeSlider);

	// Wifi
	String getWifi;
	Application::GetInstance()->GetAppResource()->GetString(IDS_WIFI, getWifi);
	__pWifiCheckButton = new (std::nothrow) CheckButton();
	__pWifiCheckButton->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT),
			CHECK_BUTTON_STYLE_ONOFF_SLIDING, BACKGROUND_STYLE_DEFAULT, false, getWifi);
	__pWifiCheckButton->SetActionId(ID_BUTTON_CHECKED, ID_BUTTON_UNCHECKED, ID_BUTTON_SELECTED);
	__pWifiCheckButton->AddActionEventListener(*this);
	__pScrollPanel->AddControl(__pWifiCheckButton);

	// Description
	String getDescription, getDescriptionGuide;
	Application::GetInstance()->GetAppResource()->GetString(IDS_DESCRIPTION, getDescription);
	Application::GetInstance()->GetAppResource()->GetString(IDS_DESCRIPTION_GUIDE, getDescriptionGuide);
	__pDescriptionEditField = new (std::nothrow) EditField();
	__pDescriptionEditField->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, EDIT_FIELD_TITLE_STYLE_TOP);
	__pDescriptionEditField->SetGuideText(getDescriptionGuide);
	__pDescriptionEditField->SetName(L"Description");
	__pDescriptionEditField->SetTitleText(getDescription);
	__pDescriptionEditField->SetOverlayKeypadCommandButtonVisible(false);
	__pScrollPanel->AddControl(__pDescriptionEditField);

	AddControl(__pScrollPanel);

	return r;
}