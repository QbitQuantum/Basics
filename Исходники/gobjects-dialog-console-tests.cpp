void test_add_remove_torture() {
    int width = gw->getCanvasWidth();
    int height = gw->getCanvasHeight();
    int numEachObj = 100;
    Vector<GObject *> objs;
    Vector<GObject *> added;
    for (int i = 0; i<numEachObj; i++) {
        int x = randomInteger(0, width);
        int y = randomInteger(0, height);
        int w = randomInteger(1, width/2);
        int h = randomInteger(1, width/2);
        GRect *r = new GRect(x, y, w, h);
        r->setLineWidth(2);
        r->setColor(colors[randomInteger(0, 12)]);
        r->rotate(randomReal(0,90));
        objs.add(r);
    }
    for (int i = 0; i < 2000; i++) {
        if (randomChance(0.8)) {
            int index = randomInteger(0, objs.size() - 1);
            gw->add(objs[index]);
            added.add(objs[index]);
        }
        pause(1);
        if (randomChance(0.05) && !added.isEmpty()) {
            int index = randomInteger(0, added.size() - 1);
            gw->remove(added[index]);
            added.remove(index);
        }
        pause(1);
    }
}