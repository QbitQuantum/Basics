void R::esconder() {
    int t;
    t = getcolor();
    setcolor (getbkcolor() );
    rectangle (x1, y1, x2, y2);
    setcolor(t);
}