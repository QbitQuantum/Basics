static int  DIB_IsWinVisible(_THIS, int  recenter)
{
    VisibilityData  data;
    data.result = 0;
    data.first  = 1;
    
    GetWindowRect(SDL_Window, &data.wrect);

    EnumDisplayMonitors(NULL, NULL, visibility_cb, (LPARAM)&data);
    
    if ( !data.result && recenter ) {
        int  new_x = 10;
        int  new_y = 10;

        if ( !data.first ) {
            int  primary_w = data.primary.right  - data.primary.left;
            int  primary_h = data.primary.bottom - data.primary.top;

            new_x = data.primary.left + (primary_w - this->screen->w)/2;
            new_y = data.primary.top  + (primary_h - this->screen->h)/2;
        }
        DIB_SetWinPos(this, new_x, new_y);
    }
    return  data.result;
}