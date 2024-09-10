double Area(const BoundingBox& bb){
  return (bb.y2() - bb.y1())*(bb.x2() - bb.x1());
}