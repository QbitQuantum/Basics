BOOL CVFPUDlg::DlgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_INITDIALOG:
    {
        return TRUE;
    }
    break;
    case WM_COMMAND:
    {
//			CtrlMemView *mv = CtrlMemView::getFrom(GetDlgItem(m_hDlg,IDC_MEMVIEW));
        //switch (LOWORD(wParam))
        //{
        //}
    }
    break;

    case WM_NOTIFY:
    {
        HWND tabs = GetDlgItem(m_hDlg, IDC_TABDATATYPE);
        NMHDR* pNotifyMessage = NULL;
        pNotifyMessage = (LPNMHDR)lParam;
        if (pNotifyMessage->hwndFrom == tabs)
        {
            mode = TabCtrl_GetCurSel (tabs);
            InvalidateRect(m_hDlg,0,0);
        }
        break;
    }

    case WM_SIZE:
        Size();
        break;

    case WM_PAINT:
    {
        HWND wnd = m_hDlg;
        RECT rect;
        GetClientRect(wnd, &rect);
        PAINTSTRUCT p;
        HDC hdc = BeginPaint(wnd, &p);
        SetBkMode(hdc, TRANSPARENT);
        DWORD bgColor = 0xffffff;
        HPEN nullPen=CreatePen(0,0,bgColor);
        HPEN currentPen=CreatePen(0,0,0);
        HPEN selPen=CreatePen(0,0,0x808080);
        LOGBRUSH lbr;
        lbr.lbHatch=0;
        lbr.lbStyle=0;
        lbr.lbColor=bgColor;
        HBRUSH nullBrush=CreateBrushIndirect(&lbr);
        lbr.lbColor=0xFFEfE8;
        HBRUSH currentBrush=CreateBrushIndirect(&lbr);
        lbr.lbColor=0x70FF70;
        HBRUSH pcBrush=CreateBrushIndirect(&lbr);
        HPEN oldPen=(HPEN)SelectObject(hdc,currentPen);
        HBRUSH oldBrush=(HBRUSH)SelectObject(hdc,nullBrush);
        HFONT oldFont = (HFONT)SelectObject(hdc,(HGDIOBJ)font);

        enum
        {
            rowHeight = 15,
            columnWidth = 80,
            xStart = columnWidth/2,
            yStart = 30,
        };

        for (int matrix = 0; matrix<8; matrix++)
        {
            int my = (int)(yStart + matrix * rowHeight * 5.5f);
            Rectangle(hdc, 0, my, xStart, my+rowHeight);
            char temp[256];
            sprintf_s(temp, "M%i00", matrix);
            TextOut(hdc,3,my+2,temp,strlen(temp));
            Rectangle(hdc,xStart,my+rowHeight,xStart+columnWidth*4,my+5*rowHeight);

            for (int column = 0; column<4; column++)
            {
                int y = my;
                int x = column * columnWidth + xStart;

                Rectangle(hdc, x, y, x + columnWidth, y+rowHeight);
                char temp[256];
                sprintf_s(temp, "R%i0%i", matrix, column);
                TextOut(hdc,x+3,y+2,temp,strlen(temp));

                Rectangle(hdc, 0, y+rowHeight*(column+1), xStart, y+rowHeight*(column+2));
                sprintf_s(temp, "C%i%i0", matrix, column);
                TextOut(hdc,3,y+rowHeight*(column+1)+1,temp,strlen(temp));

                y+=rowHeight;

                for (int row = 0; row<4; row++)
                {
                    float val = mipsr4k.v[column*32+row+matrix*4];
                    u32 hex = *((u32*)&val);
                    char temp[256];
                    switch (mode)
                    {
                    case 0:
                        sprintf_s(temp,"%f",val);
                        break;
//						case 1: sprintf_s(temp,"??"); break;
                    case 2:
                        sprintf_s(temp,"0x%08x",hex);
                        break;
                    default:
                        sprintf_s(temp,"%f",val);
                        break;
                    }

                    TextOut(hdc,x+3,y+2,temp,strlen(temp));
                    y+=rowHeight;
                }
            }
        }

        SelectObject(hdc,oldFont);
        SelectObject(hdc,oldPen);
        SelectObject(hdc,oldBrush);

        DeleteObject(nullPen);
        DeleteObject(currentPen);
        DeleteObject(selPen);

        DeleteObject(nullBrush);
        DeleteObject(pcBrush);
        DeleteObject(currentBrush);

        EndPaint(m_hDlg, &p);
    }
    break;

    case WM_CLOSE:
        Show(false);
        break;
    }

    return 0;
}