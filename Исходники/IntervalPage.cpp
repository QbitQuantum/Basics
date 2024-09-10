CIntervalPage::CIntervalPage() : CPropertyPage(CIntervalPage::IDD), m_dwElapse(ELAPSE_TIME)
{
	//{{AFX_DATA_INIT(CIntervalPage)
	m_csResult = _T("");
	m_nInputInterval = 0;
	m_csNotesPlayed = _T("");
	//}}AFX_DATA_INIT

	if (MMSYSERR_NOERROR != midiOutOpen(&m_hMidiOut, MIDIMAPPER, 0, 0, 0))
	{
		AfxMessageBox("Unable to open Midi O/P device");
		return ;
	}
}