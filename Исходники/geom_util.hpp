 bool pass(const box2d<double>& extent) const
 {
     return extent.intersects(box_);
 }