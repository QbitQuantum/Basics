int isTitlebarHit(Display *dsp, mousestate *mousepos){
    int titlebarHeight, x, y, junkx, junky;
    unsigned int wi,h, junkwi, junkh;
    Window activeWindow, parentWin;
    getFocusedWindow(dsp,&activeWindow);
    findParentWindow(dsp,&activeWindow,&parentWin);
    getNetFrameExtents(dsp,&parentWin,&titlebarHeight);
    getWindowRect(dsp, &parentWin, &junkx, &junky, &wi, &h);
    getWindowRect(dsp, &activeWindow, &x, &y, &junkwi, &junkh); // we need the size of the parent win, but the x/y coordinates of the child, don't ask me why, otherwise the values are off a bit
    if(y==junky){
        y-=titlebarHeight; //Qt hack
    }
    if(mousepos->x>=x && mousepos->x <= (x+(int)wi) &&
            mousepos->y >= (y-titlebarHeight) && mousepos->y <= y){
        return 1;
    }
    return 0;
}