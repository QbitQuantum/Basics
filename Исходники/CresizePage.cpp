HRESULT TresizePage::msgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_SHOWWINDOW:
        if (wParam) cfg2dlg();
        break;

    case WM_HSCROLL:
        if (HWND(lParam)==GetDlgItem(m_hwnd,IDC_TBR_ASPECT_USER))
        {
            int a=SendDlgItemMessage(m_hwnd,IDC_TBR_ASPECT_USER,TBM_GETPOS,0,0);
            cfgSet(IDFF_aspectRatio,a*256);
            aspect2dlg();
            return TRUE;
        }
        else if (HWND(lParam)==GetDlgItem(m_hwnd,IDC_TBR_RESIZE_GBLUR_LUM))
        {
            cfgSet(IDFF_resizeGblurLum,SendDlgItemMessage(m_hwnd,IDC_TBR_RESIZE_GBLUR_LUM,TBM_GETPOS,0,0));
            resize2dlg();
            return TRUE;
        }
        else if (HWND(lParam)==GetDlgItem(m_hwnd,IDC_TBR_RESIZE_GBLUR_CHROM))
        {
            cfgSet(IDFF_resizeGblurChrom,SendDlgItemMessage(m_hwnd,IDC_TBR_RESIZE_GBLUR_CHROM,TBM_GETPOS,0,0));
            resize2dlg();
            return TRUE;
        }
        else if (HWND(lParam)==GetDlgItem(m_hwnd,IDC_TBR_RESIZE_SHARPEN_LUM))
        {
            cfgSet(IDFF_resizeSharpenLum,SendDlgItemMessage(m_hwnd,IDC_TBR_RESIZE_SHARPEN_LUM,TBM_GETPOS,0,0));
            resize2dlg();
            return TRUE;
        }
        else if (HWND(lParam)==GetDlgItem(m_hwnd,IDC_TBR_RESIZE_SHARPEN_CHROM))
        {
            cfgSet(IDFF_resizeSharpenChrom,SendDlgItemMessage(m_hwnd,IDC_TBR_RESIZE_SHARPEN_CHROM,TBM_GETPOS,0,0));
            resize2dlg();
            return TRUE;
        }
        else break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_CHB_RESIZE:
            cfgSet(IDFF_isResize,getCheck(IDC_CHB_RESIZE));
            return TRUE;

        case IDC_CHB_RESIZE_FIRST:
            cfgSet(IDFF_resizeFirst,getCheck(IDC_CHB_RESIZE_FIRST));
            return TRUE;
        case IDC_CBX_RESIZE_METHOD:
            if (HIWORD(wParam)==CBN_SELCHANGE)
            {
                int i=SendDlgItemMessage(m_hwnd,IDC_CBX_RESIZE_METHOD,CB_GETCURSEL,0,0);
                cfgSet(IDFF_resizeMethod,i);
                return TRUE;
            }
            break;
        case IDC_RBT_ASPECT_NO:
            cfgSet(IDFF_resizeAspect,0);
            aspect2dlg();
            return TRUE;
        case IDC_RBT_ASPECT_KEEP:
            cfgSet(IDFF_resizeAspect,1);
            aspect2dlg();
            return TRUE;
        case IDC_RBT_ASPECT_USER:
            cfgSet(IDFF_resizeAspect,2);
            aspect2dlg();
            return TRUE;

        case IDC_ED_RESIZEDX:
        case IDC_ED_RESIZEDY:
            if (HIWORD(wParam)==EN_CHANGE)
            {
                enableWindow(IDC_BT_RESIZE_SET,applyResizeXY(true));
                return TRUE;
            };
            break;
        case IDC_BT_RESIZE_SET:
            applyResizeXY(false);
            return TRUE;
        };
        break;
    };
    return FALSE;
};