HWND __createWindow0(   MHND hmMonitor,LPCTSTR lpClassName,LPCTSTR lpWindowName,
                        DWORD dwStyle,int x,int y,int nWidth,
                        int nHeight,HWND hWndParent,HMENU hMenu,
                        HANDLE hInstance,LPVOID lpParam )
{
    HWND    retCode = NULL;

    if( (NULL != hmMonitor) && (NULL != lpClassName) &&
        (NULL != lpWindowName) && (NULL != hInstance) )
    {
        RECT    rRW     = {0,0,0,0};
        RECT    rRM     = {0,0,0,0};
        RECT    rSect   = {0,0,0,0};

        SetRect(&rRW,x,y,x+nWidth,y+nHeight);

        if( TRUE == _monitorBounds(hmMonitor,&rRM) )
        {
            __normaRectPos(&rRW,rRW,rRM);

            IntersectRect(&rSect,&rRM,&rRW);

            if( TRUE == EqualRect(&rSect,&rRW) )
            {
                x = rSect.left;
                y = rSect.top;
                nWidth = rSect.right - rSect.left;
                nHeight = rSect.bottom - rSect.top;
                retCode = CreateWindow(
                                            lpClassName,lpWindowName,
                                            dwStyle,x,y,nWidth,
                                            nHeight,hWndParent,hMenu,
                                            (HINSTANCE)hInstance,lpParam
                                        );
            } else  {
                    //  A coisa indefinida. Nao tenho sabdoria o que
                    //  fazer aqui mesmo
                    //  E necessario perguntar Jeannette
                    }
        }
    }

    return retCode;
}