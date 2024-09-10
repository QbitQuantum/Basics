void script_debug(int cmdd,int dataa) {
    if (play.debug_mode==0) return;
    int rr;
    if (cmdd==0) {
        for (rr=1;rr<game.numinvitems;rr++)
            playerchar->inv[rr]=1;
        update_invorder();
        //    Display("invorder decided there are %d items[display %d",play.inv_numorder,play.inv_numdisp);
    }
    else if (cmdd==1) {
        char toDisplay[STD_BUFFER_SIZE];
        const char *filterName = filter->GetVersionBoxText();
        DisplayResolution mode = gfxDriver->GetResolution();
        sprintf(toDisplay,"Adventure Game Studio run-time engine[ACI version %s"
            "[Running %d x %d at %d-bit, game frame is %d x %d %s[GFX: %s[%s" "Sprite cache size: %d KB (limit %d KB; %d locked)",
            EngineVersion.LongString.GetCStr(), mode.Width, mode.Height, final_col_dep, final_scrn_wid, final_scrn_hit, (convert_16bit_bgr) ? "BGR" : "",
            gfxDriver->GetDriverName(), filterName,
            spriteset.cachesize / 1024, spriteset.maxCacheSize / 1024, spriteset.lockedSize / 1024);
        if (play.seperate_music_lib)
            strcat(toDisplay,"[AUDIO.VOX enabled");
        if (play.want_speech >= 1)
            strcat(toDisplay,"[SPEECH.VOX enabled");
        if (transtree != NULL) {
            strcat(toDisplay,"[Using translation ");
            strcat(toDisplay, transFileName);
        }
        if (opts.mod_player == 0)
            strcat(toDisplay,"[(mod/xm player discarded)");
        Display(toDisplay);
        //    Display("shftR: %d  shftG: %d  shftB: %d", _rgb_r_shift_16, _rgb_g_shift_16, _rgb_b_shift_16);
        //    Display("Remaining memory: %d kb",_go32_dpmi_remaining_virtual_memory()/1024);
        //Display("Play char bcd: %d",->GetColorDepth(spriteset[views[playerchar->view].frames[playerchar->loop][playerchar->frame].pic]));
    }
    else if (cmdd==2) 
    {  // show walkable areas from here
        Bitmap *tempw=BitmapHelper::CreateBitmap(thisroom.walls->GetWidth(),thisroom.walls->GetHeight());
        tempw->Blit(prepare_walkable_areas(-1),0,0,0,0,tempw->GetWidth(),tempw->GetHeight());
        Bitmap *stretched = BitmapHelper::CreateBitmap(scrnwid, scrnhit);
        stretched->StretchBlt(tempw,
			RectWH(-offsetx, -offsety, get_fixed_pixel_size(tempw->GetWidth()), get_fixed_pixel_size(tempw->GetHeight())),
			Common::kBitmap_Transparency);

        IDriverDependantBitmap *ddb = gfxDriver->CreateDDBFromBitmap(stretched, false, true);
        render_graphics(ddb, 0, 0);

        delete tempw;
        delete stretched;
        gfxDriver->DestroyDDB(ddb);
        while (!kbhit()) ;
        getch();
        invalidate_screen();
    }
    else if (cmdd==3) 
    {
        int goToRoom = -1;
        if (game.roomCount == 0)
        {
            char inroomtex[80];
            sprintf(inroomtex, "!Enter new room: (in room %d)", displayed_room);
            setup_for_dialog();
            goToRoom = enternumberwindow(inroomtex);
            restore_after_dialog();
        }
        else
        {
            setup_for_dialog();
            goToRoom = roomSelectorWindow(displayed_room, game.roomCount, game.roomNumbers, game.roomNames);
            restore_after_dialog();
        }
        if (goToRoom >= 0) 
            NewRoom(goToRoom);
    }
    else if (cmdd == 4) {
        if (display_fps != 2)
            display_fps = dataa;
    }
    else if (cmdd == 5) {
        if (dataa == 0) dataa = game.playercharacter;
        if (game.chars[dataa].walking < 1) {
            Display("Not currently moving.");
            return;
        }
        Bitmap *tempw=BitmapHelper::CreateTransparentBitmap(thisroom.walls->GetWidth(),thisroom.walls->GetHeight());
        int mlsnum = game.chars[dataa].walking;
        if (game.chars[dataa].walking >= TURNING_AROUND)
            mlsnum %= TURNING_AROUND;
        MoveList*cmls = &mls[mlsnum];
        for (int i = 0; i < cmls->numstage-1; i++) {
            short srcx=short((cmls->pos[i] >> 16) & 0x00ffff);
            short srcy=short(cmls->pos[i] & 0x00ffff);
            short targetx=short((cmls->pos[i+1] >> 16) & 0x00ffff);
            short targety=short(cmls->pos[i+1] & 0x00ffff);
            tempw->DrawLine(Line(srcx, srcy, targetx, targety), GetVirtualScreen()->GetCompatibleColor(i+1));
        }
		Bitmap *screen_bmp = BitmapHelper::GetScreenBitmap();
        screen_bmp->StretchBlt(tempw,
			RectWH(-offsetx, -offsety, multiply_up_coordinate(tempw->GetWidth()), multiply_up_coordinate(tempw->GetHeight())),
			Common::kBitmap_Transparency);
        render_to_screen(BitmapHelper::GetScreenBitmap(), 0, 0);
        delete tempw;
        while (!kbhit()) ;
        getch();
    }
    else if (cmdd == 99)