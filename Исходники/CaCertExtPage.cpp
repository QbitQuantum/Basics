BOOL CCaCertExtPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO: Add extra initialization here

    ClassXP(GetDlgItem(IDC_LIST)->m_hWnd,TRUE);


    CImageList * pImgList = ((CMiniCaApp *)AfxGetApp())->GetImgList();
    m_CheckList.SetImageList(pImgList,LVSIL_SMALL);//用来改变LISTCTRL行宽度

    ListView_SetExtendedListViewStyle(m_CheckList.m_hWnd, LVS_EX_CHECKBOXES | LVS_EX_SUBITEMIMAGES |
                                      LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    CRect rect;
    m_CheckList.GetClientRect(rect);
    int width = rect.Width();

    m_CheckList.InsertColumn(0, MiniCT_0400, LVCFMT_LEFT,width/3); //MiniCT_0400 "扩展名称"
    m_CheckList.InsertColumn(1, MiniCT_0401, LVCFMT_LEFT,2*width/3);		//MiniCT_0401 "内容"


    CString m_IniPathName = ((CMiniCaApp *)AfxGetApp())->GetAppPath() +  "\\MiniExt.ini";

    //加载配置信息
    //检测是否已经打开,如果打不开,则重新写入
    CFile file;
    if(!file.Open(m_IniPathName,CFile::modeRead))
    {
        /*得到配置,判断是否繁体环境*/
        HRSRC hRsrc = 0;

        if(CMiniCaApp::IsBig())
            hRsrc = FindResource(NULL,MAKEINTRESOURCE(IDR_MINICA_EXT_BG),"INI");
        else
            hRsrc = FindResource(NULL,MAKEINTRESOURCE(IDR_MINICA_EXT),"INI");

        DWORD lenCert = SizeofResource(NULL, hRsrc);
        HGLOBAL hgCert=LoadResource(NULL,hRsrc);
        LPSTR lpCert=(LPSTR)LockResource(hgCert);

        if(file.Open(m_IniPathName,CFile::modeCreate|CFile::modeWrite))	//存文件
        {
            file.Write(lpCert,lenCert);
        }

    }
    file.Close();

    GetIniInfo(m_IniPathName);

    /*LVS_EX_CHECKBOXES 使用检查框
    LVS_EX_FULLROWSELECT 选择整行
    LVS_EX_GRIDLINES 在REPORT中画出分隔线
    LVS_EX_HEADERDRAGDROP LVS_REPORT时可以利用drag-and-drop重新排序
    LVS_EX_SUBITEMIMAGES 允许在子项中显示image
    LVS_EX_TRACKSELECT 当鼠标指到某一项时便自动选择该项 */

    m_toolTip.Create(this);
    m_toolTip.AddTool(GetDlgItem(IDC_LIST), "证书扩展设置\r详细设置请转到配置选项卡");


    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}