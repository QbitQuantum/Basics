 static Ellipse since_center(int centerx, int centery, uint16_t radiusx, uint16_t radiusy) {
     return Ellipse(centerx - radiusx, centery - radiusy, centerx + radiusx, centery + radiusy);
 }