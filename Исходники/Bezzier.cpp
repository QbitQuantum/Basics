int main()
{
    int x[3], y[3];
    int i;
    Screen screen;
    printf ("Enter the x- and y-coordinates of the four control points.\n");
    for (i=0; i<3; i++)
	  scanf ("%d%d", &x[i], &y[i]);
    screen.init();
    bezier (screen, x, y);
    screen.terminate();
    return 0;
}