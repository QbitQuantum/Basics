void QuickParameters::OnTextChangedTargtype(LPCTSTR Caption, short index) 
{
	targtype=GETDLGITEM(IDC_TARGTYPE)->GetIndex();
	targentry=0;
	CSQuick1::quickdef.target=CSQuick1::quickdef.targets[targtype][targentry];

	TargNameCombo();
}