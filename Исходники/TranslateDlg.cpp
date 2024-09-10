BOOL CTranslateDlg::OnInitDialog()
{
   CDialogEx::OnInitDialog();

   // Add "About..." menu item to system menu.

   // IDM_ABOUTBOX must be in the system command range.
   ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
   ASSERT(IDM_ABOUTBOX < 0xF000);

   CMenu* pSysMenu = GetSystemMenu(FALSE);
   if (pSysMenu != NULL)
   {
      BOOL bNameValid;
      CString strAboutMenu;
      bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
      ASSERT(bNameValid);
      if (!strAboutMenu.IsEmpty())
      {
         pSysMenu->AppendMenu(MF_SEPARATOR);
         pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
      }
   }

   // Set the icon for this dialog.  The framework does this automatically
   //  when the application's main window is not a dialog
   SetIcon(m_hIcon, TRUE);			// Set big icon
   SetIcon(m_hIcon, FALSE);		// Set small icon

   // TODO: Add extra initialization here

   CStringArray sLanguages;
   m_cTranslator.GetAllLanguages(sLanguages);
   int count = sLanguages.GetCount();
   for (int i = 0 ; i < count; i++)
      m_cToLang.AddString(sLanguages.GetAt(i));

   if(count)
      m_cToLang.SelectString(0, _T("Kannada"));

   m_font.CreateFont(30, 0, 0, 0, FW_DEMIBOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 0, 0, NULL);
   m_cTranslatedText.SetFont(&m_font,TRUE);

   m_Errorfont.CreateFont(20, 0, 0, 0, FW_NORMAL, TRUE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 0, 0, NULL);
   m_cErrorText.SetFont(&m_Errorfont,TRUE);

   return TRUE;  // return TRUE  unless you set the focus to a control
}