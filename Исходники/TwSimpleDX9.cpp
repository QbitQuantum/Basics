// Main
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int cmdShow)
{
    // Register our window class
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_CLASSDC|CS_DBLCLKS, MessageProc, 0L, 0L, 
                        instance, NULL, NULL, NULL, NULL, "TwDX9", NULL };
    RegisterClassEx(&wcex);

    // Create a window
    const int W = 640;
    const int H = 480;
    BOOL fullscreen = FALSE; // Set to TRUE to run in fullscreen
    RECT rect = { 0, 0, W, H };
    DWORD style = fullscreen ? WS_POPUP : WS_OVERLAPPEDWINDOW;
    AdjustWindowRect(&rect, style, FALSE);
    HWND wnd = CreateWindow("TwDX9", "AntTweakBar simple example using DirectX9", 
                            style, CW_USEDEFAULT, CW_USEDEFAULT, 
                            rect.right-rect.left, rect.bottom-rect.top, NULL, NULL, instance, NULL);
    if( !wnd )
    {
        MessageBox(NULL, "Cannot create window", "Error", MB_OK|MB_ICONERROR);
        return FALSE;
    }
    ShowWindow(wnd, cmdShow);
    UpdateWindow(wnd);

    // Initialize Direct3D
    g_D3D = Direct3DCreate9(D3D_SDK_VERSION);
    if( !g_D3D )
    {
        MessageBox(wnd, "Cannot initialize DirectX", "Error", MB_OK|MB_ICONERROR);
        return FALSE;
    }

    // Create a Direct3D device
    ZeroMemory( &g_D3Dpp, sizeof(D3DPRESENT_PARAMETERS) );
    g_D3Dpp.Windowed = !fullscreen;
    if( fullscreen )
    {
        g_D3Dpp.BackBufferWidth = W;
        g_D3Dpp.BackBufferHeight = H;
    }
    g_D3Dpp.BackBufferCount = 1;
    g_D3Dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
    if( fullscreen )
        g_D3Dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    else
        g_D3Dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_D3Dpp.hDeviceWindow = wnd;

    g_D3Dpp.EnableAutoDepthStencil = TRUE;
    g_D3Dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_D3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    HRESULT hr = g_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, wnd, 
                                     D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_D3Dpp, &g_D3DDev);
    if( FAILED(hr) )
    {
        //DXTRACE_ERR_MSGBOX("Cannot create DirectX device", hr);
        MessageBox(wnd, "Cannot create DirectX device", "Error", MB_OK|MB_ICONERROR);
        g_D3D->Release();
        g_D3D = NULL;
        return FALSE;
    }

    // This example draws a moving strip;
    // create a buffer of vertices for the strip
    struct Vertex
    {
        float x, y, z;
        DWORD color;
    };
    Vertex vertices[2002];
    int numSec = 100;            // number of strip sections
    float color[] = { 1, 0, 0 }; // strip color
    unsigned int bgColor = D3DCOLOR_ARGB(255, 128, 196, 196); // background color

    // Init some D3D states
    InitD3D();

    // Initialize AntTweakBar
    // (note that the Direct3D device pointer must be passed to TwInit)
    if( !TwInit(TW_DIRECT3D9, g_D3DDev) )
    {
        MessageBox(wnd, TwGetLastError(), "Cannot initialize AntTweakBar", MB_OK|MB_ICONERROR);
        g_D3DDev->Release();
        g_D3DDev = NULL;
        g_D3D->Release();
        g_D3D = NULL;
        return FALSE;
    }

    
    // Create a tweak bar
    TwBar *bar = TwNewBar("TweakBar");
    TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar in a DirectX9 application.' "); // Message added to the help bar.
    TwDefine(" TweakBar color='128 224 160' text=dark "); // Change TweakBar color and use dark text

    // Add 'numSec' to 'bar': it is a modifiable (RW) variable of type TW_TYPE_INT32. Its shortcuts are [s] and [S].
    TwAddVarRW(bar, "NumSec", TW_TYPE_INT32, &numSec, 
               " label='Strip length' min=1 max=1000 keyIncr=s keyDecr=S help='Number of segments of the strip.' ");

    // Add 'color' to 'bar': it is a modifiable variable of type TW_TYPE_COLOR3F (3 floats color)
    TwAddVarRW(bar, "Color", TW_TYPE_COLOR3F, &color, " label='Strip color' ");

    // Add 'bgColor' to 'bar': it is a modifiable variable of type TW_TYPE_COLOR32 (32 bits color)
    TwAddVarRW(bar, "BgColor", TW_TYPE_COLOR32, &bgColor, " label='Background color' ");

    // Add 'width' and 'height' to 'bar': they are read-only (RO) variables of type TW_TYPE_INT32.
    TwAddVarRO(bar, "Width", TW_TYPE_INT32, &g_D3Dpp.BackBufferWidth, 
               " label='wnd width' help='Current graphics window width.' ");
    TwAddVarRO(bar, "Height", TW_TYPE_INT32, &g_D3Dpp.BackBufferHeight, 
               " label='wnd height' help='Current graphics window height.' ");


    // Main loop
    bool quit = false;
    while( !quit )
    {
        // Clear screen and begin draw
        g_D3DDev->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, bgColor, 1.0f, 0);
        g_D3DDev->BeginScene();

        // Draw scene
        float s, t = (float)GetTickCount()/1000.0f;
        for( int i=0; i<=numSec; ++i )  // update vertices
        {
            s = (float)i/100;
            vertices[2*i+0].x = 0.05f+0.7f*cosf(2.0f*s+5.0f*t);
            vertices[2*i+1].x = vertices[2*i+0].x + (0.25f+0.1f*cosf(s+t));
            vertices[2*i+0].y = vertices[2*i+1].y = 0.7f*(0.7f+0.3f*sinf(s+t))*sinf(1.5f*s+3.0f*t);
            vertices[2*i+0].z = vertices[2*i+1].z = 0;
            s = (float)i/numSec;
            vertices[2*i+0].color = vertices[2*i+1].color = 
                D3DCOLOR_XRGB((int)(255*color[0]*s), (int)(255*color[1]*s), (int)(255*color[2]*s));
        }
        g_D3DDev->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
        g_D3DDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2*numSec, vertices, sizeof(Vertex)); // draw strip
 
        // Draw tweak bars
        TwDraw();

        // End draw
        g_D3DDev->EndScene();

        // Present frame buffer
        g_D3DDev->Present(NULL, NULL, NULL, NULL);

        // Process windows messages
        MSG msg;
        while( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
        {
            if( msg.message==WM_QUIT )
                quit = true;
            else if( !TranslateAccelerator(msg.hwnd, NULL, &msg) ) 
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    } // End of main loop


    // Terminate AntTweakBar
    TwTerminate();

    // Release Direct3D
    g_D3DDev->Release();
    g_D3DDev = NULL;
    g_D3D->Release();
    g_D3D = NULL;

    return 0;
}