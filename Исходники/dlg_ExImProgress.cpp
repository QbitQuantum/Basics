/**
 * name:	~CProgress
 * class:	CProgress
 * desc:	destroy the progress dialog and its data structure
 * params:	none
 * return:	nothing
 **/
CProgress::~CProgress()
{
	if(IsWindow(_hDlg)) DestroyWindow(_hDlg);
}