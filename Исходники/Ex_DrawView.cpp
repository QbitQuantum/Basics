void CEx_DrawView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
    CEx_DrawDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    
    m_bContextMenu = TRUE;

    if (pDoc->m_GM.m_DrawType == SELECT)
    {
        CPoint pt;
        GetCursorPos(&pt);
        ScreenToClient(&pt);
        pt += m_ptLocalScroll;
        BOOL bResult = FALSE;
        GraphicHitTest(pt, bResult, m_iTrackID);
        
        if (bResult && pDoc->m_sel == m_iTrackID && m_iTrackID != -1)
        {          
            CGraphic* P = Convert_To_Graphic(pDoc->m_obArray[m_iTrackID]);
            CRect rt;
            P->GetRect(rt);
            GraphicMember GM;
            P->UpdateData(&GM, FALSE);
            CMenu menu;
            CString title;
            GetCursorPos(&pt);
            menu.CreatePopupMenu();
            
            menu.AppendMenu(MF_STRING, 0x80, _T("----===== 画布信息 =====----"));
            title.Format(_T("图布大小： %dx%d"), m_size.cx, m_size.cy);
            menu.AppendMenu(MF_STRING, 0x81, title);
            
            menu.AppendMenu(MF_STRING, 0x200, _T("----===== 操作命令 =====----"));
            menu.AppendMenu(MF_STRING | MF_BYCOMMAND, 0x201, _T("编辑当前图形"));
            menu.AppendMenu(MF_STRING | MF_BYCOMMAND, 0x202, _T("删除当前图形"));
            
            menu.AppendMenu(MF_STRING, 0x100, _T("----===== 图形信息 =====----"));
            title.Format(_T("自定义名称： %s"), GM.m_lpszName);
            menu.AppendMenu(MF_STRING, 0x106, title);
            title.Format(_T("图像类型： %s"), P->GetName());
            menu.AppendMenu(MF_STRING, 0x101, title);
            title.Format(_T("存放序号： %d"), m_iTrackID);
            menu.AppendMenu(MF_STRING, 0x102, title);
            title.Format(_T("节点数量： %d"), P->GetPts());
            menu.AppendMenu(MF_STRING, 0x103, title);
            title.Format(_T("图像大小： %dx%d"), rt.Width(), rt.Height());
            menu.AppendMenu(MF_STRING, 0x104, title);
            title.Format(_T("是否隐藏： %s"), GM.m_bHidden ? _T("是") : _T("否"));
            menu.AppendMenu(MF_STRING, 0x107, title);
            title.Format(_T("逻辑坐标： (%d, %d, %d, %d)"), rt.left, rt.top, rt.right, rt.bottom);
            menu.AppendMenu(MF_STRING, 0x105, title);
            
            menu.AppendMenu(MF_SEPARATOR);
            
            title.Format(_T("创建时间： %s"), GM.m_createTime.Format("%c"));
            menu.AppendMenu(MF_STRING, 0x300, title);
            title.Format(_T("修改时间： %s"), GM.m_modifiedTime.Format("%c"));
            menu.AppendMenu(MF_STRING, 0x301, title);
            
            menu.AppendMenu(MF_SEPARATOR);
            
            title.Format(_T("画笔类型： %s"), CGraphic::GetPenStyleById(GM.m_iPenStyle, FALSE));
            menu.AppendMenu(MF_STRING, 0x125, title);
            
            if (!IF_NULL_PEN(GM.m_iPenStyle))
            {
                title.Format(_T("画笔颜色： RGB(%d, %d, %d)"), GetRValue(GM.m_clrPen), GetGValue(GM.m_clrPen), GetBValue(GM.m_clrPen));
                menu.AppendMenu(MF_STRING, 0x120, title);
                title.Format(_T("画笔粗细： %d"), GM.m_iPenWidth);
                menu.AppendMenu(MF_STRING, 0x122, title);
            }
            
            menu.AppendMenu(MF_SEPARATOR);
            
            if (P->EnableBrush())
            {
                title.Format(_T("画笔类型： %s"), CGraphic::GetBrushStyleById(GM.m_iBrushStyle, FALSE));
                menu.AppendMenu(MF_STRING, 0x400, title);
                if (!IF_NULL_BRUSH(GM.m_iBrushStyle))
                {
                    title.Format(_T("画刷颜色： RGB(%d, %d, %d)"), GetRValue(GM.m_clrBrush), GetGValue(GM.m_clrBrush), GetBValue(GM.m_clrBrush));
                    menu.AppendMenu(MF_STRING, 0x401, title);
                }
            }
            
            menu.TrackPopupMenu(0, pt.x, pt.y, this);
        }
    }
    else
    {
        pDoc->m_GM.m_DrawType = SELECT;
        pDoc->UpdateAllViews(NULL, 0x2000);
    }
}