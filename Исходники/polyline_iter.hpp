 const Vertex *operator*() const {
   CARVE_ASSERT(idx >= 0 && idx < base->vertexCount());
   return base->vertex((size_t)idx);
 }