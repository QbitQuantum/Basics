static void printBoxes(FILE *f)
{
    for (int i = 0; i<10; i++) {
        startLayer(f);
        for (double x=-45; x<45; x+=20) {
            for (double y=-45; y<45; y+=20) {
                rectf(f, x, y, 10.0, 10.0);
            }
        }
        endLayer(f);
    }
}