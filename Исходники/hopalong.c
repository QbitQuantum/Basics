int main (int argc, char **argv)
{
  int gd, gm;
  int col;
  unsigned int seed;
  long int counter;
  float j, k, x, y, xx, xp, yp, r, xoffs, yoffs;
  
  if (argc == 2)
    seed = atoi (argv [1]); /* no checks! */
  else {  
    printf ("Seed: ");
    j = scanf ("%d", &seed);
  }
  srand (seed);
  // random each time:
  // srand (time(NULL));
  
  gd = X11;
  gm = getmaxmode ();
  initgraph(&gd, &gm, "");
  
  setbkcolor (BLACK);
  cleardevice ();
  setcolor (YELLOW);
  outtextxy (0, 0, "Press a key or click to exit: ");
  
  xoffs = getmaxx () / 2;
  yoffs = getmaxy () / 3;
  j = random (100);
  k = random (100);
  x = y = xx = xp = yp = r = 0.0;
  col = 1; /* colours codes run from 0 (black) to 15 (white) */
  counter = 0;
  setcolor (col);

  while (!kbhit () && !mouseclick ()) {
    xx = y - sgn (x) * sqrt (abs (k * x - 1));
    y = j - x;
    x = xx;
    xp = x * 2 + xoffs;
    yp = y * 2 + yoffs;
    _putpixel (xp, yp);
    if (++counter == 20000) {
      counter = 0;
      col++;
      if (col == 16)
	col = 1;
    }
    setcolor (col);
  }
   
  closegraph ();
  return 0;
}