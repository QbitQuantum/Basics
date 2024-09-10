int main() {
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	outtext("Welcome to the rail booking system\n");
	getch();
	setbkcolor(WHITE); 	/*Sets background colour to White*/
	setcolor(BLACK);   	/*Sets colour to Black*/
	getch();
	closegraph();
	return 0;
}