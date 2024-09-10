main()
{
	int driver = DETECT, mode;
	initgraph(&driver, &mode, "");
	setbkcolor(BLUE);
	setcolor(WHITE);
	move();
	getch();
	closegraph();
}