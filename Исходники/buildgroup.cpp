//-----------------------------------------------------------------------------
// Purpose: Create a new control in the context panel
// Input:	name: class name of control to create
//			controlKeys: keyvalues of settings for the panel.
//			name OR controlKeys should be set, not both.  
//			x,y position relative to base panel
// Output: Panel *newPanel, NULL if failed to create new control.
//-----------------------------------------------------------------------------
Panel *BuildGroup::NewControl( const char *name, int x, int y)
{
	Assert (name);
	
	Panel *newPanel = NULL;
	// returns NULL on failure
	newPanel = static_cast<EditablePanel *>(m_pParentPanel)->CreateControlByName(name);
	
	if (newPanel)
	{
		// panel successfully created
		newPanel->SetParent(m_pParentPanel);	
		newPanel->SetBuildGroup(this);
		newPanel->SetPos(x, y);

		char newFieldName[255];
		GetNewFieldName(newFieldName, sizeof(newFieldName), newPanel);
		newPanel->SetName(newFieldName);
		
		newPanel->AddActionSignalTarget(m_pParentPanel);
		newPanel->SetBuildModeEditable(true);
		newPanel->SetBuildModeDeletable(true);	
		
		// make sure it gets freed
		newPanel->SetAutoDelete(true);
	}	

	return newPanel;
}