/***************************************************
~CUGNoteType - Destructor
	Clean up all allocated resources
****************************************************/
CUGNoteType::~CUGNoteType(){

	if(m_timerID != 0)
		KillTimer(m_ctrl->m_hWnd,m_timerID);
}