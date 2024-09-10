LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) {
  struct WindowData *data=window_data();

  // WindowHandle handle = (WindowHandle)GetWindowLong(hWnd,GWL_USERDATA);

  if(!data->created) {
    return DefWindowProc(hWnd,message,wParam,lParam);
  } else if(message==WM_INPUT) {
    // UINT dwSize = 40;
    // static BYTE lpb[40];
    // GetRawInputData((HRAWINPUT)lParam,RID_INPUT,lpb,&dwSize,sizeof(RAWINPUTHEADER));
    // RAWINPUT* raw = (RAWINPUT*)lpb;

    RAWINPUT raw;
    UINT DataSize = sizeof(RAWINPUT);
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &raw, &DataSize, sizeof(RAWINPUTHEADER));

    if(raw.header.dwType == RIM_TYPEMOUSE) {
      if(raw.data.mouse.usButtonFlags & RI_MOUSE_WHEEL) {
        data->mouseZ=(int)raw.data.mouse.usButtonData;
      } else if(raw.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN) {
        data->inputs[WINDOW_MOUSE_LEFT]=WINDOW_INPUT_PRESS;
      } else if(raw.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP &&
                data->inputs[WINDOW_MOUSE_LEFT]!=WINDOW_INPUT_UP) {
        data->inputs[WINDOW_MOUSE_LEFT]=WINDOW_INPUT_RELEASE;
      } else if(raw.data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN) {
        data->inputs[WINDOW_MOUSE_RIGHT]=WINDOW_INPUT_PRESS;
      } else if(raw.data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP &&
                data->inputs[WINDOW_MOUSE_RIGHT]!=WINDOW_INPUT_UP) {
        data->inputs[WINDOW_MOUSE_RIGHT]=WINDOW_INPUT_RELEASE;
      } else if(raw.data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN) {
        data->inputs[WINDOW_MOUSE_MIDDLE]=WINDOW_INPUT_PRESS;
      } else if(raw.data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP &&
                data->inputs[WINDOW_MOUSE_MIDDLE]!=WINDOW_INPUT_UP) {
        data->inputs[WINDOW_MOUSE_MIDDLE]=WINDOW_INPUT_RELEASE;
      }

      data->mouseX=(int)raw.data.mouse.lLastX;
      data->mouseY=(int)raw.data.mouse.lLastY;
    } else if(raw.header.dwType == RIM_TYPEKEYBOARD) {
      USHORT vk=raw.data.keyboard.VKey;
      USHORT up=raw.data.keyboard.Flags & RI_KEY_BREAK;
      USHORT right=raw.data.keyboard.Flags & RI_KEY_E0;

      if(up && data->inputs[window_key_convert(vk)]!=WINDOW_INPUT_UP) {
        data->inputs[window_key_convert(vk)]=WINDOW_INPUT_RELEASE;
      }else if(!up) {
        data->inputs[window_key_convert(vk)]=WINDOW_INPUT_PRESS;
      }
    }
  } else if(message==WM_DESTROY) {
    PostQuitMessage(0);
    return 0;
  } else if(message==WM_SIZE) {
    //data->clientWidth=(int)LOWORD(lParam);
    //data->clientHeight=(int)HIWORD(lParam);
    data->sized=true;
    data->iconified=(wParam==SIZE_MINIMIZED);
  } else if(message==WM_KILLFOCUS) {
    data->focused=false;
  } else if(message==WM_SETFOCUS) {
    data->focused=true;
  } else {
    return DefWindowProc(hWnd,message,wParam,lParam);
  }

  return 0;
}