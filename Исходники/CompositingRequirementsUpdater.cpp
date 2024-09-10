 bool overlapsLayers(const IntRect& bounds) const
 {
     // Checking with the bounding box will quickly reject cases when
     // layers are created for lists of items going in one direction and
     // never overlap with each other.
     if (!bounds.intersects(m_boundingBox))
         return false;
     for (unsigned i = 0; i < m_layerRects.size(); i++) {
         if (m_layerRects[i].intersects(bounds))
             return true;
     }
     return false;
 }