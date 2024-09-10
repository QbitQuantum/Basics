void ResourceData::vscan(IMarker& mark) const {
  // default implementation scans for ambiguous pointers.
  mark(this, heapSize());
}