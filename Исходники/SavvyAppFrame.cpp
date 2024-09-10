void SavvyEditor::AppFrame::OnMenuOpen(wxMenuEvent& a_Event)
{
	wxMenu* currMenu = a_Event.GetMenu();

	// Fixes a bug when clicking on the icon
	if (currMenu == NULL)
		return;

	wxMenuItem* currItem = NULL;
	if (currMenu->GetTitle() == "&Edit")
	{
		// Redo enable/disable
		if (m_LastSelectedTextCtrl->CanRedo())
		{
			currItem = currMenu->FindItem(wxID_REDO);
			EnableMenuItem(currItem, true);
		}
		else
		{
			currItem = currMenu->FindItem(wxID_REDO);
			EnableMenuItem(currItem, false);
		}

		// Undo enable/disable
		if (m_LastSelectedTextCtrl->CanUndo())
		{
			currItem = currMenu->FindItem(wxID_UNDO);
			EnableMenuItem(currItem, true);
		}
		else
		{
			currItem = currMenu->FindItem(wxID_UNDO);
			EnableMenuItem(currItem, false);
		}

		// Delete enable/disable
		if (!m_LastSelectedTextCtrl->IsEmpty())
		{
			currItem = currMenu->FindItem(wxID_DELETE);
			EnableMenuItem(currItem, true);
		}
		else
		{
			currItem = currMenu->FindItem(wxID_DELETE);
			EnableMenuItem(currItem, false);
		}

		// Copy
		if (m_LastSelectedTextCtrl->CanCopy())
		{
			currItem = currMenu->FindItem(wxID_COPY);
			EnableMenuItem(currItem, true);
		}
		else
		{
			currItem = currMenu->FindItem(wxID_COPY);
			EnableMenuItem(currItem, false);
		}

		// Cut
		if (m_LastSelectedTextCtrl->CanCut())
		{
			currItem = currMenu->FindItem(wxID_CUT);
			EnableMenuItem(currItem, true);
		}
		else
		{
			currItem = currMenu->FindItem(wxID_CUT);
			EnableMenuItem(currItem, false);
		}

		// Paste
		if (m_LastSelectedTextCtrl->CanPaste())
		{
			currItem = currMenu->FindItem(wxID_PASTE);
			EnableMenuItem(currItem, true);
		}
		else
		{
			currItem = currMenu->FindItem(wxID_PASTE);
			EnableMenuItem(currItem, false);
		}
	}
	else if (currMenu->GetTitle() == "&File")
	{
		if (m_LastSelectedTextCtrl->IsModified())
		{
			currItem = currMenu->FindItem(wxID_SAVE);
			EnableMenuItem(currItem, true);
		}
		else
		{
			currItem = currMenu->FindItem(wxID_SAVE);
			EnableMenuItem(currItem, false);
		}
	}
}