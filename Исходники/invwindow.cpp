int __actual_invscreen() {

    int BUTTONAREAHEIGHT = get_fixed_pixel_size(30);
    int cmode=CURS_ARROW, toret = -1;
    int top_item = 0, num_visible_items = 0;
    int MAX_ITEMAREA_HEIGHT = ((scrnhit - BUTTONAREAHEIGHT) - get_fixed_pixel_size(20));
    in_inv_screen++;
    inv_screen_newroom = -1;
    Bitmap *ds = NULL;

start_actinv:
    ds = SetVirtualScreen(virtual_screen);

    DisplayInvItem dii[MAX_INV];
    int numitems=0,ww,widest=0,highest=0;
    if (charextra[game.playercharacter].invorder_count < 0)
        update_invorder();
    if (charextra[game.playercharacter].invorder_count == 0) {
        DisplayMessage(996);
        in_inv_screen--;
        return -1;
    }

    if (inv_screen_newroom >= 0) {
        in_inv_screen--;
        NewRoom(inv_screen_newroom);
        return -1;
    }

    for (ww = 0; ww < charextra[game.playercharacter].invorder_count; ww++) {
        if (game.invinfo[charextra[game.playercharacter].invorder[ww]].name[0]!=0) {
            dii[numitems].num = charextra[game.playercharacter].invorder[ww];
            dii[numitems].sprnum = game.invinfo[charextra[game.playercharacter].invorder[ww]].pic;
            int snn=dii[numitems].sprnum;
            if (spritewidth[snn] > widest) widest=spritewidth[snn];
            if (spriteheight[snn] > highest) highest=spriteheight[snn];
            numitems++;
        }
    }
    if (numitems != charextra[game.playercharacter].invorder_count)
        quit("inconsistent inventory calculations");

    widest += get_fixed_pixel_size(4);
    highest += get_fixed_pixel_size(4);
    num_visible_items = (MAX_ITEMAREA_HEIGHT / highest) * ICONSPERLINE;

    int windowhit = highest * (numitems/ICONSPERLINE) + get_fixed_pixel_size(4);
    if ((numitems%ICONSPERLINE) !=0) windowhit+=highest;
    if (windowhit > MAX_ITEMAREA_HEIGHT) {
        windowhit = (MAX_ITEMAREA_HEIGHT / highest) * highest + get_fixed_pixel_size(4);
    }
    windowhit += BUTTONAREAHEIGHT;

    int windowwid = widest*ICONSPERLINE + get_fixed_pixel_size(4);
    if (windowwid < get_fixed_pixel_size(105)) windowwid = get_fixed_pixel_size(105);
    int windowxp=scrnwid/2-windowwid/2;
    int windowyp=scrnhit/2-windowhit/2;
    int buttonyp=windowyp+windowhit-BUTTONAREAHEIGHT;
    color_t draw_color = ds->GetCompatibleColor(play.sierra_inv_color);
    ds->FillRect(Rect(windowxp,windowyp,windowxp+windowwid,windowyp+windowhit), draw_color);
    draw_color = ds->GetCompatibleColor(0); 
    int bartop = windowyp + get_fixed_pixel_size(2);
    int barxp = windowxp + get_fixed_pixel_size(2);
    ds->FillRect(Rect(barxp,bartop, windowxp + windowwid - get_fixed_pixel_size(2),buttonyp-1), draw_color);
    for (ww = top_item; ww < numitems; ww++) {
        if (ww >= top_item + num_visible_items)
            break;
        Bitmap *spof=spriteset[dii[ww].sprnum];
        wputblock(ds, barxp+1+((ww-top_item)%4)*widest+widest/2-spof->GetWidth()/2,
            bartop+1+((ww-top_item)/4)*highest+highest/2-spof->GetHeight()/2,spof,1);
    }
    if ((spriteset[2041] == NULL) || (spriteset[2042] == NULL) || (spriteset[2043] == NULL))
        quit("!InventoryScreen: one or more of the inventory screen graphics have been deleted");
#define BUTTONWID spritewidth[2042]
    // Draw select, look and OK buttons
    wputblock(ds, windowxp+2, buttonyp + get_fixed_pixel_size(2), spriteset[2041], 1);
    wputblock(ds, windowxp+3+BUTTONWID, buttonyp + get_fixed_pixel_size(2), spriteset[2042], 1);
    wputblock(ds, windowxp+4+BUTTONWID*2, buttonyp + get_fixed_pixel_size(2), spriteset[2043], 1);

    // Draw Up and Down buttons if required
    const int ARROWBUTTONWID = 11;
    Bitmap *arrowblock = BitmapHelper::CreateTransparentBitmap (ARROWBUTTONWID, ARROWBUTTONWID);
    draw_color = arrowblock->GetCompatibleColor(0);
    if (play.sierra_inv_color == 0)
        draw_color = ds->GetCompatibleColor(14);

    arrowblock->DrawLine(Line(ARROWBUTTONWID/2, 2, ARROWBUTTONWID-2, 9), draw_color);
    arrowblock->DrawLine(Line(ARROWBUTTONWID/2, 2, 2, 9), draw_color);
    arrowblock->DrawLine(Line(2, 9, ARROWBUTTONWID-2, 9), draw_color);
	arrowblock->FloodFill(ARROWBUTTONWID/2, 4, draw_color);

    if (top_item > 0)
        wputblock(ds, windowxp+windowwid-ARROWBUTTONWID, buttonyp + get_fixed_pixel_size(2), arrowblock, 1);
    if (top_item + num_visible_items < numitems)
        arrowblock->FlipBlt(arrowblock, windowxp+windowwid-ARROWBUTTONWID, buttonyp + get_fixed_pixel_size(4) + ARROWBUTTONWID, Common::kBitmap_VFlip);
    delete arrowblock;

    domouse(1);
    set_mouse_cursor(cmode);
    int wasonitem=-1;
    while (!kbhit()) {
        timerloop = 0;
        NEXT_ITERATION();
        domouse(0);
        update_polled_stuff_and_crossfade();
        write_screen();

        int isonitem=((mousey-bartop)/highest)*ICONSPERLINE+(mousex-barxp)/widest;
        if (mousey<=bartop) isonitem=-1;
        else if (isonitem >= 0) isonitem += top_item;
        if ((isonitem<0) | (isonitem>=numitems) | (isonitem >= top_item + num_visible_items))
            isonitem=-1;

        int mclick = mgetbutton();
        if (mclick == LEFT) {
            if ((mousey<windowyp) | (mousey>windowyp+windowhit) | (mousex<windowxp) | (mousex>windowxp+windowwid))
                continue;
            if (mousey<buttonyp) {
                int clickedon=isonitem;
                if (clickedon<0) continue;
                evblocknum=dii[clickedon].num;
                play.used_inv_on = dii[clickedon].num;

                if (cmode==MODE_LOOK) {
                    domouse(2);
                    run_event_block_inv(dii[clickedon].num, 0); 
                    // in case the script did anything to the screen, redraw it
                    mainloop();

                    goto start_actinv;
                    continue;
                }
                else if (cmode==MODE_USE) {
                    // use objects on each other
                    play.usedinv=toret;

                    // set the activeinv so the script can check it
                    int activeinvwas = playerchar->activeinv;
                    playerchar->activeinv = toret;

                    domouse(2);
                    run_event_block_inv(dii[clickedon].num, 3);

                    // if the script didn't change it, then put it back
                    if (playerchar->activeinv == toret)
                        playerchar->activeinv = activeinvwas;

                    // in case the script did anything to the screen, redraw it
                    mainloop();

                    // They used the active item and lost it
                    if (playerchar->inv[toret] < 1) {
                        cmode = CURS_ARROW;
                        set_mouse_cursor(cmode);
                        toret = -1;
                    }

                    goto start_actinv;
                    //          continue;
                }
                toret=dii[clickedon].num;
                //        int plusng=play.using; play.using=toret;
                update_inv_cursor(toret);
                set_mouse_cursor(MODE_USE);
                cmode=MODE_USE;
                //        play.using=plusng;
                //        break;
                continue;
            }
            else {
                if (mousex >= windowxp+windowwid-ARROWBUTTONWID) {
                    if (mousey < buttonyp + get_fixed_pixel_size(2) + ARROWBUTTONWID) {
                        if (top_item > 0) {
                            top_item -= ICONSPERLINE;
                            domouse(2);
                            goto start_actinv;
                        }
                    }
                    else if ((mousey < buttonyp + get_fixed_pixel_size(4) + ARROWBUTTONWID*2) && (top_item + num_visible_items < numitems)) {
                        top_item += ICONSPERLINE;
                        domouse(2);
                        goto start_actinv;
                    }
                    continue;
                }

                int buton=(mousex-windowxp)-2;
                if (buton<0) continue;
                buton/=BUTTONWID;
                if (buton>=3) continue;
                if (buton==0) { toret=-1; cmode=MODE_LOOK; }
                else if (buton==1) { cmode=CURS_ARROW; toret=-1; }
                else break;
                set_mouse_cursor(cmode);
            }
        }
        else if (mclick == RIGHT) {
            if (cmode == CURS_ARROW)
                cmode = MODE_LOOK;
            else
                cmode = CURS_ARROW;
            toret = -1;
            set_mouse_cursor(cmode);
        }
        else if (isonitem!=wasonitem) { domouse(2);
        int rectxp=barxp+1+(wasonitem%4)*widest;
        int rectyp=bartop+1+((wasonitem - top_item)/4)*highest;
        if (wasonitem>=0) {
            draw_color = ds->GetCompatibleColor(0);
            ds->DrawRect(Rect(rectxp,rectyp,rectxp+widest-1,rectyp+highest-1), draw_color);
        }
        if (isonitem>=0) { draw_color = ds->GetCompatibleColor(14);//opts.invrectcol);
        rectxp=barxp+1+(isonitem%4)*widest;
        rectyp=bartop+1+((isonitem - top_item)/4)*highest;
        ds->DrawRect(Rect(rectxp,rectyp,rectxp+widest-1,rectyp+highest-1), draw_color);
        }
        domouse(1);
        }
        wasonitem=isonitem;
        while (timerloop == 0) {
            update_polled_stuff_if_runtime();
            platform->YieldCPU();
        }
    }
    while (kbhit()) getch();
    set_default_cursor();
    domouse(2);
    construct_virtual_screen(true);
    in_inv_screen--;
    return toret;
}