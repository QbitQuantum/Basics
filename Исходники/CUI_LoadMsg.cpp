void CUI_LoadMsg::leave(void) {
    FileList *fl;
    SetThreadPriority(GetCurrentThread(),OldPriority);
    KillTimer(NULL,strtimer);
    CloseHandle(hThread);
//    setWindowTitle("zt");
    SDL_WM_SetCaption("zt","zt");
    fl = (FileList *)UIP_Savescreen->UI->get_element(0);
//    fl->set_cursor(load_filename);
    fl->setCursor(fl->findItem(load_filename));
    need_refresh++;
}