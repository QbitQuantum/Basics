void LWDiaryDetails::OnSelectedRradiodisplay(long ButtonNum) 
{
	parent->RefreshData(0);
	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIODISPLAY);
	pradio->SetCurrentSelection(0);
	
}