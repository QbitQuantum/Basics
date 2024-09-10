void CSFlight::OnTextChangedCboAll(LPCTSTR text, short index) 
{
	// TODO: Add your control notification handler code here
#define	SG2C_CHANGELEVEL   tmp
#include "sg2combo.h"
	OPTIONS

		CRCombo* combo;

	if (GETDLGITEM(IDC_CBO_SPINS)->GetIndex() == 1)
	{
		combo=GETDLGITEM(IDC_CBO_ENGINEMANAGEMENT);
		combo->SetEnabled(true);

		if (GETDLGITEM(IDC_CBO_ENGINEMANAGEMENT)->GetIndex() == 0)
		{
			combo=GETDLGITEM(IDC_CBO_PROPPITCH);
			combo->SetEnabled(true);
		}else
		{
			combo=GETDLGITEM(IDC_CBO_PROPPITCH);
			combo->SetEnabled(false);
			Save_Data.flightdifficulty %= FD_PROPPITCH;
		}
	}else
	{
		combo=GETDLGITEM(IDC_CBO_ENGINEMANAGEMENT);
		combo->SetEnabled(false);
		Save_Data.flightdifficulty %= FD_ENGINEMANAGMENT;

		combo=GETDLGITEM(IDC_CBO_PROPPITCH);
		combo->SetEnabled(false);
		Save_Data.flightdifficulty %= FD_PROPPITCH;
	}
}