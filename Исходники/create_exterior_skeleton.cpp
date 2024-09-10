int main()
{
  Polygon_2 poly ;
  
  poly.push_back( Point(-1,-1) ) ;
  poly.push_back( Point(0,-12) ) ;
  poly.push_back( Point(1,-1) ) ;
  poly.push_back( Point(12,0) ) ;
  poly.push_back( Point(1,1) ) ;
  poly.push_back( Point(0,12) ) ;
  poly.push_back( Point(-1,1) ) ;
  poly.push_back( Point(-12,0) ) ;
     
  SsPtr ss = CGAL::create_interior_straight_skeleton_2(poly);
  
  double offset = 1 ;
  
  { 
    CGAL::Timer time; time.start();
    PolygonPtrVector outer_polygons =
    CGAL::create_exterior_skeleton_and_offset_polygons_2(offset, poly); 
    time.stop();
    std:: cout << outer_polygons.size() << " built in " << time.time() << "\n";
  }

  {
    CGAL::Timer time; time.start();
    PolygonPtrVector outer_polygons =
    CGAL::create_offset_polygons_2<Polygon_2>(offset,
    *CGAL::create_exterior_straight_skeleton_2( offset, poly)); 
    time.stop();
    std:: cout << outer_polygons.size() << " built in " << time.time() << "\n";
  }

  return 0;
}