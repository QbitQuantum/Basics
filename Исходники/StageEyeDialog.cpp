void CStageEyeDialog::OnKillfocusEyeToy()
{
    // TODO: Add your control notification handler code here
    CMainFrame *pMainFrame = (CMainFrame *)GetTopLevelFrame();
    if (!pMainFrame || !pMainFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
    {
        return;
    }
    CStageView *pView = (CStageView *)pMainFrame->GetActiveView();
    if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CStageView)))
    {
        return;
    }
    CStageDoc *pDoc = pView->GetDocument();
    if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CStageDoc)))
    {
        return;
    }
    CWnd *pCBox;
    char s[32];
    GLdouble toY;
    RECT rect;

    pMainFrame->GetWindowRect(&rect);
    if (rect.right - rect.left < YO_THRESH_WIDTH || pMainFrame->m_wndDlgEyeVisible == FALSE
            || pMainFrame->m_wndDlgEye == NULL)
    {
        return;
    }

    pCBox = (CComboBox*)pMainFrame->m_wndDlgEye->GetDlgItem(IDC_EYE_TOY);
    pCBox->GetWindowText(s, 32);
    sscanf(s, "%lf", &toY);
    pView->m_eye[4] = toY / pDoc->m_unitScaleFactor;

    ::glMatrixMode(GL_MODELVIEW);
    ::glLoadIdentity();
    ::gluLookAt(pView->m_eye[0], pView->m_eye[1], pView->m_eye[2],
                pView->m_eye[3], pView->m_eye[4], pView->m_eye[5],
                pView->m_eye[6], pView->m_eye[7], pView->m_eye[8]);

    pView->YoRender(YO_RENDER_LIGHT);
    pView->YoRender(YO_RENDER_FULL);
    return;
}