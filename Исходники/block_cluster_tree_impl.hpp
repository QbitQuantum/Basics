inline bool WeakAdmissibility::operator()(const BoundingBox &box1,
                                          const BoundingBox &box2) const {

  return box1.distance(box2) > 0;
}