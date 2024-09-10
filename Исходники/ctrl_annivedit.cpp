/**
 * name:	OnMenuPopup
 * class:	CAnnivEditCtrl
 * desc:	is called to show a popup menu for all anniversaries of a contact
 * param:	none
 * return:	nothing
 **/
void CAnnivEditCtrl::OnDateChanged(LPNMDATETIMECHANGE lpChange)
{
	MAnnivDate *pCurrent = Current();

	if (pCurrent && !pCurrent->IsEqual(lpChange->st))
	{
		HWND hPs = GetParent(_hwndDlg);

		// save the new date to the structure
		DateTime_SetFormat(_hwndDate, NULL);
		pCurrent->Set(lpChange->st, TRUE);
		pCurrent->SetFlags(MAnnivDate::MADF_CHANGED|MAnnivDate::MADF_HASCUSTOM);
		
		// notify parent of the change
		SendMessage(hPs, PSM_CHANGED, NULL, NULL);
		EnableWindow(_hBtnDel, TRUE);

		// update the age and zodiac controls on the general propertysheetpage
		if (pCurrent->Id() == ANID_BIRTHDAY) 
		{
			SetZodiacAndAge(pCurrent);
		}
	}
}