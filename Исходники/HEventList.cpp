void
HEventList::SelectionChanged()
{
	BColumnListView::SelectionChanged();

	HEventRow* row = (HEventRow*)CurrentSelection();
	if (row != NULL) {
		entry_ref ref;
		BMediaFiles().GetRefFor(fType, row->Name(), &ref);

		BPath path(&ref);
		if (path.InitCheck() == B_OK || ref.name == NULL
			|| strcmp(ref.name, "") == 0) {
			row->SetPath(path.Path());
			UpdateRow(row);
		} else {
			printf("name %s\n", ref.name);
			BMediaFiles().RemoveRefFor(fType, row->Name(), ref);
			BAlert* alert = new BAlert("alert",
				B_TRANSLATE("No such file or directory"), B_TRANSLATE("OK"));
			alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
			alert->Go();
			return;
		}
		BMessage msg(M_EVENT_CHANGED);
		msg.AddString("name", row->Name());
		msg.AddString("path", row->Path());
		Window()->PostMessage(&msg);
	}
}