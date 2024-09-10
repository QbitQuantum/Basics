LRESULT KItemNull::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    float const fX = (float)(GET_X_LPARAM(lParam));
    float const fY = (float)(GET_Y_LPARAM(lParam));
    switch (uMsg)
    {
    case WM_LBUTTONDOWN:
        if (PtInItem(fX, fY))
        {
            if (KDebugConfig::ms_aBoolFlag[KDebugConfig::BOOL_SELECT_WINDOW_IN_CLIENT])
				g_pUI->m_EditorMgr.UIEditorOperation(PLUGIN_UI_EDITOR_SEL_WND, (WPARAM)m_szItemName, 0);

            if (KDebugConfig::ms_aBoolFlag[KDebugConfig::BOOL_RESIZE_WND_AND_ITEM_MODE] &&
                (fX > m_fAbsX + m_fWidth - 2 * KDebugConfig::ms_nResizeWindowHandleNodeHalfSize) &&
                (fY > m_fAbsY + m_fHeight - 2 * KDebugConfig::ms_nResizeWindowHandleNodeHalfSize))
            {
                KItemEditModeMgr::GetSelf().SetEditMode(EDIT_RESIZE_MODE);
            }
            else
            {
                KItemEditModeMgr::GetSelf().SetEditMode(EDIT_DRAG_MODE);
            }
            KItemEditModeMgr::GetSelf().SetCurrentEditItem(this);
            KItemEditModeMgr::GetSelf().SetDragStartPos(fX, fY);
            return TRUE;
        }
        break;
    case WM_MOUSEMOVE:
        if (wParam & MK_LBUTTON)
        {
            float fLastX;
            float fLastY;
            KItemEditModeMgr::GetSelf().GetFragStartPos(fLastX, fLastY);
            if (KItemEditModeMgr::GetSelf().GetEditMode() == EDIT_DRAG_MODE)
                AbsMove(fX - fLastX, fY - fLastY);
            else if (KItemEditModeMgr::GetSelf().GetEditMode() == EDIT_RESIZE_MODE)
            {
                float fWidth = m_fWidth + (fX - fLastX);
                float fHeight = m_fHeight + (fY - fLastY);
                if (fWidth < 0.0f)
                    fWidth = 0.0f;
                if (fHeight < 0.0f)
                    fHeight = 0.0f;
                SetSize(fWidth, fHeight);
            }
            KItemEditModeMgr::GetSelf().SetDragStartPos(fX, fY);
            return TRUE;
        }
		else if (PtInItem(fX, fY))
		{
			static char szInfo[MAX_PATH] = { 0 };
			_snprintf(szInfo, _countof(szInfo), "名字: %s\n   x=%d, y=%d, w=%d, h=%d\n", m_szItemName, 
				(int)m_fRelX, (int)m_fRelY, (int)m_fWidth, (int)m_fHeight);
			g_pUI->m_EditorMgr.UIEditorOperation(PLUGIN_UI_EDITOR_SHOW_INFO, (WPARAM)szInfo, 0);
			return TRUE;
		}
        break;
    }
    
    return FALSE;
}