LRESULT uie_albumart::on_message(HWND wnd1,UINT msg,WPARAM wp,LPARAM lp)
{
    switch(msg)
    {
    case WM_CREATE:
        {
            GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

            m_sources_control.register_foo_callbacks();
            m_sources_control.register_sources_control_callback(this);
            m_sources_control.setup_sources_control(m_config, m_sources);

            m_wheel_accum = 0;
        }
        break;

    case WM_DESTROY:
        {
            m_sources_control.unregister_sources_control_callback(this);
            m_sources_control.unregister_foo_callbacks();

            m_bufold.release();
            m_bufnew.release();
            m_bufanim.release();

            m_bmpnew.release();
            m_bmp.release();

            GdiplusShutdown(gdiplusToken);
        }
        break;

    case WM_LBUTTONDOWN:
        {
            POINTS pts = MAKEPOINTS(lp);
            POINT pt;
            POINTSTOPOINT(pt, pts);
            if (m_panning_enabled)
            {
                m_dragging = true;
                SetCursor(LoadCursor(NULL, IDC_SIZEALL));
                SetCapture(wnd1);

                m_drag_start = pt;
                m_orig_dx = m_pan_dx;
                m_orig_dy = m_pan_dy;
            }
        }
        break;
    case WM_MOUSEMOVE:
        {
            if (m_dragging)
            {
                POINTS pts = MAKEPOINTS(lp);
                m_pan_dx = m_orig_dx + pts.x - m_drag_start.x;
                m_pan_dy = m_orig_dy + pts.y - m_drag_start.y;
                redraw();
            }
        }
        break;
    case WM_CANCELMODE:
        if (m_dragging)
        {
            ReleaseCapture();
            SetCursor(LoadCursor(NULL, IDC_ARROW));
            m_dragging = false;
        }
        break;

    case WM_LBUTTONDBLCLK:
        click_func(m_config.dblclickfunc);
        b_dblclick = true;
        break;
    case WM_LBUTTONUP:
        if (m_dragging)
        {
            ReleaseCapture();
            SetCursor(LoadCursor(NULL, IDC_ARROW));
            m_dragging = false;

            // if the mouse didn't move much, it probably wasn't
            // a drag, so trigger the mouse action
            POINTS pts = MAKEPOINTS(lp);
            POINT pt;
            POINTSTOPOINT(pt, pts);

            int cxdrag = GetSystemMetrics(SM_CXDRAG);
            int cydrag = GetSystemMetrics(SM_CYDRAG);

            RECT rect;
            SetRect(&rect, -1*cxdrag/2, -1*cydrag/2, cxdrag/2, cydrag/2);
            OffsetRect(&rect, m_drag_start.x, m_drag_start.y);

            if (PtInRect(&rect, pt)) click_func(m_config.lftclickfunc);
        }
        else if (!b_dblclick)
        {
            click_func(m_config.lftclickfunc);
        }
        b_dblclick = false;
        break;
    case WM_MBUTTONUP:
        click_func(m_config.mdlclickfunc);
        break;

    case WM_MOUSEWHEEL:
        {
            short delta = GET_WHEEL_DELTA_WPARAM(wp);
            m_wheel_accum += delta;
            while (m_wheel_accum <= -WHEEL_DELTA)
            {
                m_wheel_accum += WHEEL_DELTA;
                func_NextSource(true);
            }
            while (m_wheel_accum >= WHEEL_DELTA)
            {
                m_wheel_accum -= WHEEL_DELTA;
                func_PreviousSource();
            }
        }
        break;

    case WM_PAINT:
        {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(m_hWnd, &ps);
            paint(hdc);
            EndPaint(m_hWnd, &ps);
            return 0;
        }
        break;
    case WM_TIMER:
        switch (wp)
        {
        case animation_timer_id:
            KillTimer(m_hWnd, animation_timer_id);
            redraw();
            return 0;
            break;
        case cycle_timer_id:
            if (static_api_ptr_t<ui_control>()->is_visible())
            {
                func_NextSource(false);
            }
            else
            {
                start_cycle_timer();
            }
            return 0;
            break;
        }
        break;
    case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO mmi = LPMINMAXINFO(lp);
            mmi->ptMinTrackSize.y = m_config.minheight;
            mmi->ptMinTrackSize.x = m_config.minwidth;
        }
        break;
    }
    return uDefWindowProc(wnd1, msg, wp, lp);
}