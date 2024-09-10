static HRESULT WINAPI ActiveIMMApp_GetImeMenuItemsW(IActiveIMMApp* This,
        HIMC hIMC, DWORD dwFlags, DWORD dwType,
        IMEMENUITEMINFOW *pImeParentMenu, IMEMENUITEMINFOW *pImeMenu,
        DWORD dwSize, DWORD *pdwResult)
{
    *pdwResult = ImmGetImeMenuItemsW(hIMC,dwFlags,dwType,pImeParentMenu,pImeMenu,dwSize);
    return S_OK;
}