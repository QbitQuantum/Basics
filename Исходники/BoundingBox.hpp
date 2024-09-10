 /** Test if @a box is entirely within this bounding box.
  *
  * Returns false if @a box.empty(). */
 bool contains(const BoundingBox& box) const {
   return !box.empty() && contains(box.min()) && contains(box.max());
 }