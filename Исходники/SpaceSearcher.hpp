 /** Method to return an iterator pointing to "one past"
  * the last item in a given BoundingBox.
  */
 iterator end(const BoundingBox& bb) const {
   assert(!bb.empty());
   return Iterator(this, bb, mc_.code(bb.max())+1, 0);
 }