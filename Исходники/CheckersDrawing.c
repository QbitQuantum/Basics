void createWindow(char* windowName, int boardSize, MouseListener l) {
    int windowSize = 2*BOARD_PADDING + boardSize * TILE_SIZE;
    initwindow(windowSize, windowSize, windowName);
    setbkcolor(LIGHTGRAY);
    clearScreen();
    swapBuffers();

    mouseClickListener.l = l;

    // register mouse listeners
    registermousehandler(WM_LBUTTONDOWN, mouseDown);
    registermousehandler(WM_LBUTTONUP, mouseUp);
    registermousehandler(WM_MOUSEMOVE, mouseMove);
}