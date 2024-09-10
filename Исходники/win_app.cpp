void AppState::initInputDevices() {
    //创建DirectInput8对象
    IDirectInput8A* direct_input;
    dx::throwIfFailed(
        DirectInput8Create(
            hInstance_,
            DIRECTINPUT_VERSION,
            IID_IDirectInput8,
            (void **) &direct_input,
            nullptr)
    );
    direct_input_.reset(direct_input);


    //创建DirectInput8设备（键盘）
    IDirectInputDevice8A* keyboard_device;
    dx::throwIfFailed(
        direct_input_->CreateDevice(GUID_SysKeyboard, &keyboard_device, nullptr)
    );
    keyboard_device_.reset(keyboard_device);


    //为键盘设置格式
    dx::throwIfFailed(
        keyboard_device_->SetDataFormat(&c_dfDIKeyboard)
    );


    //为键盘设置行为
    dx::throwIfFailed(
        keyboard_device_->SetCooperativeLevel(windowHwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)
    );

    //为键盘设置缓冲方式
    DIPROPDWORD dipdw;
    dipdw.diph.dwSize = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj = 0;
    dipdw.diph.dwHow = DIPH_DEVICE;
    dipdw.dwData = kKeyInputBufferSize; // Arbitary buffer size

    dx::throwIfFailed(
        keyboard_device_->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph)
    );

    //创建事件，为自动型（使用完自动置为无信号状态），初始化为无信号状态
    HANDLE handle = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (!handle) {
        throw std::runtime_error("CreateEvent keyboard error!");
    }

    //为键盘安装事件通知关联，并准备获取采集
    keyboard_device_->SetEventNotification(handle);
    keyboard_device_->Acquire();

    //添加等待对象,以及触发事件
    addEventHandle(handle, std::bind(&AppState::updateKeyInputState, this));

    //创建DirectInput8设备（鼠标）
    IDirectInputDevice8A* mouse_device;
    dx::throwIfFailed(
        direct_input_->CreateDevice(GUID_SysMouse, &mouse_device, NULL)
    );
    mouse_device_.reset(mouse_device);


    //为鼠标设置格式(8按键鼠标)
    dx::throwIfFailed(
        mouse_device_->SetDataFormat(&c_dfDIMouse2)
    );


    //为鼠标设置行为
    dx::throwIfFailed(
        mouse_device_->SetCooperativeLevel(windowHwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)
    );


    //鼠标设置缓冲方式
    dipdw.diph.dwSize = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj = 0;
    dipdw.diph.dwHow = DIPH_DEVICE;
    dipdw.dwData = kMouseInputBufferSize;

    dx::throwIfFailed(
        mouse_device_->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph)
    );

    handle = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (!handle) {
        throw std::runtime_error("CreateEvent mouse error!");
    }

    mouse_device_->SetEventNotification(handle);
    mouse_device_->Acquire();

    addEventHandle(handle, std::bind(&AppState::updateMouseInputState, this));

    /*
     _pD3D = Direct3DCreate9(D3D_SDK_VERSION);
     if(_pD3D == nullptr)
     {
     BOOST_THROW_EXCEPTION(std::runtime_error("Direct3DCreate9 error!"));
     }

     D3DPRESENT_PARAMETERS d3dpp;
     ZeroMemory( &d3dpp, sizeof( d3dpp ) );
     d3dpp.Windowed = TRUE; //不是全屏
     d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
     d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

     hr = _pD3D->CreateDevice(
     D3DADAPTER_DEFAULT,
     D3DDEVTYPE_HAL,
     WindowHwnd,
     D3DCREATE_SOFTWARE_VERTEXPROCESSING,
     &d3dpp,
     &_pd3dDevice);

     if (FAILED(hr)) {
     BOOST_THROW_EXCEPTION(std::runtime_error("CreateDevice IDirect3DDevice9 error!"));
     }

     IDirect3DSurface8* lpDSCursor;
     hr = _pd3dDevice->CreateImageSurface(32, 32, D3DFMT_A8R8G8B8,&lpDSCursor);
     */

}