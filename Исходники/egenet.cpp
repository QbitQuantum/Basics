int main(int argc, char* argv[]) {
    char str[100] = "";
    int basepoint = 20;
    /*
    if (argc < 2) return 0;
    if (stricmp(argv[1], "/p") == 0)
    {
        HWND hwnd;
        sscanf(argv[2], "%d", &hwnd);
        attachHWND(hwnd);
    }
    else if (stricmp(argv[1], "/s")) return 0;//*/

    init();
    init_net(&g_net, basepoint * 4, basepoint * 3, g_width, g_height);
    setbkmode(TRANSPARENT);

    fps fps_obj;
    setrendermode(RENDER_MANUAL);
    for (; kbhit() == 0; delay_fps(60)) {
        cleardevice();
        setcolor(0x8000);
        draw_net(&g_net);

        setcolor(0xFFFFFF);
        outtextxy(0,0,str);

        move_net(&g_net);
        move_net(&g_net);
        {
            int x, y, k;
            getmouse(&x, &y, &k);
            if (k) {
                cap_pt(&g_net, x, y, 1);
            } else {
                cap_pt(&g_net, x, y, 0);
            }
        }
    }
    closegraph();
    return 0;
}