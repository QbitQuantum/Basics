int CALLBACK
WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR command_line, int show_code)
{
    static Bank s_stack = {0};
    static Bank s_storage = {0};
    static Core s_core = {0};
    static Bitmap s_canvas = {0};
    WNDCLASSA window_class = {0};
    u32 *window_buffer = NULL;
    BITMAPINFO window_bmi = {0};


    if (align_to(CANVAS_WIDTH, 16) != CANVAS_WIDTH) {
        printf("CANVAS_WIDTH must be aligned to 16.\n");
        return 1;
    }


    CORE = &s_core;
    CORE->running = 1;
    CORE->stack = &s_stack;
    CORE->storage = &s_storage;

    bank_init(CORE->stack, STACK_CAPACITY);
    bank_init(CORE->storage, STORAGE_CAPACITY);

    // TODO: Push canvas to storage? Storage is not initialized yet, so we cannot push it there.
    CORE->canvas = &s_canvas;
    bitmap_init(CORE->canvas, CANVAS_WIDTH, CANVAS_HEIGHT, 0, 0);
    bitmap_clear(CORE->canvas, COLOR_TRANSPARENT);

    clip_reset();

    CORE->audio_volume = PUNP_SOUND_DEFAULT_MASTER_VOLUME;

    //
    //
    //

    punp_win32_instance = instance;
    QueryPerformanceFrequency((LARGE_INTEGER *)&punp_win32_perf_counter_frequency);

    // b32 sleep_is_granular = (timeBeginPeriod(1 /*ms*/) == TIMERR_NOERROR);

#ifndef RELEASE_BUILD
    printf("Debug build...");
    if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
#else
    printf("Release build...");
#endif

    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc = win32_window_callback;
    window_class.hInstance = punp_win32_instance;
    // window_class.hIcon = (HICON)LoadImage(0, "icon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
    window_class.hIcon = (HICON)LoadIcon(instance, "icon.ico");
    window_class.hCursor = LoadCursor(0, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    window_class.lpszClassName = "Punity";

    if (!RegisterClassA(&window_class)) {
        printf("RegisterClassA failed.\n");
        return 1;
    }

    {
        int screen_width = GetSystemMetrics(SM_CXSCREEN);
        int screen_height = GetSystemMetrics(SM_CYSCREEN);
        RECT rc;
        DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

        rc.left = (screen_width - (PUNP_WINDOW_WIDTH)) / 2;
        rc.top = (screen_height - (PUNP_WINDOW_HEIGHT)) / 2;
        rc.right = rc.left + PUNP_WINDOW_WIDTH;
        rc.bottom = rc.top + PUNP_WINDOW_HEIGHT;


        ASSERT(AdjustWindowRect(&rc, style, FALSE) != 0);

        // int window_width  = rc.right - rc.left;
        // int window_height = rc.bottom - rc.top;
        // rc.left = (screen_width  - width) / 2;
        // rc.top  = (screen_height - height) / 2;

        punp_win32_window = CreateWindowExA(
                0,
                window_class.lpszClassName,
                WINDOW_TITLE,
                style,
                rc.left, rc.top,
                rc.right - rc.left, rc.bottom - rc.top,
                0, 0,
                punp_win32_instance,
                0);
    }
    if (!punp_win32_window) {
        printf("CreateWindowExA failed.\n");
        return 1;
    }

    // Canvas
    window_bmi.bmiHeader.biSize = sizeof(window_bmi.bmiHeader);
    window_bmi.bmiHeader.biWidth = CANVAS_WIDTH;
    window_bmi.bmiHeader.biHeight = CANVAS_HEIGHT;
    window_bmi.bmiHeader.biPlanes = 1;
    window_bmi.bmiHeader.biBitCount = 32;
    window_bmi.bmiHeader.biCompression = BI_RGB;

    window_buffer = (u32 *)bank_push(CORE->stack, (CANVAS_WIDTH * 4) * CANVAS_HEIGHT);
    ASSERT(window_buffer);

    // Sound

    if (punp_win32_sound_init() == 0) {
        punp_win32_audio_buffer = 0;
    }


    init();


    // TODO: Center window
    ShowWindow(punp_win32_window, SW_SHOW);

    {
        f64 frame_time_stamp, frame_time_now, frame_time_delta;
        int x, y;
        u32 *window_row;
        u8 *canvas_it;
        MSG message;
        perf_from(&CORE->perf_frame);
        while (CORE->running) {
            perf_to(&CORE->perf_frame);
            perf_from(&CORE->perf_frame_inner);

            memset(&CORE->key_deltas, 0, KEYS_MAX);

            while (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
                if (message.message == WM_QUIT) {
                    CORE->running = 0;
                }

                TranslateMessage(&message);
                DispatchMessageA(&message);
            }

            perf_from(&CORE->perf_step);
            step();
            perf_to(&CORE->perf_step);

            perf_from(&CORE->perf_audio);
            if (punp_win32_audio_buffer) {
                punp_win32_sound_step();
            }
            perf_to(&CORE->perf_audio);

            perf_from(&CORE->perf_blit);
            perf_from(&CORE->perf_blit_cvt);
            canvas_it = CORE->canvas->pixels;
            for (y = CANVAS_HEIGHT; y != 0; --y) {
                window_row = window_buffer + ((y - 1) * CANVAS_WIDTH);
                for (x = 0; x != CANVAS_WIDTH; ++x) {
                    *(window_row++) = CORE->palette.colors[*canvas_it++].rgba;
                }
            }
            perf_to(&CORE->perf_blit_cvt);

            perf_from(&CORE->perf_blit_gdi);
            {
                HDC dc = GetDC(punp_win32_window);
        #if 1
                // TODO: This is sadly slow (50us on my machine), need to find a faster way to do this.
                StretchDIBits(dc,
                              0, 0, CANVAS_WIDTH * CANVAS_SCALE, CANVAS_HEIGHT * CANVAS_SCALE,
                              0, 0, CANVAS_WIDTH, CANVAS_HEIGHT,
                              window_buffer,
                              &window_bmi,
                              DIB_RGB_COLORS,
                              SRCCOPY);
        #else
        #endif
                ReleaseDC(punp_win32_window, dc);
            }
            perf_to(&CORE->perf_blit_gdi);
            perf_to(&CORE->perf_blit);

            perf_to(&CORE->perf_frame_inner);

            {
                f32 frame_delta = perf_delta(&CORE->perf_frame);
                if (frame_delta < PUNP_FRAME_TIME) {
                    // printf("sleeping ... %.3f\n", (f32)PUNP_FRAME_TIME - frame_delta);
                    Sleep((PUNP_FRAME_TIME - frame_delta) * 1e3);
                }
            }
            CORE->frame++;

    #if 0
            printf("stack %d storage %d\n",
                   CORE->stack->it - CORE->stack->begin,
                   CORE->storage->it - CORE->storage->begin);
    #endif
        }
    }

#if PUNP_SOUND_DEBUG_FILE
    fclose(punp_audio_buf_file);
#endif

    return 0;
}