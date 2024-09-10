static void init_dialog(HWND hwnd, int num)
{
    int drive_type, drive_extend_image_policy, drive_idle_method, n;
    int drive_true_emulation, iecdevice, enabled;
    int xpos;
    int xstart;
    HWND temp_hwnd;
    HWND parent_hwnd;
    HWND element;

    parent_hwnd = GetParent(hwnd);

    /* translate all dialog items */
    uilib_localize_dialog(hwnd, drive_dialog_trans);

    /* translate the parent window items */
    uilib_localize_dialog(parent_hwnd, parent_dialog_trans);

    /* translate the generic items */
    for (n = 0; generic_items[n].text != NULL; n++) {
        element = GetDlgItem(hwnd, generic_items[n].idm);
        SetWindowText(element, generic_items[n].text);
    }

    /* adjust the size of the elements in the main group */
    uilib_adjust_group_width(hwnd, drive_main_group);

    /* get the max x of the elements in the left group */
    uilib_get_group_max_x(hwnd, drive_left_group, &xpos);

    /* get the min x of the none element of the left group */
    uilib_get_element_min_x(hwnd, IDC_SELECT_DRIVE_TYPE_NONE, &xstart);

    /* resize and move the left group element to the correct position */
    uilib_move_and_set_element_width(hwnd, IDC_DRIVE_TYPE, xstart - 10, xpos - xstart + 20);

    /* get the max x of the left group element */
    uilib_get_element_max_x(hwnd, IDC_DRIVE_TYPE, &xpos);
    
    /* move the middle group elements to the correct position */
    uilib_move_group(hwnd, drive_middle_move_group, xpos + 20);
    uilib_move_element(hwnd, IDC_40_TRACK_HANDLING, xpos + 10);
    uilib_move_element(hwnd, IDC_DRIVE_EXPANSION, xpos + 10);

    xstart = xpos + 20;

    /* get the max x of the middle group */
    uilib_get_group_max_x(hwnd, drive_middle_group, &xpos);
    
    /* resize and move the middle group boxes to the correct position */
    uilib_move_and_set_element_width(hwnd, IDC_40_TRACK_HANDLING, xstart - 10, xpos - xstart + 20);
    uilib_move_and_set_element_width(hwnd, IDC_DRIVE_EXPANSION, xstart - 10, xpos - xstart + 20);

    /* get the max x of the middle group element */
    uilib_get_element_max_x(hwnd, IDC_DRIVE_EXPANSION, &xpos);

    /* move the right group elements to the correct position */
    uilib_move_group(hwnd, drive_right_move_group, xpos + 20);
    uilib_move_element(hwnd, IDC_IDLE_METHOD, xpos + 10);

    xstart = xpos + 20;

    /* get the max x of the right group */
    uilib_get_group_max_x(hwnd, drive_right_group, &xpos);

    /* resize and move the right group element to the correct position */
    uilib_move_and_set_element_width(hwnd, IDC_IDLE_METHOD, xstart - 10, xpos - xstart + 20);

    /* get the max x of the drive parallel cable label element */
    uilib_get_element_max_x(hwnd, IDC_DRIVE_PARALLEL_CABLE_LABEL, &xpos);

    /* move the drive parallel cable element to the right position */
    uilib_move_element(hwnd, IDC_DRIVE_PARALLEL_CABLE, xpos + 10);

    /* recenter the buttons in the newly resized dialog window */
    uilib_center_buttons(parent_hwnd, move_buttons_group, 0);

    resources_get_int_sprintf("IECDevice%i", &iecdevice, num);
    resources_get_int("DriveTrueEmulation", &drive_true_emulation);
    enabled = drive_true_emulation && !iecdevice;

    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_1541), enabled && drive_check_type(DRIVE_TYPE_1541, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_1541II), enabled && drive_check_type(DRIVE_TYPE_1541II, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_1570), enabled && drive_check_type(DRIVE_TYPE_1570, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_1571), enabled && drive_check_type(DRIVE_TYPE_1571, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_1581), enabled && drive_check_type(DRIVE_TYPE_1581, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_2000), enabled && drive_check_type(DRIVE_TYPE_2000, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_4000), enabled && drive_check_type(DRIVE_TYPE_4000, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_2031), enabled && drive_check_type(DRIVE_TYPE_2031, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_2040), enabled && drive_check_type(DRIVE_TYPE_2040, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_3040), enabled && drive_check_type(DRIVE_TYPE_3040, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_4040), enabled && drive_check_type(DRIVE_TYPE_4040, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_1001), enabled && drive_check_type(DRIVE_TYPE_1001, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_8050), enabled && drive_check_type(DRIVE_TYPE_8050, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_8250), enabled && drive_check_type(DRIVE_TYPE_8250, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_NONE), enabled);

    resources_get_int_sprintf("Drive%dType", &drive_type, num);
    resources_get_int_sprintf("Drive%dExtendImagePolicy", &drive_extend_image_policy, num);
    resources_get_int_sprintf("Drive%dIdleMethod", &drive_idle_method, num);

    dialog_drive_type[num - 8] = drive_type;
    switch (drive_type) {
        case DRIVE_TYPE_NONE:
            n = IDC_SELECT_DRIVE_TYPE_NONE;
            break;
        case DRIVE_TYPE_1541:
            n = IDC_SELECT_DRIVE_TYPE_1541;
            break;
        case DRIVE_TYPE_1541II:
            n = IDC_SELECT_DRIVE_TYPE_1541II;
            break;
        case DRIVE_TYPE_1570:
            n = IDC_SELECT_DRIVE_TYPE_1570;
            break;
        case DRIVE_TYPE_1571:
            n = IDC_SELECT_DRIVE_TYPE_1571;
            break;
        case DRIVE_TYPE_1581:
            n = IDC_SELECT_DRIVE_TYPE_1581;
            break;
        case DRIVE_TYPE_2000:
            n = IDC_SELECT_DRIVE_TYPE_2000;
            break;
        case DRIVE_TYPE_4000:
            n = IDC_SELECT_DRIVE_TYPE_4000;
            break;
        case DRIVE_TYPE_2031:
            n = IDC_SELECT_DRIVE_TYPE_2031;
            break;
        case DRIVE_TYPE_2040:
            n = IDC_SELECT_DRIVE_TYPE_2040;
            break;
        case DRIVE_TYPE_3040:
            n = IDC_SELECT_DRIVE_TYPE_3040;
            break;
        case DRIVE_TYPE_4040:
            n = IDC_SELECT_DRIVE_TYPE_4040;
            break;
        case DRIVE_TYPE_1001:
            n = IDC_SELECT_DRIVE_TYPE_1001;
            break;
        case DRIVE_TYPE_8050:
            n = IDC_SELECT_DRIVE_TYPE_8050;
            break;
        case DRIVE_TYPE_8250:
            n = IDC_SELECT_DRIVE_TYPE_8250;
            break;
    }

    if (!enabled) {
        n = IDC_SELECT_DRIVE_TYPE_NONE;
    }

    CheckRadioButton(hwnd, IDC_SELECT_DRIVE_TYPE_1541, IDC_SELECT_DRIVE_TYPE_NONE, n);

    enable_controls_for_drive_settings(hwnd, n);

    dialog_drive_extend[num - 8] = drive_extend_image_policy;
    switch (drive_extend_image_policy) {
        case DRIVE_EXTEND_NEVER:
            n = IDC_SELECT_DRIVE_EXTEND_NEVER;
            break;
        case DRIVE_EXTEND_ASK:
            n = IDC_SELECT_DRIVE_EXTEND_ASK;
            break;
        case DRIVE_EXTEND_ACCESS:
            n = IDC_SELECT_DRIVE_EXTEND_ACCESS;
            break;
    }

    CheckRadioButton(hwnd, IDC_SELECT_DRIVE_EXTEND_NEVER, IDC_SELECT_DRIVE_EXTEND_ACCESS, n);

    dialog_drive_idle[num - 8] = drive_idle_method;
    switch (drive_idle_method) {
        case DRIVE_IDLE_NO_IDLE:
            n = IDC_SELECT_DRIVE_IDLE_NO_IDLE;
            break;
        case DRIVE_IDLE_TRAP_IDLE:
            n = IDC_SELECT_DRIVE_IDLE_TRAP_IDLE;
            break;
        case DRIVE_IDLE_SKIP_CYCLES:
            n = IDC_SELECT_DRIVE_IDLE_SKIP_CYCLES;
            break;
    }

    CheckRadioButton(hwnd, IDC_SELECT_DRIVE_IDLE_NO_IDLE, IDC_SELECT_DRIVE_IDLE_SKIP_CYCLES, n);

    resources_get_int_sprintf("Drive%dParallelCable", &n, num);

    temp_hwnd = GetDlgItem(hwnd, IDC_DRIVE_PARALLEL_CABLE);
    SendMessage(temp_hwnd, CB_ADDSTRING, 0, (LPARAM)translate_text(IDS_NONE));
    SendMessage(temp_hwnd, CB_ADDSTRING, 0, (LPARAM)translate_text(IDS_STANDARD));
    SendMessage(temp_hwnd, CB_ADDSTRING, 0, (LPARAM)"Dolphin DOS 3");
    SendMessage(temp_hwnd, CB_ADDSTRING, 0, (LPARAM)"Formel 64");
    SendMessage(temp_hwnd, CB_SETCURSEL, (WPARAM)n, 0);

    resources_get_int_sprintf("Drive%dRAM2000", &n, num);
    CheckDlgButton(hwnd, IDC_TOGGLE_DRIVE_EXPANSION_2000, n ? BST_CHECKED : BST_UNCHECKED);

    resources_get_int_sprintf("Drive%dRAM4000", &n, num);
    CheckDlgButton(hwnd, IDC_TOGGLE_DRIVE_EXPANSION_4000, n ? BST_CHECKED : BST_UNCHECKED);

    resources_get_int_sprintf("Drive%dRAM6000", &n, num);
    CheckDlgButton(hwnd, IDC_TOGGLE_DRIVE_EXPANSION_6000, n ? BST_CHECKED : BST_UNCHECKED);

    resources_get_int_sprintf("Drive%dRAM8000", &n, num);
    CheckDlgButton(hwnd, IDC_TOGGLE_DRIVE_EXPANSION_8000, n ? BST_CHECKED : BST_UNCHECKED);

    resources_get_int_sprintf("Drive%dRAMA000", &n, num);
    CheckDlgButton(hwnd, IDC_TOGGLE_DRIVE_EXPANSION_A000, n ? BST_CHECKED : BST_UNCHECKED);
}