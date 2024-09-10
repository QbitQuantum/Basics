 Arc Dubins::getSecondArc() const {
     State st;
     if (isCCC) {
         st = getCenterArc().getEnd();
     } else {
         Point ps = getCenter().p2;
         st = State(ps, start.ang + len1);
     }
     return Arc(st, len3, radius);
 }