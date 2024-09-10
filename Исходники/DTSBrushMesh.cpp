   void BoxMesh::construct() 
   {
      int   i ;
      Box   bounds = getBounds() ;
      Point center = (bounds.max - bounds.min) / 2 ;

      // Vertex
      verts.push_back(Point(bounds.min.x(), bounds.min.y(), bounds.min.z()));
      verts.push_back(Point(bounds.max.x(), bounds.min.y(), bounds.min.z()));
      verts.push_back(Point(bounds.min.x(), bounds.max.y(), bounds.min.z()));
      verts.push_back(Point(bounds.max.x(), bounds.max.y(), bounds.min.z()));
      verts.push_back(Point(bounds.min.x(), bounds.min.y(), bounds.max.z()));
      verts.push_back(Point(bounds.max.x(), bounds.min.y(), bounds.max.z()));
      verts.push_back(Point(bounds.min.x(), bounds.max.y(), bounds.max.z()));
      verts.push_back(Point(bounds.max.x(), bounds.max.y(), bounds.max.z()));

      // Texture coordinates
      for (i = 0 ; i < 8 ; i++)
         tverts.push_back(Point2D(0,0));

      // Indices
      int inds[] = { 0, 4, 1, 5, 3, 7, 2, 6, 0, 4, 6, 7, 4, 5, 0, 1, 2, 3 } ;
      for (i = 0 ; i < sizeof(inds)/sizeof(inds[0]) ; i++)
         indices.push_back(inds[i]);

      // Primitives
      Primitive p ;
      p.firstElement = 0 ;
      p.numElements  = 10 ;
      p.type         = Primitive::NoMaterial | Primitive::Strip | Primitive::Indexed ;
      primitives.push_back(p) ;
      p.firstElement = 10 ;
      p.numElements  = 4 ;
      primitives.push_back(p) ;
      p.firstElement = 14 ;
      primitives.push_back(p) ;

      // Normals
      std::vector<Point>::iterator ptr ;
      for (ptr = verts.begin() ; ptr != verts.end() ; ptr++)
      {
         Point normal ;
         normal = *ptr - center ;
         normal.normalize() ;
         normals.push_back (normal) ;
         enormals.push_back (encodeNormal(normal)) ;
      }

      // Other stuff
      setFrames (1) ;
      setParent (-1) ;
      calculateCenter() ;
      calculateRadius() ;
   }