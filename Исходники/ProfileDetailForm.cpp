result
ProfileDetailForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	Header* pHeader = GetHeader();
	AppAssert(pHeader);
	pHeader->SetStyle(HEADER_STYLE_TITLE);
	String getDetails;
	Application::GetInstance()->GetAppResource()->GetString(IDS_DETAILS, getDetails);
	pHeader->SetTitleText(getDetails);

	Footer* pFooter = GetFooter();
	AppAssert(pFooter);
	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);


	String getEdit;
	Application::GetInstance()->GetAppResource()->GetString(IDS_EDIT, getEdit);
	FooterItem footerEdit;
	footerEdit.Construct(ID_FOOTER_EDIT);
	footerEdit.SetText(getEdit);
	pFooter->AddItem(footerEdit);


	String getDelete;
	Application::GetInstance()->GetAppResource()->GetString(IDS_DELETE, getDelete);
	FooterItem footerDelete;
	footerDelete.Construct(ID_FOOTER_DELETE);
	footerDelete.SetText(getDelete);
	pFooter->AddItem(footerDelete);
	pFooter->AddActionEventListener(*this);

	SetFormBackEventListener(this);

	static const unsigned int COLOR_BACKGROUND_LABEL = 0xFFEFEDE5;
	static const unsigned int COLOR_TITLE_LABEL = 0xFF808080;

	static const int UI_X_POSITION_GAP = 20;
	static const int UI_WIDTH = GetClientAreaBounds().width - 40;
	static const int UI_X_POSITION_MIDDLE = UI_WIDTH / 4 + UI_X_POSITION_GAP;
	static const int UI_HEIGHT = 112;
	static const int UI_SPACE = 26;
	int yPosition = 0;

	ScrollPanel* pScrollPanel = new (std::nothrow) ScrollPanel();
	pScrollPanel->Construct(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height));

	String date;
	DateTime displayStartDate;
	DateTime displayDueDate;

	// Subject
	Label* pSubjectLabel = new (std::nothrow) Label();
	String getProfileName;
	Application::GetInstance()->GetAppResource()->GetString(IDS_PROFILE_NAME, getProfileName);
	pSubjectLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition, UI_WIDTH, UI_HEIGHT), getProfileName);
	pSubjectLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pSubjectLabel->SetTextColor(COLOR_TITLE_LABEL);
	pSubjectLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pSubjectLabel);

	__pSubjectLabelData = new (std::nothrow) Label();
	__pSubjectLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	__pSubjectLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(__pSubjectLabelData);

	// Start Date
	Label* pStartDateLabel = new (std::nothrow) Label();
	String getStartDatetime;
	Application::GetInstance()->GetAppResource()->GetString(IDS_START_DATETIME, getStartDatetime);
	pStartDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), getStartDatetime);
	pStartDateLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pStartDateLabel->SetTextColor(COLOR_TITLE_LABEL);
	pStartDateLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pStartDateLabel);

	__pStartDateLabelData = new (std::nothrow) Label();
	__pStartDateLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	__pStartDateLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(__pStartDateLabelData);

	// Due Date
	Label* pDueDateLabel = new (std::nothrow) Label();
	String getEndDatetime;
	Application::GetInstance()->GetAppResource()->GetString(IDS_END_DATETIME, getEndDatetime);
	pDueDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), getEndDatetime);
	pDueDateLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pDueDateLabel->SetTextColor(COLOR_TITLE_LABEL);
	pDueDateLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pDueDateLabel);

	__pDueDateLabelData = new (std::nothrow) Label();
	__pDueDateLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	__pDueDateLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(__pDueDateLabelData);

	// Location
	Label* pLocationLabel = new (std::nothrow) Label();
	String getLocation;
	Application::GetInstance()->GetAppResource()->GetString(IDS_LOCATION, getLocation);
	pLocationLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), getLocation);
	pLocationLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pLocationLabel->SetTextColor(COLOR_TITLE_LABEL);
	pLocationLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pLocationLabel);

	__pLocationLabelData = new (std::nothrow) Label();
	__pLocationLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	__pLocationLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(__pLocationLabelData);

	// Volume
	Label* pVolumeLabel = new (std::nothrow) Label();
	String getVolume;
	Application::GetInstance()->GetAppResource()->GetString(IDS_VOLUME, getVolume);
	pVolumeLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), getVolume);
	pVolumeLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pVolumeLabel->SetTextColor(COLOR_TITLE_LABEL);
	pVolumeLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pVolumeLabel);

	__pVolumeLabelData = new (std::nothrow) Label();
	__pVolumeLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	__pVolumeLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(__pVolumeLabelData);

	// Wifi
	Label* pWifiLabel = new (std::nothrow) Label();
	String getWifi;
	Application::GetInstance()->GetAppResource()->GetString(IDS_WIFI, getWifi);
	pWifiLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), getWifi);
	pWifiLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pWifiLabel->SetTextColor(COLOR_TITLE_LABEL);
	pWifiLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pWifiLabel);

	__pWifiLabelData = new (std::nothrow) Label();
	__pWifiLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	__pWifiLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(__pWifiLabelData);

	// Description
	Label* pDescriptionLabel = new (std::nothrow) Label();
	String getMemo;
	Application::GetInstance()->GetAppResource()->GetString(IDS_DESCRIPTION, getMemo);
	pDescriptionLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), getMemo);
	pDescriptionLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pDescriptionLabel->SetTextColor(COLOR_TITLE_LABEL);
	pDescriptionLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pDescriptionLabel);

	__pDescriptionLabelData = new (std::nothrow) Label();
	__pDescriptionLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	__pDescriptionLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(__pDescriptionLabelData);

	AddControl(pScrollPanel);

	return r;
}