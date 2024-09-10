static void
prepare_context_menu(HMENU hmenu)
{
    khm_int32 cmd;
    wchar_t caption[128];

    cmd = get_default_notifier_action();

    if (cmd == KHUI_ACTION_NEW_CRED)
        LoadString(hResModule, IDS_ACT_NEW, caption, ARRAYLENGTH(caption));
    else
        LoadString(hResModule, IDS_ACT_OPEN, caption, ARRAYLENGTH(caption));

    ModifyMenu(hmenu, ID_DEFAULT, MF_STRING|MF_BYCOMMAND, ID_DEFAULT, caption);
    SetMenuDefaultItem(hmenu, ID_DEFAULT, FALSE);
}