BOOL CRuleCountDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    int i,j,k,nRow=0,nTotalRestructuringRules=0,nTotalDescriptiveRules=0;
    CString R,S,T;
    wchar_t c[10];
    CDTData RowData;                 //create a special grid variable

    RowData.CreateArray(3);          //create a special array to hold a row of data
    try {
        m_starChapters.SetSize(200);
    }
    catch(CMemoryException*)
    {
        AfxMessageBox(L"Memory exception for Chapters array.",MB_OK);
    }
    try {
        m_starRestructuringRules.SetSize(200);
    }
    catch(CMemoryException*)
    {
        AfxMessageBox(L"Memory exception for Transfer Rules array.",MB_OK);
    }
    try {
        m_starDescriptiveRules.SetSize(200);
    }
    catch(CMemoryException*)
    {
        AfxMessageBox(L"Memory exception for Descriptive Rules array.",MB_OK);
    }
    m_datatblRuleCount.GetColumnSet().GetItem(2).SetHeading(L"Synthesizing Rules");
    T=m_pDoc->GetRuleCount();
    while (T!=L"")
    {
        i=T.Find(L"^");
        if (i>-1)
        {
            S=T.Left(i);
            T=T.Mid(i+1);
        }
        else
        {
            S=T;
            T=L"";
        }
        i=S.Find(L",");
        R=S.Left(i);     //get the chapter
        S=S.Mid(i+1);
        m_starChapters[nRow]=R;
        i=S.Find(L",");
        R=S.Left(i);     //get the restructuring rule count
        S=S.Mid(i+1);
        m_starRestructuringRules[nRow]=R;
        m_starDescriptiveRules[nRow]=S;
        nRow++;
    }
    if (m_starChapters[0]==L"Nouns 1" && m_starChapters[1]==L"Verbs 1" && m_starChapters[2]==L"Adjectives 1" && m_starChapters[3]==L"Adverbs 1" && m_starChapters[4]==L"Adpositions 1" && m_starChapters[5]==L"Pronouns 1" && m_starChapters[6]==L"Noun Phrases 1" && m_starChapters[7]==L"Clauses 1" && m_starChapters[8]==L"Discourse 1" && m_starChapters[9]==L"Theta Grids 1")
    {
        for (i=9; i<nRow; i++)
        {
            m_starChapters[i-9]=m_starChapters[i];
            m_starRestructuringRules[i-9]=m_starRestructuringRules[i];
            m_starDescriptiveRules[i-9]=m_starDescriptiveRules[i];
        }
        m_starChapters[0]=L"Grammar Introduction";
        nRow-=9;
    }
    for (i=0; i<nRow; i++)
    {
        R=m_starChapters[i];
        S=m_starRestructuringRules[i];
        j=_wtoi(S);                      //get the new total for the restructuring rules
        k=j-nTotalRestructuringRules;   //get the number of new restructuring rules
        nTotalRestructuringRules=j;     //save new total
        _itow(k,c,10);
        S=c;
        T=m_starDescriptiveRules[i];
        j=_wtoi(T);                      //get the new total for the descriptive rules
        k=j-nTotalDescriptiveRules;     //get the number of new descriptive rules
        nTotalDescriptiveRules=j;       //save new total
        _itow(k,c,10);
        T=c;
        RowData.PutItem(R, 0);     //enter a string for the first column
        RowData.PutItem(S, 1);     //enter a string for the first column
        RowData.PutItem(T, 2);     //enter a string for the first column
        m_datatblRuleCount.GetRowSet().GetItem(i).SetValue(RowData); //add row to end of table
    }
    m_datatblRuleCount.GetRowSet().SetCount(i);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}