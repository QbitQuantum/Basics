void init(int* gd, int* gm) {
  initgraph(gd, gm, "c:\\tc\\bgi");
  clrscr();
  max.x = getmaxx(); max.y = getmaxy();
  origin.x = max.x/2; origin.y = max.y/2;
  setbkcolor(BLUE); setcolor(CYAN);
  line(0,origin.y, max.x,origin.y);
  line(origin.x,0, origin.x,max.y);
  setcolor(RED);
}