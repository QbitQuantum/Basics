void CSSound::OnTextChangedCboSounddriver(LPCTSTR Caption, short index) 
{
	// TODO: Add your control notification handler code here
	
	{
		CRCombo* combo;
		combo=GETDLGITEM(IDC_CBO_RADIOCHATTER);

		LPDSPORTINFO temp=NULL;
		
		if (_Miles.dig && _Miles.dig->DIG_valid())
		{
			temp=_Miles.dig->PortInfo;

			while (temp && index--)
			{
				temp=temp->next;
			}
			if (temp)
			{
				Save_Data.SFXDevice=temp->port;
			}
		}
	}
}