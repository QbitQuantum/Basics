 static SkRegion TestRegion() {
     SkRegion region;
     SkIRect rect = SkIRect::MakeXYWH(0, 0, 2, 1);
     region.setRect(rect);
     return region;
 }