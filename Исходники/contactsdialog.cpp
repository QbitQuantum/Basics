void ShowContactsDialog(BOOL *negated, BOOL *set1, char *name)
{
    BOOL set1Save = *set1;
    char nameSave[MAX_NAME_LEN];
    strcpy(nameSave, name);

    ContactsDialog = CreateWindowClient(0, "LDmicroDialog",
        _("Contacts"), WS_OVERLAPPED | WS_SYSMENU,
        100, 100, 404, 135, NULL, NULL, Instance, NULL);

    MakeControls();

    switch (name[0]) {
    case 'R':
        SendMessage(SourceInternalRelayRadio, BM_SETCHECK, BST_CHECKED, 0);
        break;
    case 'Y':
        SendMessage(SourceOutputPinRadio, BM_SETCHECK, BST_CHECKED, 0);
        break;
    case 'X':
        SendMessage(SourceInputPinRadio, BM_SETCHECK, BST_CHECKED, 0);
        break;
    case 'I':
        SendMessage(SourceModbusContactRadio, BM_SETCHECK, BST_CHECKED, 0);
        break;
    case 'M':
        SendMessage(SourceModbusCoilRadio, BM_SETCHECK, BST_CHECKED, 0);
        break;
    default:
        oops();
        break;
    }

    if(*negated) {
        SendMessage(NegatedCheckbox, BM_SETCHECK, BST_CHECKED, 0);
    }

    if(*set1) {
        SendMessage(Set1Checkbox, BM_SETCHECK, BST_CHECKED, 0);
    }
    EnableWindow(Set1Checkbox, SendMessage(SourceInputPinRadio, BM_GETSTATE, 0, 0) & BST_CHECKED);

    SendMessage(NameTextbox, WM_SETTEXT, 0, (LPARAM)(name + 1));

    EnableWindow(MainWindow, FALSE);
    ShowWindow(ContactsDialog, TRUE);
    SetFocus(NameTextbox);
    SendMessage(NameTextbox, EM_SETSEL, 0, -1);

    MSG msg;
    DWORD ret;
    DialogDone = FALSE;
    DialogCancel = FALSE;
    while((ret = GetMessage(&msg, NULL, 0, 0)) && !DialogDone) {
        if(msg.message == WM_KEYDOWN) {
            if(msg.wParam == VK_RETURN) {
                DialogDone = TRUE;
                break;
            } else if(msg.wParam == VK_ESCAPE) {
                DialogDone = TRUE;
                DialogCancel = TRUE;
                break;
            }
        }

        EnableWindow(Set1Checkbox, SendMessage(SourceInputPinRadio, BM_GETSTATE, 0, 0) & BST_CHECKED);

        if(IsDialogMessage(ContactsDialog, &msg)) continue;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if(!DialogCancel) {
        if(SendMessage(NegatedCheckbox, BM_GETSTATE, 0, 0) & BST_CHECKED) {
            *negated = TRUE;
        } else {
            *negated = FALSE;
        }
        if(SendMessage(SourceInternalRelayRadio, BM_GETSTATE, 0, 0)
            & BST_CHECKED)
        {
            name[0] = 'R';
        } else if(SendMessage(SourceInputPinRadio, BM_GETSTATE, 0, 0)
            & BST_CHECKED)
        {
            name[0] = 'X';
        } else if (SendMessage(SourceModbusContactRadio, BM_GETSTATE, 0, 0)
            & BST_CHECKED)
        {
            name[0] = 'I';
        } else if (SendMessage(SourceModbusCoilRadio, BM_GETSTATE, 0, 0)
            & BST_CHECKED)
        {
            name[0] = 'M';
        } else {
            name[0] = 'Y';
        }
        SendMessage(NameTextbox, WM_GETTEXT, (WPARAM)(MAX_NAME_LEN-1), (LPARAM)(name+1));

        if(SendMessage(Set1Checkbox, BM_GETSTATE, 0, 0) & BST_CHECKED) {
            *set1 = TRUE;
        } else {
            *set1 = FALSE;
        }

        if((*set1 != set1Save) || strcmp(name, nameSave)) {
          int n = CountWhich(ELEM_CONTACTS, ELEM_COIL, nameSave);
          if(n >= 1) {
            BOOL rename = FALSE;
            if(strcmp(name, nameSave)) {
                char str[1000];
                sprintf(str, _("Rename the ALL other %d contacts/coils named '%s' to '%s' ?"), n, nameSave, name);
                rename = IDYES == MessageBox(MainWindow,
                               str, "LDmicro",
                               MB_YESNO | MB_ICONQUESTION);
            }
            if(rename)
                if(name[0] == 'X')
                    RenameSet1(ELEM_CONTACTS, nameSave, name, *set1); // rename and set as set1
                else
                    RenameSet1(ELEM_CONTACTS, nameSave, name, FALSE); // rename and reset
            else
                if(name[0] == 'X')
                    RenameSet1(ELEM_CONTACTS, name, NULL, *set1); // set as set1
                else
                    RenameSet1(ELEM_CONTACTS, name, NULL, FALSE); // reset
          }
        }

    }

    EnableWindow(MainWindow, TRUE);
    DestroyWindow(ContactsDialog);
    return;
}