LRESULT AeroControlBase::SubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uidSubclass, DWORD_PTR dwRefData)
{
    AeroControlBase * pThis = (AeroControlBase*)dwRefData;
    if (pThis)
    {
        HIGHCONTRAST hc = { sizeof(HIGHCONTRAST) };
        SystemParametersInfo(SPI_GETHIGHCONTRAST, sizeof(HIGHCONTRAST), &hc, FALSE);
        BOOL bEnabled = FALSE;
        if (((hc.dwFlags & HCF_HIGHCONTRASTON) == 0) && SUCCEEDED(DwmIsCompositionEnabled(&bEnabled)) && bEnabled)
        {
            switch (uidSubclass)
            {
            case Static:
                return pThis->StaticWindowProc(hWnd, uMsg, wParam, lParam);
                break;
            case Button:
                return pThis->ButtonWindowProc(hWnd, uMsg, wParam, lParam);
                break;
            case Progressbar:
                return pThis->ProgressbarWindowProc(hWnd, uMsg, wParam, lParam);
                break;
            }
        }
    }

    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}