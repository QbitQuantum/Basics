//-----------------------------------------------------------------------------
// Purpose: sets up the current control to edit
//-----------------------------------------------------------------------------
void BuildModeDialog::SetActiveControl(Panel *controlToEdit)
{	
	if (m_pCurrentPanel == controlToEdit)
	{
		// it's already set, so just update the property data and quit
		if (m_pCurrentPanel)
		{
			UpdateControlData(m_pCurrentPanel);
		}
		return;
	}

	// reset the data
	m_pCurrentPanel = controlToEdit;
	RemoveAllControls();
	m_pPanelList->m_pControls->MoveScrollBarToTop();

	if (!m_pCurrentPanel)
	{
		m_pStatusLabel->SetText("[nothing currently selected]");
		m_pStatusLabel->SetTextColorState(Label::CS_DULL);
		RemoveAllControls();
		return;
	}

	// get the control description string
	const char *controlDesc = m_pCurrentPanel->GetDescription();

	// parse out the control description
	int tabPosition = 1;
	while (1)
	{
		const char *dataType = ParseTokenFromString(&controlDesc);

		// finish when we have no more tokens
		if (*dataType == 0)
			break;

		// default the data type to a string
		int datat = TYPE_STRING;

		if (!stricmp(dataType, "int"))
		{
			datat = TYPE_STRING; //!! just for now
		}
		else if (!stricmp(dataType, "alignment"))
		{
			datat = TYPE_ALIGNMENT;
		}
		else if (!stricmp(dataType, "autoresize"))
		{
			datat = TYPE_AUTORESIZE;
		}
		else if (!stricmp(dataType, "corner"))
		{
			datat = TYPE_CORNER;
		}
		else if (!stricmp(dataType, "localize"))
		{
			datat = TYPE_LOCALIZEDSTRING;
		}

		// get the field name
		const char *fieldName = ParseTokenFromString(&controlDesc);

		int itemHeight = 18;

		// build a control & label
		Label *label = new Label(this, NULL, fieldName);
		label->SetSize(96, itemHeight);
		label->SetContentAlignment(Label::a_east);

		TextEntry *edit = NULL;
		ComboBox *editCombo = NULL;
		Button *editButton = NULL;
		if (datat == TYPE_ALIGNMENT)
		{
			// drop-down combo box
			editCombo = new ComboBox(this, NULL, 9, false);
			editCombo->AddItem("north-west", NULL);
			editCombo->AddItem("north", NULL);
			editCombo->AddItem("north-east", NULL);
			editCombo->AddItem("west", NULL);
			editCombo->AddItem("center", NULL);
			editCombo->AddItem("east", NULL);
			editCombo->AddItem("south-west", NULL);
			editCombo->AddItem("south", NULL);
			editCombo->AddItem("south-east", NULL);
		
			edit = editCombo;
		}
		else if (datat == TYPE_AUTORESIZE)
		{
			// drop-down combo box
			editCombo = new ComboBox(this, NULL, 4, false);
			editCombo->AddItem( "0 - no auto-resize", NULL);
			editCombo->AddItem( "1 - resize right", NULL);
			editCombo->AddItem( "2 - resize down", NULL);
			editCombo->AddItem( "3 - down & right", NULL);
		
			edit = editCombo;
		}
		else if (datat == TYPE_CORNER)
		{
			// drop-down combo box
			editCombo = new ComboBox(this, NULL, 4, false);
			editCombo->AddItem("0 - top-left", NULL);
			editCombo->AddItem("1 - top-right", NULL);
			editCombo->AddItem("2 - bottom-left", NULL);
			editCombo->AddItem("3 - bottom-right", NULL);
		
			edit = editCombo;
		}
		else if (datat == TYPE_LOCALIZEDSTRING)
		{
			editButton = new Button(this, NULL, "...");
			editButton->SetParent(this);
			editButton->AddActionSignalTarget(this);
			editButton->SetTabPosition(tabPosition++);
			editButton->SetTall( itemHeight );
			label->SetAssociatedControl(editButton);
		}
		else
		{
			// normal string edit
			edit = new CSmallTextEntry(this, NULL);
		}

		if (edit)
		{
			edit->SetTall( itemHeight );
			edit->SetParent(this);
			edit->AddActionSignalTarget(this);
			edit->SetTabPosition(tabPosition++);
			label->SetAssociatedControl(edit);
		}

		HFont smallFont = scheme()->GetIScheme( GetScheme() )->GetFont( "DefaultVerySmall" );

		if ( label )
		{
			label->SetFont( smallFont );
		}
		if ( edit )
		{
			edit->SetFont( smallFont );
		}
		if ( editCombo )
		{
			editCombo->SetFont( smallFont );
		}
		if ( editButton )
		{
			editButton->SetFont( smallFont );
		}

		// add to our control list
		m_pPanelList->AddItem(label, edit, editCombo, editButton, fieldName, datat);

		if ( edit )
		{
			m_pPanelList->m_pControls->AddItem(label, edit);
		}
		else
		{
			m_pPanelList->m_pControls->AddItem(label, editButton);
		}
	}

	// check and see if the current panel is a Label
	// iterate through the class hierarchy 
	if ( controlToEdit->IsBuildModeDeletable() )
	{
		m_pDeleteButton->SetEnabled(true);
	}
	else
	{
		m_pDeleteButton->SetEnabled(false);	
	}

	// update the property data in the dialog
	UpdateControlData(m_pCurrentPanel);
	
	// set our title
	if ( m_pBuildGroup->GetResourceName() )
	{
		m_pFileSelectionCombo->SetText(m_pBuildGroup->GetResourceName());
	}
	else
	{
		m_pFileSelectionCombo->SetText("[ no resource file associated with dialog ]");
	}

	m_pApplyButton->SetEnabled(false);
	InvalidateLayout();
	Repaint();
}