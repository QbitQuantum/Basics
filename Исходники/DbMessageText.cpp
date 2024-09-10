//*****************************************************************************
bool CDbMessageText::operator == (
//Compare two strings.
//
//Params:
	CDbMessageText &text)   //(in)
//NOTE: This method cannot be const!
{
	return (WCScmp((const WCHAR *)*this, (const WCHAR *)text) == 0);
}