void main()
{   int gdriver = DETECT, gmode, errorcode;
    initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");
    intro();
    levelmenu();
    clrscr();
    cleardevice();
    setbkcolor(RED);
    easy();
}