 double angle(CBundle* const &b) const {
     double ax=x1()-x0;
     double ay=y1()-y0;
     double bx=b->x1()-b->x0;
     double by=b->y1()-b->y0;
     return vangle(ax,ay,bx,by);
 }