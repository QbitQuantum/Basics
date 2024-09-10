static void test_selection(DWORD style, const char * const text[],
                           const int *edit, const int *list)
{
    INT idx;
    HWND hCombo;

    hCombo = build_combo(style);

    SendMessageA(hCombo, CB_ADDSTRING, 0, (LPARAM)text[0]);
    SendMessageA(hCombo, CB_ADDSTRING, 0, (LPARAM)text[1]);
    SendMessageA(hCombo, CB_SETCURSEL, -1, 0);

    old_parent_proc = (void *)SetWindowLongPtrA(hMainWnd, GWLP_WNDPROC, (ULONG_PTR)parent_wnd_proc);

    idx = SendMessageA(hCombo, CB_GETCURSEL, 0, 0);
    ok(idx == -1, "expected selection -1, got %d\n", idx);

    /* keyboard navigation */

    expected_list_text = text[list[0]];
    expected_edit_text = text[edit[0]];
    selchange_fired = FALSE;
    SendMessageA(hCombo, WM_KEYDOWN, VK_DOWN, 0);
    ok(selchange_fired, "CBN_SELCHANGE not sent!\n");

    expected_list_text = text[list[1]];
    expected_edit_text = text[edit[1]];
    selchange_fired = FALSE;
    SendMessageA(hCombo, WM_KEYDOWN, VK_DOWN, 0);
    ok(selchange_fired, "CBN_SELCHANGE not sent!\n");

    expected_list_text = text[list[2]];
    expected_edit_text = text[edit[2]];
    selchange_fired = FALSE;
    SendMessageA(hCombo, WM_KEYDOWN, VK_UP, 0);
    ok(selchange_fired, "CBN_SELCHANGE not sent!\n");

    /* programmatic navigation */

    expected_list_text = text[list[3]];
    expected_edit_text = text[edit[3]];
    selchange_fired = FALSE;
    SendMessageA(hCombo, CB_SETCURSEL, list[3], 0);
    ok(!selchange_fired, "CBN_SELCHANGE sent!\n");

    expected_list_text = text[list[4]];
    expected_edit_text = text[edit[4]];
    selchange_fired = FALSE;
    SendMessageA(hCombo, CB_SETCURSEL, list[4], 0);
    ok(!selchange_fired, "CBN_SELCHANGE sent!\n");

    SetWindowLongPtrA(hMainWnd, GWLP_WNDPROC, (ULONG_PTR)old_parent_proc);
    DestroyWindow(hCombo);
}