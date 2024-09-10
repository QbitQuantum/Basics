 // address of an element in _nodes.  Used when the element is to be modified
 PointsToNode *ptnode_adr(uint idx) {
   if ((uint)_nodes->length() <= idx) {
     // expand _nodes array
     PointsToNode dummy = _nodes->at_grow(idx);
   }
   return _nodes->adr_at(idx);
 }