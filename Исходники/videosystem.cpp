void VideoSystem::drawGrid() {
    int xstart = 16 - g_Camera->x() % 16;
    for (int i = 0; i < GetW()/16; i++) {
        SDL_Rect r;
        r.x = xstart + i * 16;
        r.y = 0;
        r.w = 1;
        r.h = GetH();
        SDL_FillRect(screen, &r, Color(255,0,0));
    }
    for (int i = 0; i < GetH()/16; i++) {
        SDL_Rect r;
        r.x = 0;
        r.y = i*16;
        r.w = GetW();
        r.h = 1;
        SDL_FillRect(screen, &r, Color(255,0,0));
    }
}