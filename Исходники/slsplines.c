boolean BSplineSelection::intersects (BoxObj& userb, Graphic* gs) {
    BoxObj b;
    getBox(b, gs);
    if (b.Intersects(userb)) {
	if (intersectsGraphic(ifillbspline, userb, gs)) {
	    return true;
	} else if (intersectsGraphic(bspline, userb, gs)) {
	    return true;
	} else if (LeftAints(lx0, ly0, lx1, ly1, userb, gs)) {
	    return true;
	} else if (RightAints(rx0, ry0, rx1, ry1, userb, gs)) {
	    return true;
	}
    }
    return false;
}