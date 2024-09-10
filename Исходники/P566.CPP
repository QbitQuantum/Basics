void Ventana::Error(char *p) {
	setbkcolor(YELLOW);
	setcolor (BLACK);
	outtextxy(0,0,p);
	getch();
	closegraph();
	exit (1);
}