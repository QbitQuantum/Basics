CELFProgramView::CELFProgramView(HWND hParent, CELF* pELF)
: CDialog(MAKEINTRESOURCE(IDD_ELFVIEW_PROGRAMVIEW), hParent)
, m_nProgram(-1)
, m_pELF(pELF)
{
	SetClassPtr();

	m_pType		= new Framework::Win32::CEdit(GetItem(IDC_ELFVIEW_PROGRAMVIEW_TYPE_EDIT));
	m_pOffset	= new Framework::Win32::CEdit(GetItem(IDC_ELFVIEW_PROGRAMVIEW_OFFSET_EDIT));
	m_pVAddr	= new Framework::Win32::CEdit(GetItem(IDC_ELFVIEW_PROGRAMVIEW_VADDR_EDIT));
	m_pPAddr	= new Framework::Win32::CEdit(GetItem(IDC_ELFVIEW_PROGRAMVIEW_PADDR_EDIT));
	m_pFileSize	= new Framework::Win32::CEdit(GetItem(IDC_ELFVIEW_PROGRAMVIEW_FILESIZE_EDIT));
	m_pMemSize	= new Framework::Win32::CEdit(GetItem(IDC_ELFVIEW_PROGRAMVIEW_MEMSIZE_EDIT));
	m_pFlags	= new Framework::Win32::CEdit(GetItem(IDC_ELFVIEW_PROGRAMVIEW_FLAGS_EDIT));
	m_pAlign	= new Framework::Win32::CEdit(GetItem(IDC_ELFVIEW_PROGRAMVIEW_ALIGN_EDIT));

	RECT columnEditBoxSize;
	SetRect(&columnEditBoxSize, 0, 0, 70, 12);
	MapDialogRect(m_hWnd, &columnEditBoxSize);
	unsigned int columnEditBoxWidth = columnEditBoxSize.right - columnEditBoxSize.left;
	unsigned int columnEditBoxHeight = columnEditBoxSize.bottom - columnEditBoxSize.top;

	RECT columnLabelSize;
	SetRect(&columnLabelSize, 0, 0, 70, 8);
	MapDialogRect(m_hWnd, &columnLabelSize);
	unsigned int columnLabelWidth = columnLabelSize.right - columnLabelSize.left;
	unsigned int columnLabelHeight = columnLabelSize.bottom - columnLabelSize.top;

	m_pLayout = Framework::CGridLayout::Create(2, 9);

	m_pLayout->SetObject(0, 0, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnLabelWidth, columnLabelHeight, new Framework::Win32::CStatic(GetItem(IDC_ELFVIEW_PROGRAMVIEW_TYPE_LABEL))));
	m_pLayout->SetObject(0, 1, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnLabelWidth, columnLabelHeight, new Framework::Win32::CStatic(GetItem(IDC_ELFVIEW_PROGRAMVIEW_OFFSET_LABEL))));
	m_pLayout->SetObject(0, 2, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnLabelWidth, columnLabelHeight, new Framework::Win32::CStatic(GetItem(IDC_ELFVIEW_PROGRAMVIEW_VADDR_LABEL))));
	m_pLayout->SetObject(0, 3, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnLabelWidth, columnLabelHeight, new Framework::Win32::CStatic(GetItem(IDC_ELFVIEW_PROGRAMVIEW_PADDR_LABEL))));
	m_pLayout->SetObject(0, 4, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnLabelWidth, columnLabelHeight, new Framework::Win32::CStatic(GetItem(IDC_ELFVIEW_PROGRAMVIEW_FILESIZE_LABEL))));
	m_pLayout->SetObject(0, 5, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnLabelWidth, columnLabelHeight, new Framework::Win32::CStatic(GetItem(IDC_ELFVIEW_PROGRAMVIEW_MEMSIZE_LABEL))));
	m_pLayout->SetObject(0, 6, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnLabelWidth, columnLabelHeight, new Framework::Win32::CStatic(GetItem(IDC_ELFVIEW_PROGRAMVIEW_FLAGS_LABEL))));
	m_pLayout->SetObject(0, 7, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnLabelWidth, columnLabelHeight, new Framework::Win32::CStatic(GetItem(IDC_ELFVIEW_PROGRAMVIEW_ALIGN_LABEL))));

	m_pLayout->SetObject(1, 0, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnEditBoxWidth, columnEditBoxHeight, m_pType));
	m_pLayout->SetObject(1, 1, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnEditBoxWidth, columnEditBoxHeight, m_pOffset));
	m_pLayout->SetObject(1, 2, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnEditBoxWidth, columnEditBoxHeight, m_pVAddr));
	m_pLayout->SetObject(1, 3, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnEditBoxWidth, columnEditBoxHeight, m_pPAddr));
	m_pLayout->SetObject(1, 4, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnEditBoxWidth, columnEditBoxHeight, m_pFileSize));
	m_pLayout->SetObject(1, 5, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnEditBoxWidth, columnEditBoxHeight, m_pMemSize));
	m_pLayout->SetObject(1, 6, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnEditBoxWidth, columnEditBoxHeight, m_pFlags));
	m_pLayout->SetObject(1, 7, Framework::Win32::CLayoutWindow::CreateTextBoxBehavior(columnEditBoxWidth, columnEditBoxHeight, m_pAlign));
	m_pLayout->SetObject(1, 8, Framework::CLayoutStretch::Create());

	RefreshLayout();
}