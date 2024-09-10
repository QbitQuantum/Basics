/*
 * thanks to this article http://www.rohitab.com/discuss/topic/35415-c-getrawinputdata-keylogger/
 */
LRESULT CALLBACK raw_input_device_handler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    UINT dwSize;
    RAWINPUTDEVICE ridMouse;
    RAWINPUT *buffer;
     
    switch(msg)
    {
        case WM_CREATE:
            // Register a raw input devices to capture input
			
            ridMouse.usUsagePage = 0x01;
            ridMouse.usUsage = 0x02;
            ridMouse.dwFlags = RIDEV_INPUTSINK;
            ridMouse.hwndTarget = hwnd;
             
            if(!RegisterRawInputDevices(&ridMouse, 1, sizeof(RAWINPUTDEVICE)))
            {
                LOG_FATAL("Registering mouse raw input device failed!");
                return -1;
            }
			
        case WM_INPUT:
            // request size of the raw input buffer to dwSize
            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize,
                sizeof(RAWINPUTHEADER));
         
            // allocate buffer for input data
            buffer = (RAWINPUT*)HeapAlloc(GetProcessHeap(), 0, dwSize);
         
            if(GetRawInputData((HRAWINPUT)lParam, RID_INPUT, buffer, &dwSize,
                sizeof(RAWINPUTHEADER)))
            {
				if (buffer->header.dwType == RIM_TYPEMOUSE)
				{
					is_input_blocked = do_handle_mouse( buffer->data.mouse.lLastX, 
						buffer->data.mouse.lLastY, buffer->data.mouse.usButtonFlags, buffer->data.mouse.usButtonData);     
				}
            }
         
            // free the buffer
            HeapFree(GetProcessHeap(), 0, buffer);
            break;
             
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
             
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}