 void Canvas::update()
 {
     if (_dirty)
     {
         updateColors();
         _dirty = false;
     }
 }