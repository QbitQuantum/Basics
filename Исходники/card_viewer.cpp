void CardViewer::onChangeSize() {
	wxSize ws = GetSize(), cs = GetClientSize();
	wxSize desired_cs = (wxSize)getRotation().getExternalSize() + ws - cs;
	if (desired_cs != cs) {
		wxCommandEvent ev(EVENT_SIZE_CHANGE, GetId());
		ProcessEvent(ev);
	}
}