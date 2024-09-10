boolean MultiLine::s_intersects (BoxObj& userb, Graphic* gs) {
    Coord* convx, *convy;
    BoxObj b;
    boolean result = false;

    getBox(b, gs);
    if (b.Intersects(userb)) {
	convx = new Coord[count()];
	convy = new Coord[count()];
	transformList(x(), y(), count(), convx, convy, gs);
	MultiLineObj ml (convx, convy, count());
	result = ml.Intersects(userb);
	delete convx;
	delete convy;
    }
    return result;
}