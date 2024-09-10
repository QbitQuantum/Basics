void initgrph(int showtitle) {
    int i;
    FILE *f;
    char *pigname;
    struct ws_event ws;
    struct ws_bitmap *cursor;


    inittimer();
   #if defined (GNU_C) && defined (GO32)

        if ( showtitle &&
            ws_initgrfx(640, 480, 256, init.fontname) && titlescreen() ) {
            ws_getevent(&ws, 1);
        }

        ws_textmode();
   #endif

    if ( !w_initwins(init.xres, init.yres, 256, init.fontname) ) {
        printf(TXT_CANTINITWINS);
        my_exit();
    }

    if ( ( f = fopen(init.menuname, "r") ) == NULL ) {
        fprintf(errf, TXT_NOMENUFILE, init.menuname);
        my_exit();
    }

    my_assert( w_initmenu(f, do_event, ec_num_of_codes) );
    fclose(f);
    pigname = pig.current_pigname;
    pig.current_pigname = NULL;
    newpigfile(pigname, NULL);
    FREE(pigname);
    /* draw the cursors (init the cursor data) */
    cntrlcursor_ysize = altcursor_ysize = w_titlebarheight();
    cntrlcursor_xsize = (ws_pixstrlen(TXT_TAG) + 2 + 3) / 4 * 4;
    altcursor_xsize = (ws_pixstrlen(TXT_INFO) + 2 + 3) / 4 * 4;
    cursor = ws_createbitmap(cntrlcursor_xsize, cntrlcursor_ysize,
                             control_cursor);
    ws_bmdrawtext(cursor, 1, 0, cntrlcursor_xsize, TXT_TAG, 1, 0);
    ws_freebitmap(cursor);
    cursor = ws_createbitmap(altcursor_xsize, altcursor_ysize, alt_cursor);
    ws_bmdrawtext(cursor, 1, 0, altcursor_xsize, TXT_INFO, 1, 0);
    ws_freebitmap(cursor);
    cursor_initialized = 1;
    checkmem( pig.txt_buffer = MALLOC(64 * 64) );
    memset(pig.txt_buffer, 0, 64 * 64);
    pig.txt_bm = ws_createbitmap(64, 64, pig.txt_buffer);
    checkmem( pig.door_buffer = MALLOC(64 * 64) );
    memset(pig.door_buffer, 0, 64 * 64);
    pig.door_bm = ws_createbitmap(64, 64, pig.door_buffer);
    checkmem( pig.thing_buffer = MALLOC(64 * 64) );
    memset(pig.thing_buffer, 0, 64 * 64);
    pig.thing_bm = ws_createbitmap(64, 64, pig.thing_buffer);
    button_win.xpos = w_xmaxwinsize() - button_win.xsize - 10;
    button_win.ypos = w_ymaxwinsize() - button_win.ysize - 10;

    if (init.d_ver >= d2_10_reg) {
        button_win.ypos -= 20;
        button_win.ysize += 20;

        if (init.d_ver >= d2_12_reg) {
            button_win.ypos -= 16;
        }

        button_win.ysize += 16;
    }

    checkmem( view.movewindow = w_openwindow(&button_win) );
    drawallbuttons(view.movewindow);

    for (i = 0; i <= in_internal; i++) {
        makeoptwindow(i);
    }

    init_txtgrfx();
    read_lightsources();
}