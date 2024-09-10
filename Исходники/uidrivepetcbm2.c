static void init_dialog(HWND hwnd, int num)
{
    int drive_type, drive_extend_image_policy, n = 0;

    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_2031),
                 drive_check_type(DRIVE_TYPE_2031, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_2040),
                 drive_check_type(DRIVE_TYPE_2040, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_3040),
                 drive_check_type(DRIVE_TYPE_3040, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_4040),
                 drive_check_type(DRIVE_TYPE_4040, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_1001),
                 drive_check_type(DRIVE_TYPE_1001, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_8050),
                 drive_check_type(DRIVE_TYPE_8050, num - 8));
    EnableWindow(GetDlgItem(hwnd, IDC_SELECT_DRIVE_TYPE_8250),
                 drive_check_type(DRIVE_TYPE_8250, num - 8));

    resources_get_int_sprintf("Drive%dType", &drive_type, num);
    resources_get_int_sprintf("Drive%dExtendImagePolicy",
                              &drive_extend_image_policy, num);

    switch (drive_type) {
      case DRIVE_TYPE_NONE:
        n = IDC_SELECT_DRIVE_TYPE_NONE;
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

    CheckRadioButton(hwnd, IDC_SELECT_DRIVE_TYPE_2031,
                     IDC_SELECT_DRIVE_TYPE_NONE, n);

    enable_controls_for_drive_settings(hwnd, n);

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

    CheckRadioButton(hwnd, IDC_SELECT_DRIVE_EXTEND_NEVER,
                     IDC_SELECT_DRIVE_EXTEND_ACCESS, n);
}