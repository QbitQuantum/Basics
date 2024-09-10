 inline bool Intersects(PhysicsObject Other) {
     if (Other._id == _parentID || Other._parentID == _id)
         return false;
     return _aabb.Intersects(Other._aabb);
 }