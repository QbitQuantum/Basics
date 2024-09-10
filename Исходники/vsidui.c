static void vsid_ui_translate(void)
{
    menu = LoadMenu(winmain_instance, MAKEINTRESOURCE(IDR_MENUVSID));
    ui_translate_menu_items(menu, vsidui_menu_translation_table);
    ui_translate_menu_popups(menu, vsidui_popup_translation_table);
    SetMenu(hwnd, menu);
}