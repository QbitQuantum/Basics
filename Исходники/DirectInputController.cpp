bool DirectInputController::Init(HINSTANCE hInstance, HWND hWnd) {
  HRESULT hr = S_OK;

  if (!_directInput) {
    hr = DirectInput8Create(hInstance,
                            DIRECTINPUT_VERSION, // Compatible version.
                            IID_IDirectInput8,   // DirectInput interface version.
                            (LPVOID*)&_directInput,
                            NULL);
    if (FAILED(hr)) {
      LOGE("Fatal error in DirectInputController::InitDirectInput, DirectInput8Create failed");
      return false;
    }
  }

  // Create mouse device.
  if (!_mouseDevice) {
    hr = _directInput->CreateDevice(GUID_SysMouse, &_mouseDevice, NULL);
    if (FAILED(hr)) {
      LOGE("Fatal error in DirectInputController::InitDirectInput, _directInput->CreateDevice (GUID_SysMouse) failed");
      return false;
    }

    hr = _mouseDevice->SetDataFormat(&c_dfDIMouse2); 
    if (FAILED(hr)) {
      LOGE("Fatal error in DirectInputController::InitDirectInput, _mouseDevice->SetDataFormat failed");
      return false;
    }

    hr = _mouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND); 
    if (FAILED(hr)) {
      LOGE("Fatal error in DirectInputController::InitDirectInput, _mouseDevice->SetCooperativeLevel failed");
      return false;
    }

    _mouseDevice->Acquire();
  }

  // Create keyboard device.
  if (!_keyboardDevice) {
    hr = _directInput->CreateDevice(GUID_SysKeyboard, &_keyboardDevice, NULL);
    if (FAILED(hr)) {
      LOGE("Fatal error in DirectInputController::InitDirectInput, _directInput->CreateDevice (GUID_SysKeyboard) failed");
      return false;
    }

    hr = _keyboardDevice->SetDataFormat(&c_dfDIKeyboard); 
    if (FAILED(hr)) {
      LOGE("Fatal error in DirectInputController::InitDirectInput, _keyboardDevice->SetDataFormat failed");
      return false;
    }

    hr = _keyboardDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND); 
    if (FAILED(hr)) {
      LOGE("Fatal error in DirectInputController::InitDirectInput, _keyboardDevice->SetCooperativeLevel failed");
      return false;
    }

    _keyboardDevice->Acquire();
  }

  return SUCCEEDED(hr);
}