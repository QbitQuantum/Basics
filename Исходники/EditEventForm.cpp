result
EditEventForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	Header* pHeader = GetHeader();
	AppAssert(pHeader);
	pHeader->SetStyle(HEADER_STYLE_TITLE);
	pHeader->SetTitleText(L"Edit event");

	Footer* pFooter = GetFooter();
	AppAssert(pFooter);
	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);

	FooterItem footerSave;
	footerSave.Construct(ID_FOOTER_SAVE);
	footerSave.SetText(L"Save");
	pFooter->AddItem(footerSave);

	pFooter->AddActionEventListener(*this);
	SetFormBackEventListener(this);

	static const unsigned int COLOR_BACKGROUND_LABEL = 0xFFEFEDE5;
	static const unsigned int COLOR_TITLE_LABEL = 0xFF808080;
	static const unsigned int COLOR_TIMEZONE_DATA = 0xFF444444;

	static const int UI_X_POSITION_GAP = 20;
	static const int UI_WIDTH = GetClientAreaBounds().width - 40;
	static const int UI_X_POSITION_MIDDLE = UI_WIDTH / 4;
	static const int UI_HEIGHT = 112;
	static const int BUTTON_HEIGHT = 74;
	static const int UI_SPACE = 32;
	static const int FONT_SIZE = 36;

	int yPosition = 0;

	ScrollPanel* pScrollPanel = new (std::nothrow) ScrollPanel();
	pScrollPanel->Construct(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height));

	// Subject
	__pSubjectEditField = new (std::nothrow) EditField();
	__pSubjectEditField->Construct(Rectangle(UI_X_POSITION_GAP, yPosition, UI_WIDTH, UI_HEIGHT), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, EDIT_FIELD_TITLE_STYLE_TOP);
	__pSubjectEditField->SetTitleText(L"Subject");
	__pSubjectEditField->SetGuideText(L"Enter the subject");
	pScrollPanel->AddControl(__pSubjectEditField);


	int minYear = Calendarbook::GetMinDateTime().GetYear() + 1;
	int maxYear = Calendarbook::GetMaxDateTime().GetYear() - 1;

	// Start Date
	Label* pStartDateLabel = new (std::nothrow) Label();
	pStartDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), L"Start");
	pStartDateLabel->SetTextVerticalAlignment(ALIGNMENT_TOP);
	pStartDateLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pStartDateLabel->SetTextColor(COLOR_TITLE_LABEL);
	pStartDateLabel->SetBackgroundColor(COLOR_BACKGROUND_LABEL);
	pScrollPanel->AddControl(pStartDateLabel);

	__pStartEditDate = new (std::nothrow) EditDate();
	__pStartEditDate->Construct(Point(UI_X_POSITION_GAP, yPosition + 10));
	__pStartEditDate->SetCurrentDate();
	__pStartEditDate->SetYearRange(minYear, maxYear);
	__pStartEditDate->AddDateChangeEventListener(*this);
	pScrollPanel->AddControl(__pStartEditDate);

	__pStartEditTime = new (std::nothrow) EditTime();
	__pStartEditTime->Construct(Point(UI_X_POSITION_MIDDLE * 2 + UI_SPACE, yPosition + 10));
	__pStartEditTime->SetCurrentTime();
	__pStartEditTime->AddTimeChangeEventListener(*this);
	pScrollPanel->AddControl(__pStartEditTime);

	// End Date
	Label* pEndDateLabel = new (std::nothrow) Label();
	pEndDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), L"End");
	pEndDateLabel->SetTextVerticalAlignment(ALIGNMENT_TOP);
	pEndDateLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pEndDateLabel->SetTextColor(COLOR_TITLE_LABEL);
	pEndDateLabel->SetBackgroundColor(COLOR_BACKGROUND_LABEL);
	pScrollPanel->AddControl(pEndDateLabel);

	__pEndEditDate = new (std::nothrow) EditDate();
	__pEndEditDate->Construct(Point(UI_X_POSITION_GAP, yPosition + 10));
	__pEndEditDate->SetCurrentDate();
	__pEndEditDate->SetYearRange(minYear, maxYear);
	__pEndEditDate->AddDateChangeEventListener(*this);
	pScrollPanel->AddControl(__pEndEditDate);

	DateTime endTime;
	endTime = __pStartEditTime->GetTime();
	endTime.AddHours(1);

	__pEndEditTime = new (std::nothrow) EditTime();
	__pEndEditTime->Construct(Point(UI_X_POSITION_MIDDLE * 2 + UI_SPACE, yPosition + 10));
	__pEndEditTime->SetTime(endTime);
	__pEndEditTime->AddTimeChangeEventListener(*this);
	pScrollPanel->AddControl(__pEndEditTime);

	// TimeZone
	Label* pTimeZoneLabel = new (std::nothrow) Label();
	pTimeZoneLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), L"TimeZone");
	pTimeZoneLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pTimeZoneLabel->SetTextColor(COLOR_TITLE_LABEL);
	pTimeZoneLabel->SetBackgroundColor(COLOR_BACKGROUND_LABEL);
	pScrollPanel->AddControl(pTimeZoneLabel);

	Label* pTimeZoneDataLabel = new (std::nothrow) Label();
	pTimeZoneDataLabel->Construct(Rectangle(UI_X_POSITION_GAP + UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	pTimeZoneDataLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pTimeZoneDataLabel->SetText(GetTimezoneString());
	pTimeZoneDataLabel->SetTextColor(COLOR_TIMEZONE_DATA);
	pTimeZoneDataLabel->SetTextConfig(FONT_SIZE, LABEL_TEXT_STYLE_NORMAL);
	pTimeZoneDataLabel->SetBackgroundColor(COLOR_BACKGROUND_LABEL);
	pScrollPanel->AddControl(pTimeZoneDataLabel);

	// All day Event
	__pIsAllDayButton = new (std::nothrow) CheckButton();
	__pIsAllDayButton->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), CHECK_BUTTON_STYLE_ONOFF_SLIDING, BACKGROUND_STYLE_DEFAULT, false, L"All day Event");
	__pIsAllDayButton->SetActionId(ID_CHKBUTTON_ISALLDAY_CHECKED, ID_CHKBUTTON_ISALLDAY_UNCHECKED);
	__pIsAllDayButton->SetTextColor(COLOR_TITLE_LABEL);
	__pIsAllDayButton->AddActionEventListener(*this);
	pScrollPanel->AddControl(__pIsAllDayButton);

	// Location
	__pLocationEditField = new (std::nothrow) EditField();
	__pLocationEditField->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, EDIT_FIELD_TITLE_STYLE_TOP);
	__pLocationEditField->SetTitleText(L"Location");
	__pLocationEditField->SetGuideText(L"Enter the location");
	pScrollPanel->AddControl(__pLocationEditField);

	// Description
	__pDescriptionEditField = new (std::nothrow) EditField();
	__pDescriptionEditField->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, EDIT_FIELD_TITLE_STYLE_TOP);
	__pDescriptionEditField->SetTitleText(L"Description");
	__pDescriptionEditField->SetGuideText(L"Enter the description");
	pScrollPanel->AddControl(__pDescriptionEditField);

	// Reminder
	Label* pReminderLabel = new (std::nothrow) Label();
	pReminderLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), L"Reminder");
	pReminderLabel->SetTextColor(COLOR_TITLE_LABEL);
	pReminderLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pReminderLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(pReminderLabel);

	__pReminderEditField = new (std::nothrow) EditField();
	__pReminderEditField->Construct(Rectangle(UI_X_POSITION_GAP + UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH / 4, UI_HEIGHT), EDIT_FIELD_STYLE_NUMBER, INPUT_STYLE_FULLSCREEN, false, 5);
	__pReminderEditField->SetGuideText(L"0 ~ ");
	__pReminderEditField->SetName(L"Reminder");
	__pReminderEditField->SetTextAlignment(ALIGNMENT_CENTER);
	pScrollPanel->AddControl(__pReminderEditField);

	__pReminderContextButton = new (std::nothrow) Button();
	__pReminderContextButton->Construct(Rectangle(UI_X_POSITION_MIDDLE * 2 + UI_X_POSITION_GAP, yPosition + 19, UI_WIDTH / 2, BUTTON_HEIGHT), L"Minute(s)");
	__pReminderContextButton->SetActionId(ID_BUTTON_REMINDER);
	__pReminderContextButton->AddActionEventListener(*this);
	pScrollPanel->AddControl(__pReminderContextButton);

	__pReminderContextMenu = new (std::nothrow) ContextMenu();
	__pReminderContextMenu->Construct(Point(UI_X_POSITION_GAP + UI_WIDTH * 3 / 4, yPosition + UI_HEIGHT * 2), CONTEXT_MENU_STYLE_LIST, CONTEXT_MENU_ANCHOR_DIRECTION_UPWARD);
	__pReminderContextMenu->AddItem(L"Minute(s)", ID_CONTEXT_REMINDER_MINUTE);
	__pReminderContextMenu->AddItem(L"Hour(s)", ID_CONTEXT_REMINDER_HOUR);
	__pReminderContextMenu->AddItem(L"Day(s)", ID_CONTEXT_REMINDER_DAY);
	__pReminderContextMenu->AddItem(L"Week(s)", ID_CONTEXT_REMINDER_WEEK);
	__pReminderContextMenu->AddActionEventListener(*this);

	// Recurrence
	Label* pRecurrenceLabel = new (std::nothrow) Label();
	pRecurrenceLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), L"Recurrence");
	pRecurrenceLabel->SetTextConfig(29, LABEL_TEXT_STYLE_NORMAL);
	pRecurrenceLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pRecurrenceLabel->SetTextColor(COLOR_TITLE_LABEL);
	pRecurrenceLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pRecurrenceLabel);

	__pSetRecurrenceButton = new (std::nothrow) Button();
	__pSetRecurrenceButton->Construct(Rectangle(UI_X_POSITION_MIDDLE + UI_X_POSITION_GAP, yPosition + 19, UI_WIDTH * 3 / 4, BUTTON_HEIGHT), L"None");
	__pSetRecurrenceButton->SetActionId(ID_BUTTON_RECURRENCE);
	__pSetRecurrenceButton->AddActionEventListener(*this);
	pScrollPanel->AddControl(__pSetRecurrenceButton);

	// Priority
	Label* pPriorityLabel = new (std::nothrow) Label();
	pPriorityLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), L"Priority");
	pPriorityLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pPriorityLabel->SetTextColor(COLOR_TITLE_LABEL);
	pPriorityLabel->SetBackgroundColor(COLOR_BACKGROUND_LABEL);
	pScrollPanel->AddControl(pPriorityLabel);

	__pPriorityContextButton = new (std::nothrow) Button();
	__pPriorityContextButton->Construct(Rectangle(UI_X_POSITION_MIDDLE + UI_X_POSITION_GAP, yPosition + 19, UI_WIDTH * 3 / 4, BUTTON_HEIGHT), L"Low");
	__pPriorityContextButton->SetActionId(ID_BUTTON_PRIORITY);
	__pPriorityContextButton->AddActionEventListener(*this);
	pScrollPanel->AddControl(__pPriorityContextButton);

	__pPriorityContextMenu = new (std::nothrow) ContextMenu();
	__pPriorityContextMenu->Construct(Point(UI_X_POSITION_GAP + UI_WIDTH * 5 / 8, yPosition + UI_HEIGHT * 2), CONTEXT_MENU_STYLE_LIST, CONTEXT_MENU_ANCHOR_DIRECTION_UPWARD);
	__pPriorityContextMenu->AddItem(L"High", ID_CONTEXT_PRIORITY_HIGH);
	__pPriorityContextMenu->AddItem(L"Normal", ID_CONTEXT_PRIORITY_NORMAL);
	__pPriorityContextMenu->AddItem(L"Low", ID_CONTEXT_PRIORITY_LOW);
	__pPriorityContextMenu->AddActionEventListener(*this);

	// Sensitivity
	Label* pSensitivityLabel = new (std::nothrow) Label();
	pSensitivityLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), L"Sensitivity");
	pSensitivityLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pSensitivityLabel->SetTextColor(COLOR_TITLE_LABEL);
	pSensitivityLabel->SetBackgroundColor(COLOR_BACKGROUND_LABEL);
	pScrollPanel->AddControl(pSensitivityLabel);

	__pSensitivityContextButton = new (std::nothrow) Button();
	__pSensitivityContextButton->Construct(Rectangle(UI_X_POSITION_MIDDLE + UI_X_POSITION_GAP, yPosition + 19, UI_WIDTH * 3 / 4, BUTTON_HEIGHT), L"Public");
	__pSensitivityContextButton->SetActionId(ID_BUTTON_SENSITIVITY);
	__pSensitivityContextButton->AddActionEventListener(*this);
	pScrollPanel->AddControl(__pSensitivityContextButton);

	__pSensitivityContextMenu = new (std::nothrow) ContextMenu();
	__pSensitivityContextMenu->Construct(Point(UI_X_POSITION_GAP + UI_WIDTH * 5 / 8, yPosition + UI_HEIGHT * 2), CONTEXT_MENU_STYLE_LIST, CONTEXT_MENU_ANCHOR_DIRECTION_UPWARD);
	__pSensitivityContextMenu->AddItem(L"Public", ID_CONTEXT_SENSITIVITY_PUBLIC);
	__pSensitivityContextMenu->AddItem(L"Private", ID_CONTEXT_SENSITIVITY_PRIVATE);
	__pSensitivityContextMenu->AddItem(L"Confidential", ID_CONTEXT_SENSITIVITY_CONFIDENTIAL);
	__pSensitivityContextMenu->AddActionEventListener(*this);

	// Status
	Label* pStatusLabel = new (std::nothrow) Label();
	pStatusLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), L"Status");
	pStatusLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pStatusLabel->SetTextColor(COLOR_TITLE_LABEL);
	pStatusLabel->SetBackgroundColor(COLOR_BACKGROUND_LABEL);
	pScrollPanel->AddControl(pStatusLabel);

	__pStatusContextButton = new (std::nothrow) Button();
	__pStatusContextButton->Construct(Rectangle(UI_X_POSITION_MIDDLE + UI_X_POSITION_GAP, yPosition + 19, UI_WIDTH * 3 / 4, BUTTON_HEIGHT), L"None");
	__pStatusContextButton->SetActionId(ID_BUTTON_STATUS);
	__pStatusContextButton->AddActionEventListener(*this);
	pScrollPanel->AddControl(__pStatusContextButton);

	__pStatusContextMenu = new (std::nothrow) ContextMenu();
	__pStatusContextMenu->Construct(Point(UI_X_POSITION_GAP + UI_WIDTH * 5 / 8, yPosition + UI_HEIGHT * 2), CONTEXT_MENU_STYLE_LIST, CONTEXT_MENU_ANCHOR_DIRECTION_UPWARD);
	__pStatusContextMenu->AddItem(L"None", ID_CONTEXT_STATUS_NONE);
	__pStatusContextMenu->AddItem(L"Confirmed", ID_CONTEXT_STATUS_CONFIRMED);
	__pStatusContextMenu->AddItem(L"Cancelled", ID_CONTEXT_STATUS_CANCELLED);
	__pStatusContextMenu->AddItem(L"Tentative", ID_CONTEXT_STATUS_TENTATIVE);
	__pStatusContextMenu->AddActionEventListener(*this);

	AddControl(pScrollPanel);

	return r;
}