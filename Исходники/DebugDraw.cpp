void DebugDrawer::drawPolyhedronDebugInfo( const AnyPolyhedron& polyhedron, const MatrixF& transform, const Point3F& scale )
{
   Point3F center = polyhedron.getCenterPoint();
   center.convolve( scale );
   transform.mulP( center );

   // Render plane indices and normals.

   const U32 numPlanes = polyhedron.getNumPlanes();
   for( U32 i = 0; i < numPlanes; ++ i )
   {
      const AnyPolyhedron::PlaneType& plane = polyhedron.getPlanes()[ i ];

      Point3F planePos = plane.getPosition();
      planePos.convolve( scale );
      transform.mulP( planePos );

      Point3F normal = plane.getNormal();
      transform.mulV( normal );

      drawText( planePos, String::ToString( i ), ColorI::BLACK );
      drawLine( planePos, planePos + normal, ColorI::GREEN );
   }

   // Render edge indices and direction indicators.

   const U32 numEdges = polyhedron.getNumEdges();
   for( U32 i = 0; i < numEdges; ++ i )
   {
      const AnyPolyhedron::EdgeType& edge = polyhedron.getEdges()[ i ];

      Point3F v1 = polyhedron.getPoints()[ edge.vertex[ 0 ] ];
      Point3F v2 = polyhedron.getPoints()[ edge.vertex[ 1 ] ];

      v1.convolve( scale );
      v2.convolve( scale );
      transform.mulP( v1 );
      transform.mulP( v2 );

      const Point3F midPoint = v1 + ( v2 - v1 ) / 2.f;

      drawText( midPoint, String::ToString( "%i (%i, %i)", i, edge.face[ 0 ], edge.face[ 1 ] ), ColorI::WHITE );

      // Push out the midpoint away from the center to place the direction indicator.

      Point3F pushDir = midPoint - center;
      pushDir.normalize();
      const Point3F dirPoint = midPoint + pushDir;
      const Point3F lineDir = ( v2 - v1 ) / 2.f;

      drawLine( dirPoint, dirPoint + lineDir, ColorI::RED );
   }

   // Render point indices and coordinates.

   const U32 numPoints = polyhedron.getNumPoints();
   for( U32 i = 0; i < numPoints; ++ i )
   {
      Point3F p = polyhedron.getPoints()[ i ];

      p.convolve( scale );
      transform.mulP( p );

      drawText( p, String::ToString( "%i: (%.2f, %.2f, %.2f)", i, p.x, p.y, p.z ), ColorF::WHITE );
   }
}