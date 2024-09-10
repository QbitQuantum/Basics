static void init_datasette_dialog(HWND hwnd)
{
    HWND snd_hwnd;
    int res_value;
    int res_value_loop;
    int active_value;
    int xpos_max;
    int group_max;
    RECT rect;

    /* translate all dialog items */
    uilib_localize_dialog(hwnd, datasette_dialog);

    /* adjust the size of the elements in the datasette_sub_group */
    uilib_adjust_group_width(hwnd, datasette_sub_group);

    /* adjust the size of the  'reset with cpu' element */
    uilib_adjust_element_width(hwnd, IDC_DATASETTE_RESET_WITH_CPU);

    /* adjust the size of the motor group element */
    uilib_adjust_element_width(hwnd, IDC_DATASETTE_MOTOR_GROUP);

    /* get the max x of the datasette_sub_group */
    uilib_get_group_max_x(hwnd, datasette_sub_group, &xpos_max);

    /* get the max x of the motor group element */
    uilib_get_element_max_x(hwnd, IDC_DATASETTE_MOTOR_GROUP, &group_max);

    /* calculate the max x of the motor group element and the
       datasette_sub_group elements */
    if (group_max < xpos_max + 10) {
        group_max = xpos_max + 10;
    }

    /* set the width of the motor group element to 'surround' the
       datasette_sub_group elements */
    uilib_set_element_width(hwnd, IDC_DATASETTE_MOTOR_GROUP, group_max);

    /* get the max x of the datasette_main_group elements */
    uilib_get_group_max_x(hwnd, datasette_main_group, &xpos_max);

    /* set the width of the dialog to 'surround' all the elements */
    GetWindowRect(hwnd, &rect);
    MoveWindow(hwnd, rect.left, rect.top, xpos_max + 10, rect.bottom - rect.top, TRUE);

    /* recenter the buttons in the newly resized dialog window */
    uilib_center_buttons(hwnd, move_buttons_group, 0);

    resources_get_int("DatasetteResetWithCPU", &res_value);
    CheckDlgButton(hwnd, IDC_DATASETTE_RESET_WITH_CPU, res_value ? BST_CHECKED : BST_UNCHECKED);

    snd_hwnd = GetDlgItem(hwnd, IDC_DATASETTE_ZERO_GAP_DELAY);
    for (res_value_loop = 0; res_value_loop < 7; res_value_loop++) {
        TCHAR st[10];

        _stprintf(st, TEXT("%d"), ui_datasette_zero_gap_delay[res_value_loop]);
        SendMessage(snd_hwnd, CB_ADDSTRING, 0, (LPARAM)st);
    }
    resources_get_int("DatasetteZeroGapDelay", &res_value);
    active_value = 4; /* default */
    for (res_value_loop = 0; res_value_loop < 7; res_value_loop++) {
        if (ui_datasette_zero_gap_delay[res_value_loop] == res_value) {
            active_value = res_value_loop;
        }
    }
    SendMessage(snd_hwnd, CB_SETCURSEL, (WPARAM)active_value, 0);

    snd_hwnd = GetDlgItem(hwnd, IDC_DATASETTE_SPEED_TUNING);
    for (res_value_loop = 0; res_value_loop < 8; res_value_loop++) {
        TCHAR st[10];
        _stprintf(st, TEXT("%d"), res_value_loop);
        SendMessage(snd_hwnd, CB_ADDSTRING, 0, (LPARAM)st);
    }
    resources_get_int("DatasetteSpeedTuning", &res_value);
    SendMessage(snd_hwnd, CB_SETCURSEL, (WPARAM)res_value, 0);
}