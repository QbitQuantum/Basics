void
PersonView::MessageReceived(BMessage* msg)
{
	msg->PrintToStream();
	switch (msg->what) {
		case M_SAVE:
			Save();
			break;

		case M_REVERT:
			if (fPictureView)
				fPictureView->Revert();

			if (fAddressWindow)
				fAddressWindow->Reload();

			for (int32 i = fControls.CountItems() - 1; i >= 0; i--)
				fControls.ItemAt(i)->Reload();
			break;

		case M_SELECT:
			for (int32 i = fControls.CountItems() - 1; i >= 0; i--) {
				BTextView* text = fControls.ItemAt(i)->TextView();
				if (text->IsFocus()) {
					text->Select(0, text->TextLength());
					break;
				}
			}
			break;

		case M_GROUP_MENU:
		{
			/*const char* name = NULL;
			if (msg->FindString("group", &name) == B_OK)
				SetAttribute(fCategoryAttribute, name, false);*/
			break;
		}

		case M_SHOW_LOCATIONS:
		{
			if (fAddressWindow == NULL) {
				fAddressWindow = new AddressWindow(fContact);
			}
			fAddressWindow->Show();
			fAddressWindow->Activate(true);
			break;
		}

		case M_ADD_FIELD:
		{
			field_type type;
			if (msg->FindInt32("field_type", (int32*)&type) == B_OK) {
				BContactField* contactField 
					= BContactField::InstantiateChildClass(type);
				fContact->AddField(contactField);
				AddNewField(contactField);
				fSaved = false;
			}
			break;
		}

		case M_REMOVE_FIELD:
		{
			ContactFieldTextControl* control;
			if (msg->FindPointer("fieldtextcontrol",
				(void**)&control) == B_OK) {
				_RemoveField(control);
				fSaved = false;
			}
			break;
		}
	}
}