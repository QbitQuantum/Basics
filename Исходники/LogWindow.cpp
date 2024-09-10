void CLogWindow::updateSettingToServer()
{
    Network::Bundle* pBundle = Network::Bundle::createPoolObject();
    (*pBundle).newMessage(LoggerInterface::updateLogWatcherSetting);

    CguiconsoleDlg* dlg = static_cast<CguiconsoleDlg*>(theApp.m_pMainWnd);
    int32 uid = dlg->getSelTreeItemUID();
    (*pBundle) << uid;

    (*pBundle) << getSelLogTypes();

    CString apporder;
    m_appIDEdit.GetWindowTextW(apporder);

    char* cs = KBEngine::strutil::wchar2char(apporder.GetBuffer(0));
    COMPONENT_ORDER order = atoi(cs);
    free(cs);

    (*pBundle) << order;

    m_appIDEdit1.GetWindowTextW(apporder);
    cs = KBEngine::strutil::wchar2char(apporder.GetBuffer(0));
    order = atoi(cs);
    free(cs);

    (*pBundle) << order;

    CString date;
    m_dateEdit.GetWindowTextW(date);
    cs = KBEngine::strutil::wchar2char(date.GetBuffer(0));
    (*pBundle) << cs;
    free(cs);

    CString keystr;
    m_findEdit.GetWindowTextW(keystr);
    cs = KBEngine::strutil::wchar2char(keystr.GetBuffer(0));
    (*pBundle) << cs;
    free(cs);

    int8 count = 0;
    std::vector<KBEngine::COMPONENT_TYPE> vec = getSelComponents();
    count = vec.size();
    (*pBundle) << count;
    std::vector<KBEngine::COMPONENT_TYPE>::iterator iter = vec.begin();
    for(; iter != vec.end(); iter++)
    {
        (*pBundle) << (*iter);
    }

    HTREEITEM item = dlg->hasCheckApp(LOGGER_TYPE);
    if(item == NULL)
    {
        ::AfxMessageBox(L"logger no select!");
        Network::Bundle::reclaimPoolObject(pBundle);
        return;
    }

    dlg = static_cast<CguiconsoleDlg*>(theApp.m_pMainWnd);
    Network::Address addr = dlg->getTreeItemAddr(item);
    Network::Channel* pChannel = dlg->networkInterface().findChannel(addr);
    if(pChannel == NULL)
    {
        ::AfxMessageBox(L"logger is error!");
        Network::Bundle::reclaimPoolObject(pBundle);
        return;
    }

    bool first = m_loglist.GetCount() <= 0;
    (*pBundle) << first;
    pChannel->send(pBundle);
}