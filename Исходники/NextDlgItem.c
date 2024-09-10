static void
DoTest2(HWND hwnd)
{
    HWND hCtrl;
    HWND hRad1, hRad2, hRad3, hPsh1, hRad5, hRad6, hRad7, hOK, hCancel;

    // check control IDs
    hCtrl = GetDlgItem(hwnd, rad1);
    ok(GetDlgCtrlID(hCtrl) == rad1, "\n");
    hCtrl = GetDlgItem(hwnd, rad2);
    ok(GetDlgCtrlID(hCtrl) == rad2, "\n");
    hCtrl = GetDlgItem(hwnd, rad3);
    ok(GetDlgCtrlID(hCtrl) == rad3, "\n");
    hCtrl = GetDlgItem(hwnd, psh1);
    ok(GetDlgCtrlID(hCtrl) == psh1, "\n");
    hCtrl = GetDlgItem(hwnd, rad5);
    ok(GetDlgCtrlID(hCtrl) == rad5, "\n");
    hCtrl = GetDlgItem(hwnd, rad6);
    ok(GetDlgCtrlID(hCtrl) == rad6, "\n");
    hCtrl = GetDlgItem(hwnd, rad7);
    ok(GetDlgCtrlID(hCtrl) == rad7, "\n");
    hCtrl = GetDlgItem(hwnd, IDOK);
    ok(GetDlgCtrlID(hCtrl) == IDOK, "\n");
    hCtrl = GetDlgItem(hwnd, IDCANCEL);
    ok(GetDlgCtrlID(hCtrl) == IDCANCEL, "\n");

    // get dialog items
    hRad1 = GetDlgItem(hwnd, rad1);
    hRad2 = GetDlgItem(hwnd, rad2);
    hRad3 = GetDlgItem(hwnd, rad3);
    hPsh1 = GetDlgItem(hwnd, psh1);
    hRad5 = GetDlgItem(hwnd, rad5);
    hRad6 = GetDlgItem(hwnd, rad6);
    hRad7 = GetDlgItem(hwnd, rad7);
    hOK = GetDlgItem(hwnd, IDOK);
    hCancel = GetDlgItem(hwnd, IDCANCEL);

    // group next
    hCtrl = GetNextDlgGroupItem(hwnd, hRad1, FALSE);
    ok(hCtrl == hRad2, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad2, FALSE);
    ok(hCtrl == hRad3, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad3, FALSE);
    ok(hCtrl == hPsh1, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hPsh1, FALSE);
    ok(hCtrl == hRad5, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad5, FALSE);
    ok(hCtrl == hRad6, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad6, FALSE);
    ok(hCtrl == hRad7, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad7, FALSE);
    ok(hCtrl == hOK, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hOK, FALSE);
    ok(hCtrl == hCancel, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hCancel, FALSE);
    ok(hCtrl == hRad1, "hCtrl is %s\n", GetNameFromHWND(hCtrl));

    // group prev
    hCtrl = GetNextDlgGroupItem(hwnd, hRad1, TRUE);
    ok(hCtrl == hCancel, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad2, TRUE);
    ok(hCtrl == hRad1, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad3, TRUE);
    ok(hCtrl == hRad2, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hPsh1, TRUE);
    ok(hCtrl == hRad3, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad5, TRUE);
    ok(hCtrl == hPsh1, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad6, TRUE);
    ok(hCtrl == hRad5, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad7, TRUE);
    ok(hCtrl == hRad6, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hOK, TRUE);
    ok(hCtrl == hRad7, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hCancel, TRUE);
    ok(hCtrl == hOK, "hCtrl is %s\n", GetNameFromHWND(hCtrl));

    // hide
    ok(ShowWindow(hRad3, SW_HIDE) != 0, "\n");
    ok(ShowWindow(hRad6, SW_HIDE) != 0, "\n");

    // group next with hidden
    hCtrl = GetNextDlgGroupItem(hwnd, hRad1, FALSE);
    ok(hCtrl == hRad2, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad2, FALSE);
    ok(hCtrl == hPsh1, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hPsh1, FALSE);
    ok(hCtrl == hRad5, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad5, FALSE);
    ok(hCtrl == hRad7, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad7, FALSE);
    ok(hCtrl == hOK, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hOK, FALSE);
    ok(hCtrl == hCancel, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hCancel, FALSE);
    ok(hCtrl == hRad1, "hCtrl is %s\n", GetNameFromHWND(hCtrl));

    // group prev with hidden
    hCtrl = GetNextDlgGroupItem(hwnd, hRad1, TRUE);
    ok(hCtrl == hCancel, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad2, TRUE);
    ok(hCtrl == hRad1, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hPsh1, TRUE);
    ok(hCtrl == hRad2, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad5, TRUE);
    ok(hCtrl == hPsh1, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hRad7, TRUE);
    ok(hCtrl == hRad5, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hOK, TRUE);
    ok(hCtrl == hRad7, "hCtrl is %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgGroupItem(hwnd, hCancel, TRUE);
    ok(hCtrl == hOK, "hCtrl is %s\n", GetNameFromHWND(hCtrl));

    // show
    ShowWindow(hRad3, SW_SHOWNOACTIVATE);
    ShowWindow(hRad6, SW_SHOWNOACTIVATE);
}