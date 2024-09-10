/// <summary>
/// Create window of viewer
/// </sumarry>
/// <returns>Indicates success or failure</returns>
bool NuiViewer::CreateView()
{
    if (!m_hWnd)
    {
        HWND hWndParent = nullptr;
        if (m_pParent)
        {
            hWndParent = m_pParent->GetWindow();
        }

        m_hWnd = CreateDialogParamW(nullptr,
                                    MAKEINTRESOURCE(GetDlgId()),
                                    hWndParent,
                                    (DLGPROC)MessageRouter,
                                    reinterpret_cast<LPARAM>(this));
    }

    return (nullptr != m_hWnd);
}