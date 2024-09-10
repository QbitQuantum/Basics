//
//  函数: WndProc_lcd(HWND, unsigned, WORD, LONG)
//
//  目的: 处理主窗口的消息。
//
LRESULT CALLBACK WndProc_lcd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT         ps ;
    switch (message)
    {
        case WM_PAINT:
            BeginPaint (hWnd, &ps) ;
            StretchDIBits (lcd_hdc,    0, 0,cn_lcd_window_xsize, cn_lcd_window_ysize,
                       0, LCD_YSIZE, LCD_XSIZE,-LCD_YSIZE,pg_frame_buffer,lcdbmi,DIB_RGB_COLORS,SRCCOPY) ;
            EndPaint (hWnd, &ps) ;
            break;
        case WM_MOVE:
            StretchDIBits (lcd_hdc,    0, 0,cn_lcd_window_xsize, cn_lcd_window_ysize,
               0, LCD_YSIZE, LCD_XSIZE,-LCD_YSIZE,pg_frame_buffer,lcdbmi,DIB_RGB_COLORS,SRCCOPY) ;
            GetWindowRect(hWnd, &tg_WindowRect);
            MoveWindow(tg_keyboard_wnd, tg_WindowRect.left+s32g_window_width + 5,
                       tg_WindowRect.top, s32g_window_width, s32g_window_height,
                       true);
            break ;
        case WM_ACTIVATE:
            StretchDIBits (lcd_hdc,    0, 0,cn_lcd_window_xsize, cn_lcd_window_ysize,
               0, LCD_YSIZE, LCD_XSIZE,-LCD_YSIZE,pg_frame_buffer,lcdbmi,DIB_RGB_COLORS,SRCCOPY) ;

            break ;
        case WM_LBUTTONDOWN:
            touch_x = LOWORD(lParam);
            touch_y = HIWORD(lParam);
            touch_z = 1;
            touched = true;
            break;
        case WM_LBUTTONUP:
            touch_x = LOWORD(lParam);
            touch_y = HIWORD(lParam);
            touch_z = 0;
            touched = false;
            break;
        case WM_MOUSEMOVE:
            touch_x = LOWORD(lParam);
            touch_y = HIWORD(lParam);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}