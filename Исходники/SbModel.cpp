void
SbModel::fireSbModelChanged(void)
{
	wxCommandEvent event(anEVT_ROW_SIZECHANGE);
	event.SetInt(entries_.size());
	ProcessEvent(event);
}