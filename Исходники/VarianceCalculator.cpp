void VarianceCalculator::setDistanceHeadingVariance(RRCoord &rr) {
   int camera_height = 500;
   float phi = atan(rr.distance() / camera_height);
   rr.var.setZero();
   rr.var(0,0) = SQUARE(500 + camera_height*(tan(phi + DEG2RAD(3)) - tan(phi)));
   rr.var(1,1) = SQUARE(DEG2RAD(10));
}