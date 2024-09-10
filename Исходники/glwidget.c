static void drawbutton(gl_button *bt) {
    Int32 lw = getlwidth();
    Int32 cl = getcolor();
    Int32 oriwin = winget();
    int cfg, bg;
    
    winset(bt->win);
    linewidth(1);
    locate_button(bt);
    
    cfg = *(bt->state)?bt->bg:bt->fg;
    bg  = *(bt->state)?((bt->type == BUTTON)?bt->fg:bt->active_c):bt->bg;
	
    color(bg);
    rectf(bt->x, bt->y, bt->x + bt->width, bt->y + bt->height);
    
    color(bt->fg);
    rect (bt->x, bt->y, bt->x + bt->width, bt->y + bt->height);

    if (bt->label != NULL) {
	color(cfg);
	cmov2(bt->x, bt->y + 0.05 * bt->height);
	charstr(bt->label);
    }
    
    winset(oriwin);
    color(cl);
    linewidth(lw);
    
    sleep(0);
}