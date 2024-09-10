void CDlgHiddenColumns::CreateCheckboxes() {
    int i, stdCount, actualCount;
    bool val;
    CAdvancedFrame* pFrame = (CAdvancedFrame*)GetParent();
    wxASSERT(wxDynamicCast(pFrame, CAdvancedFrame));
    
    wxNotebook* pNotebook = pFrame->GetNotebook();
    wxASSERT(pNotebook);

    actualCount = m_checkbox_list.size();
    for (i=0; i<actualCount; ++i) {
        std::vector <wxCheckBox*> *checkbox_list = m_checkbox_list[i];
        checkbox_list->clear();
        delete checkbox_list;
    }
    m_checkbox_list.clear();
    
    wxWindow*       pwndNotebookPage = NULL;
    CBOINCBaseView* pView = NULL;
    long            iIndex;
    long            iPageCount;

    iPageCount = (long)pNotebook->GetPageCount();

    for (iIndex = 0; iIndex < iPageCount; iIndex++) {
        pwndNotebookPage = pNotebook->GetPage(iIndex);
        wxASSERT(wxDynamicCast(pwndNotebookPage, CBOINCBaseView));

        pView = wxDynamicCast(pwndNotebookPage, CBOINCBaseView);
        wxASSERT(pView);

        CBOINCListCtrl* listPane = pView->GetListCtrl();
        if (!listPane) continue;

        m_pBOINCBaseView.push_back(pView);
        
        std::vector <wxCheckBox*> *checkbox_list = new std::vector <wxCheckBox*>;

        wxStaticBox* tabStaticBox = new wxStaticBox(m_scrolledWindow, -1, pView->GetViewDisplayName());
        wxStaticBoxSizer* tabStaticBoxSizer = new wxStaticBoxSizer( tabStaticBox, wxVERTICAL );
        wxGridSizer* checkboxSizer = new wxGridSizer(2, wxSize(0,3));

        stdCount = pView->m_aStdColNameOrder->GetCount();
        for (i=0; i<stdCount; ++i) {
            wxString columnLabel = pView->m_aStdColNameOrder->Item(i);
            wxCheckBox* ckbox = new wxCheckBox(tabStaticBox, wxID_ANY, columnLabel);
            checkboxSizer->Add(ckbox, 0, wxLEFT, 25);
            val = false;
            if (pView->m_iColumnIDToColumnIndex[i] >= 0) val = true;
            ckbox->SetValue(val);
            checkbox_list->push_back(ckbox);
        }
        m_checkbox_list.push_back(checkbox_list);
        
        tabStaticBoxSizer->Add(checkboxSizer, 0, wxEXPAND, 1 );
        m_scrolledSizer->Add(tabStaticBoxSizer, 0, wxEXPAND, 1 );
    }

    m_scrolledWindow->SetSizer( m_scrolledSizer );
    m_scrolledWindow->Layout();
    m_scrolledSizer->Fit( m_scrolledWindow );
}