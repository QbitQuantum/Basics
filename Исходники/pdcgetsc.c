int PDC_get_cursor_mode(void)
{
    CONSOLE_CURSOR_INFO ci;
    
    PDC_LOG(("PDC_get_cursor_mode() - called\n"));

    GetConsoleCursorInfo(pdc_con_out, &ci);

    return ci.dwSize;
}