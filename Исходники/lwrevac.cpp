void LWReviewAircraft::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LWReviewAircraft)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
	GETDLGITEM(IDC_RLISTBOXCTRL1)->AddString("",0);
}