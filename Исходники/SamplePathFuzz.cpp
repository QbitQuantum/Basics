 SkRRect makeRRect() {
     SkRRect rrect;
     RandomSetRRect rrectType = makeSetRRectType();
     if (fPrintName) {
         SkDebugf("%.*s%s\n", fPathDepth * 3, fTab, gRandomSetRRectNames[rrectType]);
     }
     switch (rrectType) {
     case kSetEmpty:
         rrect.setEmpty();
         break;
     case kSetRect: {
         SkRect rect = makeRect();
         rrect.setRect(rect);
     }
     break;
     case kSetOval: {
         SkRect oval = makeRect();
         rrect.setOval(oval);
     }
     break;
     case kSetRectXY: {
         SkRect rect = makeRect();
         SkScalar xRad = makeScalar();
         SkScalar yRad = makeScalar();
         rrect.setRectXY(rect, xRad, yRad);
     }
     break;
     case kSetNinePatch: {
         SkRect rect = makeRect();
         SkScalar leftRad = makeScalar();
         SkScalar topRad = makeScalar();
         SkScalar rightRad = makeScalar();
         SkScalar bottomRad = makeScalar();
         rrect.setNinePatch(rect, leftRad, topRad, rightRad, bottomRad);
         SkDebugf("");  // keep locals in scope
     }
     break;
     case kSetRectRadii: {
         SkRect rect = makeRect();
         SkVector radii[4];
         makeVectorArray(SK_ARRAY_COUNT(radii), radii);
         rrect.setRectRadii(rect, radii);
     }
     break;
     }
     return rrect;
 }