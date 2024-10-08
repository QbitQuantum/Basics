void draw(SkCanvas* canvas) {
    const char* verbNames[] = { "move", "line", "quad", "conic", "cubic", "close", "done" };
    const int pointCount[]  = {     1 ,     2 ,     3 ,      3 ,      4 ,      1 ,     0  };
    SkPath path;
    path.arcTo(20, 0, 20, 20, 20);
    SkPath::Iter iter(path, false);
    SkPath::Verb verb;
    do {
       SkPoint points[4];
       verb = iter.next(points);
       SkDebugf("%s ", verbNames[(int) verb]);
       for (int i = 0; i < pointCount[(int) verb]; ++i) {
            SkDebugf("{%g, %g}, ", points[i].fX, points[i].fY);
       }
       if (SkPath::kConic_Verb == verb) {
           SkDebugf("weight = %g", iter.conicWeight());
       }
       SkDebugf("\n");
    } while (SkPath::kDone_Verb != verb);
}