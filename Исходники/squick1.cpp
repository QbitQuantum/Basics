void CSQuick1::OnTextChangedEltnum(LPCTSTR text, short index) 
{

	// TODO: Add your control notification handler code here
	quickdef.plac=(quickdef.plac&-4)
					+GETDLGITEM(IDC_ELTNUM)->GetIndex();
	
}