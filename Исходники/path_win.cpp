 // static
 HRGN Path::CombineRegions(HRGN r1, HRGN r2)
 {
     HRGN dest = CreateRectRgn(0, 0, 1, 1);
     CombineRgn(dest, r1, r2, RGN_OR);
     return dest;
 }