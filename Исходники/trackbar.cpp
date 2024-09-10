LRESULT track_bar::on_message(HWND wnd,UINT msg,WPARAM wp,LPARAM lp)
{
    switch(msg)
    {
    case WM_NCCREATE:
        break;
    case WM_CREATE:
    {
        if (IsThemeActive() && IsAppThemed())
        {
            m_theme = OpenThemeData(wnd, L"Trackbar");
        }
    }
    break;
    case WM_THEMECHANGED:
    {
        {
            if (m_theme)
            {
                CloseThemeData(m_theme);
                m_theme=0;
            }
            if (IsThemeActive() && IsAppThemed())
                m_theme = OpenThemeData(wnd, L"Trackbar");
        }
    }
    break;
    case WM_DESTROY:
    {
        if (m_hook_registered)
        {
            message_hook_manager::deregister_hook(message_hook_manager::type_keyboard, this);
            m_hook_registered=false;
        }
        {
            if (m_theme) CloseThemeData(m_theme);
            m_theme=0;
        }
    }
    break;
    case WM_NCDESTROY:
        break;
    case WM_SIZE:
        RedrawWindow(wnd, 0, 0, RDW_INVALIDATE|RDW_ERASE);
        break;
    case WM_MOUSEMOVE:
    {

        POINT pt = {GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
        if (m_dragging)
        {
            if (!m_last_mousemove.m_valid || wp != m_last_mousemove.m_wp || lp != m_last_mousemove.m_lp)
            {
                if (get_enabled())
                {
                    unsigned pos = calculate_position_from_point(pt);
                    set_position_internal(pos);
                    if (m_wnd_tooltip && m_host)
                    {
                        POINT pts = pt;
                        ClientToScreen(wnd, &pts);
                        track_bar_string temp;
                        m_host->get_tooltip_text(pos, temp);
                        update_tooltip(pts, temp.data());
                    }
                    if (m_host)
                        m_host->on_position_change(pos, true);
                }
            }
            m_last_mousemove.m_valid = true;
            m_last_mousemove.m_wp = wp;
            m_last_mousemove.m_lp = lp;
        }
        else
        {
            update_hot_status(pt);
        }
    }
    break;
    case WM_ENABLE:
    {
        RECT rc;
        get_thumb_rect(&rc);
        InvalidateRect(wnd, &rc, TRUE);
    }
    break;
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_XBUTTONDOWN:
    {
        if (get_enabled() && get_auto_focus() && GetFocus() != wnd)
            SetFocus(wnd);

        if (m_dragging)
        {
            destroy_tooltip();
            if (GetCapture() == wnd)
                ReleaseCapture();
            message_hook_manager::deregister_hook(message_hook_manager::type_keyboard, this);
            m_hook_registered=false;
            //SetFocus(IsWindow(m_wnd_prev) ? m_wnd_prev : uFindParentPopup(wnd));
            m_dragging = false;
            set_position_internal(m_position);
        }
    }
    break;
    case WM_LBUTTONDOWN:
    {
        if (get_enabled())
        {
            if (get_auto_focus() && GetFocus() != wnd)
                SetFocus(wnd);

            POINT pt;

            pt.x = GET_X_LPARAM(lp);
            pt.y = GET_Y_LPARAM(lp);

            RECT rc_client;
            GetClientRect(wnd, &rc_client);

            if (PtInRect(&rc_client, pt))
            {
                m_dragging = true;
                SetCapture(wnd);

                //SetFocus(wnd);
                message_hook_manager::register_hook(message_hook_manager::type_keyboard, this);
                m_hook_registered=true;

                unsigned pos = calculate_position_from_point(pt);
                set_position_internal(pos);
                POINT pts = pt;
                ClientToScreen(wnd, &pts);
                if (m_show_tooltips && m_host)
                {
                    track_bar_string temp;
                    m_host->get_tooltip_text(pos, temp);
                    create_tooltip(temp.data(), pts);
                }
            }
            m_last_mousemove.m_valid = false;
        }
    }
    return 0;
    case WM_LBUTTONUP:
    {
        if (m_dragging)
        {
            destroy_tooltip();
            if (GetCapture() == wnd)
                ReleaseCapture();
            m_dragging = false;
            if (get_enabled())
            {
                POINT pt;

                pt.x = GET_X_LPARAM(lp);
                pt.y = GET_Y_LPARAM(lp);

                unsigned pos = calculate_position_from_point(pt);
                set_position(pos);
            }
            //SetFocus(IsWindow(m_wnd_prev) ? m_wnd_prev : uFindParentPopup(wnd));
            message_hook_manager::deregister_hook(message_hook_manager::type_keyboard, this);
            m_hook_registered = false;
            if (m_host)
                m_host->on_position_change(m_display_position, false);

            m_last_mousemove.m_valid = false;
        }
    }
    return 0;
    case WM_KEYDOWN:
    case WM_KEYUP:
    {
        if ((wp == VK_ESCAPE || wp == VK_RETURN) && m_host && m_host->on_key(wp, lp))
            return 0;
        if ( !(lp & (1<<31)) && (wp == VK_LEFT || wp == VK_DOWN || wp == VK_RIGHT || wp == VK_UP))
        {
            bool down = (wp == VK_LEFT || wp == VK_UP) == false;//!get_direction();
            unsigned newpos = m_position;
            if (down && m_step > m_position)
                newpos = 0;
            else if (!down && m_step + m_position > m_range)
                newpos = m_range;
            else
                newpos += down ? -(int)m_step : m_step;
            if (newpos != m_position)
            {
                set_position(newpos);
                if (m_host)
                    m_host->on_position_change(m_position, false);
            }
        }
        if ( !(lp & (1<<31)) && (wp == VK_HOME || wp == VK_END))
        {
            bool down = (wp == VK_END) == false;//!get_direction();
            unsigned newpos = m_position;
            if (down) newpos = m_range;
            else newpos = 0;
            if (newpos != m_position)
            {
                set_position(newpos);
                if (m_host)
                    m_host->on_position_change(m_position, false);
            }
        }
    }
    break;
    case WM_MOUSEWHEEL:
    {
        UINT ucNumLines=3;  // 3 is the default
        SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &ucNumLines, 0);
        unsigned short fwKeys = GET_KEYSTATE_WPARAM(wp);
        short zDelta = GET_WHEEL_DELTA_WPARAM(wp);
        int xPos = GET_X_LPARAM(lp);
        int yPos = GET_Y_LPARAM(lp);
        if (ucNumLines == WHEEL_PAGESCROLL)
            ucNumLines = 3;
        int delta = MulDiv(m_step*zDelta, ucNumLines, WHEEL_DELTA);
        bool down = delta < 0;
        //if (get_direction()) down = down == false;
        if (!get_orientation()) down = down == false;
        if (m_mouse_wheel_reversed)
            down = down == false;
        unsigned offset = abs(delta);

        unsigned newpos = m_position;
        if (down && offset > m_position)
            newpos = 0;
        else if (!down && offset + m_position > m_range)
            newpos = m_range;
        else
            newpos += down ? -(int)offset : offset;
        if (newpos != m_position)
        {
            set_position(newpos);
            if (m_host)
                m_host->on_position_change(m_position, false);
        }
    }
    return 0;
#if 0
    case WM_KEYDOWN:
        if (wp == VK_ESCAPE)
        {
            destroy_tooltip();
            if (GetCapture() == wnd)
                ReleaseCapture();
            SetFocus(IsWindow(m_wnd_prev) ? m_wnd_prev : uFindParentPopup(wnd));
            m_dragging = false;
            set_position_internal(m_position);
            return 0;
        }
        break;
    case WM_SETFOCUS:
        m_wnd_prev = (HWND)wp;
        break;
#endif
    case WM_MOVE:
        RedrawWindow(wnd, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
        break;
    case WM_ERASEBKGND:
        return FALSE;
    case WM_PAINT:
    {
        RECT rc_client;
        GetClientRect(wnd, &rc_client);

        PAINTSTRUCT ps;

        HDC dc = BeginPaint(wnd, &ps);

        RECT rc_thumb;

        get_thumb_rect(&rc_thumb);

        RECT rc_track; //channel
        get_channel_rect(&rc_track);

        //Offscreen rendering to eliminate flicker
        HDC dc_mem = CreateCompatibleDC(dc);

        //Create a rect same size of update rect
        HBITMAP bm_mem = CreateCompatibleBitmap(dc, rc_client.right, rc_client.bottom);

        HBITMAP bm_old = (HBITMAP)SelectObject(dc_mem, bm_mem);

        //we should always be erasing first, so shouldn't be needed
        BitBlt(dc_mem, 0, 0, rc_client.right, rc_client.bottom, dc, 0, 0, SRCCOPY);
        if (ps.fErase)
        {
            draw_background(dc_mem, &rc_client);
        }

        draw_channel(dc_mem, &rc_track);
        draw_thumb(dc_mem, &rc_thumb);

        BitBlt(dc, 0, 0, rc_client.right, rc_client.bottom, dc_mem, 0, 0, SRCCOPY);
        SelectObject(dc_mem, bm_old);
        DeleteObject(bm_mem);
        DeleteDC(dc_mem);
        EndPaint(wnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(wnd, msg, wp, lp);
}