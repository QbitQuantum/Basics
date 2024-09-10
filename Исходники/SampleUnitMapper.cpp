 SkPoint invertPt(SkScalar x, SkScalar y) {
     SkPoint pt;
     SkMatrix m;
     fMatrix.invert(&m);
     m.mapXY(x, y, &pt);
     return pt;
 }