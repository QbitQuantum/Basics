LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int wmId, wmEvent;
  PAINTSTRUCT ps;
  HDC hdc;
  HRESULT hResult;

  switch (message)
  {

  case WM_CREATE:
  {
    // Todo: 
    // 1. Put this in an actual panel and make program resizeable (maybe)
    // 2. All those edit boxes should probably be classes...

    int panel_pos_x = 420;
    int panel_pos_y = 10;
    int edit_width = 45;
    int edit_caption_height = 17;
    int caption_width = 47;
    int caption_panel_pos_x = panel_pos_x + edit_width + 10;
    int y_space = 24;

    sens_box = CreateWindow(L"EDIT",
      L"4",
      WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
      panel_pos_x, panel_pos_y + y_space * 0, edit_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(sens_box, WM_SETFONT, (WPARAM)standard_font, TRUE);
    //SetWindowSubclass(sens_box,ButtonProc,0,0); // 

    accel_box = CreateWindow(L"EDIT",
      L"0",
      WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
      panel_pos_x, panel_pos_y + y_space * 1, edit_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(accel_box, WM_SETFONT, (WPARAM)standard_font, TRUE);

    offset_box = CreateWindow(L"EDIT",
      L"0",
      WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
      panel_pos_x, panel_pos_y + y_space * 2, edit_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(offset_box, WM_SETFONT, (WPARAM)standard_font, TRUE);

    senscap_box = CreateWindow(L"EDIT",
      L"0",
      WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
      panel_pos_x, panel_pos_y + y_space * 3, edit_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(senscap_box, WM_SETFONT, (WPARAM)standard_font, TRUE);

    power_box = CreateWindow(L"EDIT",
      L"2",
      WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
      panel_pos_x, panel_pos_y + y_space * 4, edit_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(power_box, WM_SETFONT, (WPARAM)standard_font, TRUE);

    m_cpi_box = CreateWindow(L"EDIT",
      L"0",
      WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
      panel_pos_x, panel_pos_y + y_space * 5, edit_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(m_cpi_box, WM_SETFONT, (WPARAM)standard_font, TRUE);

    fps_box = CreateWindow(L"EDIT",
      L"125",
      WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
      panel_pos_x, panel_pos_y + y_space * 6, edit_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(fps_box, WM_SETFONT, (WPARAM)standard_font, TRUE);

    x_scale_box = CreateWindow(L"EDIT",
      L"8",
      WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
      panel_pos_x, panel_pos_y + y_space * 7, edit_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(x_scale_box, WM_SETFONT, (WPARAM)standard_font, TRUE);

    y_scale_box = CreateWindow(L"EDIT",
      L"8",
      WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
      panel_pos_x, panel_pos_y + y_space * 8, edit_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(y_scale_box, WM_SETFONT, (WPARAM)standard_font, TRUE);

    caption_box = CreateWindow(L"STATIC",
      L"sens",
      WS_CHILD | WS_VISIBLE | SS_NOTIFY,
      caption_panel_pos_x, panel_pos_y + y_space * 0, caption_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(caption_box, WM_SETFONT, (WPARAM)standard_font, TRUE);
    CreateToolTipForRect(caption_box, hInst, L"cl_sensitivity");
    CreateToolTipForRect(sens_box, hInst, L"cl_sensitivity");

    caption_box = CreateWindow(L"STATIC",
      L"accel",
      WS_CHILD | WS_VISIBLE | SS_NOTIFY,
      caption_panel_pos_x, panel_pos_y + y_space * 1, caption_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(caption_box, WM_SETFONT, (WPARAM)standard_font, TRUE);
    CreateToolTipForRect(caption_box, hInst, L"cl_mouseAccel");
    CreateToolTipForRect(accel_box, hInst, L"cl_mouseAccel");

    caption_box = CreateWindow(L"STATIC",
      L"offset",
      WS_CHILD | WS_VISIBLE | SS_NOTIFY,
      caption_panel_pos_x, panel_pos_y + y_space * 2, caption_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(caption_box, WM_SETFONT, (WPARAM)standard_font, TRUE);
    CreateToolTipForRect(caption_box, hInst, L"cl_mouseAccelOffset");
    CreateToolTipForRect(offset_box, hInst, L"cl_mouseAccelOffset");

    caption_box = CreateWindow(L"STATIC",
      L"cap",
      WS_CHILD | WS_VISIBLE | SS_NOTIFY,
      caption_panel_pos_x, panel_pos_y + y_space * 3, caption_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(caption_box, WM_SETFONT, (WPARAM)standard_font, TRUE);
    CreateToolTipForRect(caption_box, hInst, L"cl_mouseSensCap");
    CreateToolTipForRect(senscap_box, hInst, L"cl_mouseSensCap");

    caption_box = CreateWindow(L"STATIC",
      L"power",
      WS_CHILD | WS_VISIBLE | SS_NOTIFY,
      caption_panel_pos_x, panel_pos_y + y_space * 4, caption_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(caption_box, WM_SETFONT, (WPARAM)standard_font, TRUE);
    CreateToolTipForRect(caption_box, hInst, L"cl_mouseAccelPower");
    CreateToolTipForRect(power_box, hInst, L"cl_mouseAccelPower");

    caption_box = CreateWindow(L"STATIC",
      L"m_cpi",
      WS_CHILD | WS_VISIBLE | SS_NOTIFY,
      caption_panel_pos_x, panel_pos_y + y_space * 5, caption_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(caption_box, WM_SETFONT, (WPARAM)standard_font, TRUE);
    CreateToolTipForRect(caption_box, hInst, L"m_cpi");
    CreateToolTipForRect(m_cpi_box, hInst, L"m_cpi");

    caption_box = CreateWindow(L"STATIC",
      L"fps",
      WS_CHILD | WS_VISIBLE | SS_NOTIFY,
      caption_panel_pos_x, panel_pos_y + y_space * 6, caption_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(caption_box, WM_SETFONT, (WPARAM)standard_font, TRUE);
    CreateToolTipForRect(caption_box, hInst, L"com_maxfps");
    CreateToolTipForRect(fps_box, hInst, L"com_maxfps");

    caption_box = CreateWindow(L"STATIC",
      L"x-scale",
      WS_CHILD | WS_VISIBLE | SS_NOTIFY,
      caption_panel_pos_x, panel_pos_y + y_space * 7, caption_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(caption_box, WM_SETFONT, (WPARAM)standard_font, TRUE);
    CreateToolTipForRect(caption_box, hInst, L"scale for x-axis");
    CreateToolTipForRect(x_scale_box, hInst, L"scale for x-axis");

    caption_box = CreateWindow(L"STATIC",
      L"y-scale",
      WS_CHILD | WS_VISIBLE | SS_NOTIFY,
      caption_panel_pos_x, panel_pos_y + y_space * 8, caption_width, edit_caption_height,
      hWnd, NULL, NULL, NULL);
    SendMessage(caption_box, WM_SETFONT, (WPARAM)standard_font, TRUE);
    CreateToolTipForRect(caption_box, hInst, L"scale for y-axis");
    CreateToolTipForRect(y_scale_box, hInst, L"scale for y-axis");


    text_box = CreateWindow(L"STATIC",
      L"If you can see this something is not working.",
      WS_CHILD | WS_VISIBLE,
      10, 220, 400, 30,
      hWnd, NULL, NULL, NULL);

    convert_button = CreateWindow(L"BUTTON",
      L"convert",
      WS_CHILD | WS_VISIBLE | BS_FLAT,
      432, 222, 55, 23,
      hWnd, (HMENU)IDC_CONVERT_BUTTON, NULL, NULL);
    SendMessage(convert_button, WM_SETFONT, (WPARAM)standard_font, TRUE);
    CreateToolTipForRect(convert_button, hInst, L"If m_cpi is set to 0, convert all settings to m_cpi system. Otherwise, convert all settings back.");

    SetWindowLongPtr(text_box, -4, (LONG_PTR)&TextBoxProc);
    break;
  }

  case WM_COMMAND:
    wmId = LOWORD(wParam);
    wmEvent = HIWORD(wParam);
    if (wmEvent == EN_CHANGE) {
      GetWindowText(sens_box, global_temp_string, 10);
      cvar_sens = wcstod(global_temp_string, NULL);
      GetWindowText(offset_box, global_temp_string, 10);
      cvar_offset = wcstod(global_temp_string, NULL);
      GetWindowText(accel_box, global_temp_string, 10);
      cvar_accel = wcstod(global_temp_string, NULL);
      GetWindowText(senscap_box, global_temp_string, 10);
      cvar_senscap = wcstod(global_temp_string, NULL);
      GetWindowText(power_box, global_temp_string, 10);
      cvar_power = wcstod(global_temp_string, NULL) - 1;
      if (cvar_power < 0) cvar_power = 0;
      GetWindowText(m_cpi_box, global_temp_string, 10);
      cvar_m_cpi = wcstod(global_temp_string, NULL);
      GetWindowText(fps_box, global_temp_string, 10);
      max_fps = wcstod(global_temp_string, NULL);
      GetWindowText(x_scale_box, global_temp_string, 10);
      graph_max_x = wcstod(global_temp_string, NULL);
      GetWindowText(y_scale_box, global_temp_string, 10);
      graph_max_y = wcstod(global_temp_string, NULL);
      InvalidateRect(hWnd, &invalidate_rect, false);
    }
    switch (wmId)
    {
    case ID_HELP_ABOUT:
      DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, AboutProc);
      break;
    case ID_FILE_EXIT:
      DestroyWindow(hWnd);
      break;
    case IDC_CONVERT_BUTTON:
      if (cvar_power != 1){
        MessageBeep(1);
        DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, ErrorProc);
      }
      else {
        if (cvar_m_cpi == 0) {
          DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, ConvertProc);
        }
        else ConvertFromMcpi();
      }
      break;

    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;

  case WM_INPUT: {

    UINT dwSize;
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize,
      sizeof(RAWINPUTHEADER));
    LPBYTE lpb = new BYTE[dwSize];
    if (lpb == NULL)
    {
      return 0;
    }

    if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize,
      sizeof(RAWINPUTHEADER)) != dwSize)
      OutputDebugString(TEXT("GetRawInputData does not return correct size !\n"));

    RAWINPUT* raw = (RAWINPUT*)lpb;


    if (raw->header.dwType == RIM_TYPEMOUSE)
    {
      mouse_x_buffer += raw->data.mouse.lLastX;
      mouse_y_buffer += raw->data.mouse.lLastY;

      auto t_end = std::chrono::high_resolution_clock::now();
      double frame_duration = (std::chrono::duration<double, std::micro>(t_end - t_start_frame).count());
      double mouse_input_duration = (std::chrono::duration<double, std::micro>(t_end - t_start_mouse).count());
      double cur_mouse_poll_rate = 1000 * 1000 / mouse_input_duration;

      if ((double)frame_duration + 1000 > 1000 * 1000 / (max_fps)){
        cur_fps = 1 * 1000 * 1000 / frame_duration;
        double mcpi2 = cvar_m_cpi / 2.54;
        double mx = mouse_x_buffer;
        double my = mouse_y_buffer;
        if (mcpi2 > 0) {
          mx = mouse_x_buffer / mcpi2;
          my = mouse_y_buffer / mcpi2;
        }
        speed = sqrt((double)mx*mx + my*my);

        speed = 1000 * speed / frame_duration;
        if (mcpi2 > 0) {
          speed = speed * 1000;
          speed_unit_str = speed_unit_str_cmps;
          move_unit_str = move_unit_str_cmps;
        }
        else {
          speed_unit_str = speed_unit_str_cpms;
          move_unit_str = move_unit_str_cpms;
        }
        hResult = StringCchPrintf(info_string_left, STRSAFE_MAX_CCH, TEXT("mouse speed: %.3f %s\r\nmultiplier: %.3f %s\r\n"),
          speed, speed_unit_str,
          multi, move_unit_str);
        hResult = StringCchPrintf(info_string_right, STRSAFE_MAX_CCH, TEXT("mouse poll rate: %04.0f Hz\r\n%.0f fps"),
          cur_mouse_poll_rate, cur_fps);

        InvalidateRect(text_box, &invalidate_rect_2, false);
        InvalidateRect(hWnd, &invalidate_rect, false);

        if (FAILED(hResult))
        {
          // TODO: write error handler
        }
        // OutputDebugString(info_string_left);
        // Static_SetText(text_box, info_string_left);
        

        t_start_frame = t_end;
        mouse_x_buffer = 0;
        mouse_y_buffer = 0;
      }
      t_start_mouse = t_end;

    }
    delete[] lpb;

    return 0;
  }



  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    hdc_backbuffer = CreateCompatibleDC(hdc);
    hbm_backbuffer = CreateCompatibleBitmap(hdc, graph_width, graph_height);

    h_old = SelectObject(hdc_backbuffer, hbm_backbuffer);

    FillRect(hdc_backbuffer, &invalidate_rect, black_brush);
    hResult = StringCchPrintf(global_temp_string, STRSAFE_MAX_CCH, TEXT("%.1f [%s]"), graph_max_y, move_unit_str);
    SetTextColor(hdc_backbuffer, 0x00DDDDDD);
    SetBkColor(hdc_backbuffer, 0x00000000);
    SelectObject(hdc_backbuffer, standard_font);
    TextOut(hdc_backbuffer, 3, 0, global_temp_string, wcslen(global_temp_string));
    TextOut(hdc_backbuffer, 3, invalidate_rect.bottom - 27, L"0", 1);

    hResult = StringCchPrintf(global_temp_string, STRSAFE_MAX_CCH, TEXT("[%s] %.1f"), speed_unit_str, graph_max_x);
    SetTextAlign(hdc_backbuffer, TA_RIGHT);
    TextOut(hdc_backbuffer, invalidate_rect.right - 13, invalidate_rect.bottom - 27, global_temp_string, wcslen(global_temp_string));


    //OutputDebugString(global_temp_string);


    for (int i = 0; i<graph_width; i++){
      double x = i*graph_max_x / graph_width;

      double y = cvar_sens + pow((cvar_accel*(x - cvar_offset)), cvar_power);

      if (cvar_offset>x) y = cvar_sens;
      if (y > cvar_senscap && cvar_senscap > 0) y = cvar_senscap;
      int j = graph_height - y*graph_height / graph_max_y;
      SetPixel(hdc_backbuffer, i, j, 0x00BBBBBB);
    }

    multi = cvar_sens + pow((cvar_accel*(speed - cvar_offset)), cvar_power);

    if (cvar_offset > speed) multi = cvar_sens;
    if (multi > cvar_senscap && cvar_senscap > 0) multi = cvar_senscap;
    red_rectangle.top = graph_height - multi*graph_height / graph_max_y - 2;
    red_rectangle.left = speed*graph_width / graph_max_x - 2;
    red_rectangle.right = speed*graph_width / graph_max_x + 3;
    red_rectangle.bottom = graph_height - multi*graph_height / graph_max_y + 3;

    FillRect(hdc_backbuffer, &red_rectangle, red_brush);

    BitBlt(hdc, 10, 10, graph_width, graph_height, hdc_backbuffer, 0, 0, SRCCOPY);


    SelectObject(hdc_backbuffer, h_old);
    DeleteObject(hbm_backbuffer);
    DeleteDC(hdc_backbuffer);


    EndPaint(hWnd, &ps);

    break;
  case WM_CTLCOLORSTATIC:
  {
    HDC hdcStatic = (HDC)wParam;
    SetTextColor(hdcStatic, text_color);
    SetBkColor(hdcStatic, background_color);

    return (INT_PTR)background_brush;
  }
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}