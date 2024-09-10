void CGetAssgnUpdatesDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    CRect rcDlg;
    GetWindowRect(&rcDlg);
    ScreenToClient(&rcDlg);

    const int commGrBottom = 95;
    const int commGrRight = 30;

    const int macGrBottom = 199;
    const int macGrRight = 30;

    CRect rc;
    if(m_whiteBkg)
    {
        m_whiteBkg.GetWindowRect(&rc);
        ScreenToClient(&rc);
        rc.right = rcDlg.right - 18;
        rc.bottom = rcDlg.bottom - 43;
        rc.top = rcDlg.bottom - 303;
        m_whiteBkg.MoveWindow(rc);
    }
    if(m_whiteBkg2)
    {
        m_whiteBkg2.GetWindowRect(&rc);
        ScreenToClient(&rc);
        rc.right = rcDlg.right - 18;
        m_whiteBkg2.MoveWindow(rc);
    }
    if(m_whiteBkg3)
    {
        m_whiteBkg3.GetWindowRect(&rc);
        ScreenToClient(&rc);
        rc.bottom = rcDlg.bottom - 57;
        m_whiteBkg3.MoveWindow(rc);
    }
    if(m_whiteBkg4)
    {
        m_whiteBkg4.GetWindowRect(&rc);
        ScreenToClient(&rc);
        rc.bottom = rcDlg.bottom - 57;
        rc.right = rcDlg.right - 18;
        rc.left = rcDlg.right - 30;
        m_whiteBkg4.MoveWindow(rc);
    }
    if(m_frame)
    {
        m_frame.GetWindowRect(&rc);
        ScreenToClient(&rc);
        rc.right = rcDlg.right - 18;
        rc.bottom = rcDlg.bottom - 42;
        m_frame.MoveWindow(rc);
    }
    if(m_listCtrl)
    {
        m_listCtrl.GetWindowRect(&rc);
        ScreenToClient(&rc);
        rc.right = rcDlg.right - 30;
        rc.bottom = rcDlg.bottom - 303;
        m_listCtrl.MoveWindow(rc);
    }
    if(m_AcceptButton)
    {
        m_AcceptButton.GetWindowRect(&rc);
        ScreenToClient(&rc);
        rc.bottom = rcDlg.bottom - 59;
        rc.top = rc.bottom	- 23;
        m_AcceptButton.MoveWindow(rc);
    }
    if(m_RejectButton)
    {
        m_RejectButton.GetWindowRect(&rc);
        ScreenToClient(&rc);
        rc.bottom = rcDlg.bottom - 59;
        rc.top = rc.bottom	- 23;
        m_RejectButton.MoveWindow(rc);
    }
    if(m_ResetButton)
    {
        m_ResetButton.GetWindowRect(&rc);
        ScreenToClient(&rc);
        rc.bottom = rcDlg.bottom - 59;
        rc.top = rc.bottom	- 23;
        m_ResetButton.MoveWindow(rc);
    }
    if(m_buttonOK)
    {
        m_buttonOK.GetWindowRect(&rc);
        ScreenToClient(&rc);
        rc.bottom = rcDlg.bottom - 12;
        rc.top = rc.bottom	- 23;
        rc.right = rcDlg.right - 100;
        rc.left = rc.right - 75;
        m_buttonOK.MoveWindow(rc);
    }
    if(m_buttonCancel)
    {
        m_buttonCancel.GetWindowRect(&rc);
        ScreenToClient(&rc);
        rc.bottom = rcDlg.bottom - 12;
        rc.top = rc.bottom	- 23;
        rc.right = rcDlg.right - 17;
        rc.left = rc.right - 75;
        m_buttonCancel.MoveWindow(rc);
    }

    if (m_GrBoxMarkAsComplete)
    {
        CRect rcGrBoxMarkAsComplete;
        m_GrBoxMarkAsComplete.GetWindowRect(&rcGrBoxMarkAsComplete);
        ScreenToClient(&rcGrBoxMarkAsComplete);
        rcGrBoxMarkAsComplete.bottom = rcDlg.bottom - macGrBottom;
        rcGrBoxMarkAsComplete.top = rcGrBoxMarkAsComplete.bottom - 93;
        rcGrBoxMarkAsComplete.right = rcDlg.right - macGrRight;
        m_GrBoxMarkAsComplete.MoveWindow(rcGrBoxMarkAsComplete);

        if(m_radioNone)
        {
            CRect rcRadioNone;
            m_radioNone.GetWindowRect(&rcRadioNone);
            int w = rcRadioNone.Width();

            rcRadioNone.SetRect(
                (rcGrBoxMarkAsComplete.left+rcGrBoxMarkAsComplete.right)/2+14,
                rcGrBoxMarkAsComplete.top + 34,
                (rcGrBoxMarkAsComplete.left+rcGrBoxMarkAsComplete.right)/2+14 + w,
                rcGrBoxMarkAsComplete.top + 50);
            m_radioNone.MoveWindow(rcRadioNone);
        }
        if(m_radioPercent)
        {
            CRect rcRadioPercent;
            m_radioPercent.GetWindowRect(&rcRadioPercent);
            int w = rcRadioPercent.Width();

            rcRadioPercent.SetRect(
                (rcGrBoxMarkAsComplete.left+rcGrBoxMarkAsComplete.right)/2+14,
                rcGrBoxMarkAsComplete.top + 52,
                (rcGrBoxMarkAsComplete.left+rcGrBoxMarkAsComplete.right)/2+14 + w,
                rcGrBoxMarkAsComplete.top + 68);
            m_radioPercent.MoveWindow(rcRadioPercent);
        }
        if(m_radioFinish)
        {
            CRect rcRadioFinish;
            m_radioFinish.GetWindowRect(&rcRadioFinish);
            int w = rcRadioFinish.Width();

            rcRadioFinish.SetRect(
                (rcGrBoxMarkAsComplete.left+rcGrBoxMarkAsComplete.right)/2+14,
                rcGrBoxMarkAsComplete.top + 70,
                (rcGrBoxMarkAsComplete.left+rcGrBoxMarkAsComplete.right)/2+14 + w,
                rcGrBoxMarkAsComplete.top + 86);
            m_radioFinish.MoveWindow(rcRadioFinish);
        }

        if(m_staticMACSelectMethod)
        {
            CRect rcGrMACSelect;
            m_staticMACSelectMethod.GetWindowRect(&rcGrMACSelect);
            int w = rcGrMACSelect.Width();
            rcGrMACSelect.SetRect(
                (rcGrBoxMarkAsComplete.left+rcGrBoxMarkAsComplete.right)/2+14,
                rcGrBoxMarkAsComplete.top + 15,
                (rcGrBoxMarkAsComplete.left+rcGrBoxMarkAsComplete.right)/2+14 + w,
                rcGrBoxMarkAsComplete.top + 28);
            m_staticMACSelectMethod.MoveWindow(rcGrMACSelect);
        }

        if(m_staticMACNotificication)
        {
            CRect rcGrMACNote;
            m_staticMACNotificication.GetWindowRect(&rcGrMACNote);
            int w = rcGrMACNote.Width();
            rcGrMACNote.SetRect(
                rcGrBoxMarkAsComplete.left + 9,
                rcGrBoxMarkAsComplete.top + 29,
                (rcGrBoxMarkAsComplete.left+rcGrBoxMarkAsComplete.right)/2-14,
                rcGrBoxMarkAsComplete.top + 73);
            m_staticMACNotificication.MoveWindow(rcGrMACNote);
        }

    }

    if(m_GrBoxComment)//comment group
    {
        CRect rcGrBoxComment;
        m_GrBoxComment.GetWindowRect(&rcGrBoxComment);
        ScreenToClient(&rcGrBoxComment);
        rcGrBoxComment.bottom = rcDlg.bottom - commGrBottom;
        rcGrBoxComment.top = rcGrBoxComment.bottom	- 93;
        rcGrBoxComment.right = rcDlg.right - commGrRight;
        m_GrBoxComment.MoveWindow(rcGrBoxComment);

        if(m_editTMComment)
        {
            CRect rcEditTMComment(
                rcGrBoxComment.left + 9,
                rcGrBoxComment.top + 36,
                (rcGrBoxComment.left+rcGrBoxComment.right)/2-14,
                rcGrBoxComment.bottom - 8);
            m_editTMComment.MoveWindow(rcEditTMComment);
        }
        if(m_editPMComment)
        {
            CRect rcEditPMComment(
                (rcGrBoxComment.left+rcGrBoxComment.right)/2+14,
                rcGrBoxComment.top + 36,
                rcGrBoxComment.right-9,
                rcGrBoxComment.bottom - 8);
            m_editPMComment.MoveWindow(rcEditPMComment);
        }
        CStatic* pTMCommStatic = (CStatic*)GetDlgItem(IDC_STATIC_TM);
        if(pTMCommStatic)
        {
            CRect rcTMCommStatic(
                rcGrBoxComment.left+9,
                rcGrBoxComment.top+20,
                (rcGrBoxComment.left+rcGrBoxComment.right)/2-14,
                rcGrBoxComment.top+33);
            pTMCommStatic->MoveWindow(rcTMCommStatic);
        }
        CStatic* pPMCommStatic = (CStatic*)GetDlgItem(IDC_STATIC_PM);
        if(pPMCommStatic)
        {
            CRect rcPMCommStatic(
                (rcGrBoxComment.left+rcGrBoxComment.right)/2+14,
                rcGrBoxComment.top+20,
                rcGrBoxComment.right-9,
                rcGrBoxComment.top+33);
            pPMCommStatic->MoveWindow(rcPMCommStatic);
        }
    }





    Invalidate();
}