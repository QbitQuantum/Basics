bool KINWM::Create(const std::wstring& p_Caption,
                   const Common::KINRect p_Rect,
                   const unsigned int p_BackColor,
                   const unsigned int p_WindowStyle,
                   const WNDPROC p_MessageFunction)
{
    mhInstance = GetModuleHandle(NULL);

    WNDCLASSW WndClass;
    WndClass.style			= CS_CLASSDC;
    WndClass.lpfnWndProc	= (WNDPROC)p_MessageFunction;
    WndClass.cbClsExtra		= 0;
    WndClass.cbWndExtra		= 0;
    WndClass.hInstance		= mhInstance;
    WndClass.hIcon			= LoadIcon (NULL, IDI_APPLICATION);
    WndClass.hCursor		= LoadCursor (NULL, IDC_ARROW);
    WndClass.hbrBackground	= 0;
    WndClass.lpszMenuName	= NULL;
    WndClass.lpszClassName	= p_Caption.c_str();
    RegisterClassW(&WndClass);

    mhWnd = CreateWindowW(p_Caption.c_str(), p_Caption.c_str(), p_WindowStyle,
                          p_Rect.mX, p_Rect.mY, p_Rect.mWidth, p_Rect.mHeight,
                          NULL, NULL, GetModuleHandle(NULL), NULL);

    if(mhWnd == NULL)
    {
        printf("KINWM::Create 실패 - mhWnd가 NULL 입니다.\n");
    }

    SetToClient(Common::KINSize(p_Rect.mWidth, p_Rect.mHeight));

    ShowWindow();

    return true;
}