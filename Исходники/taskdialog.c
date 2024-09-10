static HRESULT CALLBACK taskdialog_callback_proc_timer(HWND hwnd, UINT notification,
        WPARAM wParam, LPARAM lParam, LONG_PTR ref_data)
{
    struct timer_notification_data *data = (struct timer_notification_data *)ref_data;

    if (notification == TDN_TIMER)
    {
        DWORD elapsed_ms;
        int delta;

        elapsed_ms = (DWORD)wParam;

        if (data->num_fired == 3)
            ok(data->last_elapsed_ms > elapsed_ms, "Expected reference time update.\n");
        else
        {
            delta = elapsed_ms - data->last_elapsed_ms;
            ok(delta > 0, "Expected positive time tick difference.\n");
        }
        data->last_elapsed_ms = elapsed_ms;

        if (data->num_fired == 3)
            PostMessageW(hwnd, TDM_CLICK_BUTTON, IDOK, 0);

        ++data->num_fired;
        return data->num_fired == 3 ? S_FALSE : S_OK;
    }

    return S_OK;
}