void FieldPainter::translateRR(const RRCoord &rr, const AbsCoord &robot) {
   translate(robot.x(), robot.y());
   rotate((const float)RAD2DEG(robot.theta()));
   rotate((const float)RAD2DEG(rr.heading()));
   translate(rr.distance(), 0);
   /*
   rotate((const float)RAD2DEG(-robot.theta()));
   rotate((const float)RAD2DEG(-rr.heading()));
   */
   if (!isnan(rr.orientation())) {
      rotate(RAD2DEG(-rr.orientation()));
   }
}