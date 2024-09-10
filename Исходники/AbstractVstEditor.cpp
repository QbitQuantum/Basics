void CAbstractVstEditor::UpdateInputMenu()
{
     CMenu* pInfoMenu = m_pMenu->GetSubMenu(2);
    pInfoMenu->DeleteMenu(0, MF_BYPOSITION);

    CModDoc* pModDoc = m_pVstPlugin->GetModDoc();
    module_renderer* pSndFile = pModDoc->GetSoundFile();

    if (m_pInputMenu->m_hMenu)        {
            m_pInputMenu->DestroyMenu();
    }
    if (!m_pInputMenu->m_hMenu) {
            m_pInputMenu->CreatePopupMenu();
    }

    CString name;

    CArray<CVstPlugin*, CVstPlugin*> inputPlugs;
    m_pVstPlugin->GetInputPlugList(inputPlugs);
    for (int nPlug=0; nPlug<inputPlugs.GetSize(); nPlug++) {
            name.Format("FX%02d: %s", inputPlugs[nPlug]->m_nSlot+1, inputPlugs[nPlug]->m_pMixStruct->Info.szName);
            m_pInputMenu->AppendMenu(MF_STRING, ID_PLUGSELECT+inputPlugs[nPlug]->m_nSlot, name);
    }

    CArray<UINT, UINT> inputChannels;
    m_pVstPlugin->GetInputChannelList(inputChannels);
    for (int nChn=0; nChn<inputChannels.GetSize(); nChn++) {
            if (nChn==0 && inputPlugs.GetSize()) {
                    m_pInputMenu->AppendMenu(MF_SEPARATOR);
            }
            name.Format("Chn%02d: %s", inputChannels[nChn]+1, pSndFile->ChnSettings[inputChannels[nChn]].szName);
            m_pInputMenu->AppendMenu(MF_STRING, NULL, name);
    }

    CArray<UINT, UINT> inputInstruments;
    m_pVstPlugin->GetInputInstrumentList(inputInstruments);
    bool checked;
    for (int nIns=0; nIns<inputInstruments.GetSize(); nIns++) {
            checked=false;
            if (nIns==0 && (inputPlugs.GetSize() || inputChannels.GetSize())) {
                    m_pInputMenu->AppendMenu(MF_SEPARATOR);
            }
            name.Format("Ins%02d: %s", inputInstruments[nIns], (LPCTSTR)pSndFile->GetInstrumentName(inputInstruments[nIns]));
            if (inputInstruments[nIns] == (UINT)m_nInstrument)        checked=true;
            m_pInputMenu->AppendMenu(MF_STRING|(checked?MF_CHECKED:0), ID_SELECTINST+inputInstruments[nIns], name);
    }

    if ((inputPlugs.GetSize() == 0) &&
            (inputChannels.GetSize() == 0) &&
            (inputInstruments.GetSize() == 0)) {
            m_pInputMenu->AppendMenu(MF_STRING|MF_GRAYED, NULL, "None");
    }

    pInfoMenu->InsertMenu(0, MF_BYPOSITION|MF_POPUP, (UINT)m_pInputMenu->m_hMenu, "I&nputs");
}