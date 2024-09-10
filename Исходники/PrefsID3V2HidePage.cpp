int CPrefsID3V2HidePage::GetWidthForCol(int ncol)
{
	CListCtrl* pListCtrl = &(pMainDlg->m_lvtabPage1.m_ID3v2ListCtrl);
	CRect rect;
	pListCtrl->GetClientRect(&rect);
	int nColInterval = rect.Width()/4;

	switch(ncol)
	{
	case 0:
		return nColInterval*2;
		break;
	case 1:
	case 2:
	case 3:
	case 5:
		return nColInterval;
		break;
	case 4:
	case 6:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
		return nColInterval/4;
		break;
	case 7:
	case 8:
	case 9:
	case 10:
	case 14:
	case 16:
		return nColInterval/2;
		break;
	case 11:
	case 12:
	case 15:
	case 17:
		return nColInterval/3;
		break;
	case 13:
		return nColInterval*2/3;
		break;
	default:
		return nColInterval;
		break;
	}
	
}