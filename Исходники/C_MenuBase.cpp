void MenuBaseC::MenuOpen(bool   defaultButtonOK,
                         bool   clearButtonOK)
{
    FormContainer* pForm = m_pFormContainer;
    ASSERT(pForm);
    CWnd* currWnd = pForm->GetWindow();

    buttonForm.Create(currWnd, WS_DLGFRAME);
    mainForm.Create(currWnd);
    pForm->ResetForm();
    mainForm.ShowWindow(SW_SHOW);
    mainForm.GetParentWnd()->ShowWindow(SW_SHOW);

    propClear.SetSensitive(clearButtonOK);
    propDefault.SetSensitive(defaultButtonOK);

    if (currWnd)
        {
            currWnd->Invalidate();  // attempt to fix RRs bug with overlaying menus
            currWnd->UpdateWindow();
        }
}