//游戏初始化
void gameInit()
{
    initgraph(LENGTH, WIDTH);
    setcolor(FGCLR);
    setbkcolor(BKCLR);
    setfillstyle(FGCLR, SOLID_FILL);
    BeginBatchDraw();
    setfont(25, 0, "华文行楷");
    setbkmode(TRANSPARENT);
    cleardevice();
    loadimage(&bkImg, BKIMG, LENGTH, WIDTH);
    putimage(0, 0, &bkImg);
    srand((unsigned)time(NULL));//初始化种子
    setPlayer(1, "player1", 0, createPt(160, 0), createBlk(), true, createPt(10, 10));
    setPlayer(2, "player2", 0, createPt(400, 0), createBlk(), true, createPt(10, 240));
    drawStageLine();
}