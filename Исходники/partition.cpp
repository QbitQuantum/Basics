void ConvexpartitionIpelet::protected_run(int fn)
{
  
  if (fn==4) {
    show_help();
    return;
  }

  std::list<Polygon_2> pol_list;
  Iso_rectangle_2 bbox=
    read_active_objects( CGAL::dispatch_or_drop_output<Polygon_2>( std::back_inserter(pol_list) ) );

  
  
  if (pol_list.size ()==0){
    print_error_message("No polygon selected");
    return;
  }
  
  for (std::list<Polygon_2>::iterator itp=pol_list.begin();itp!=pol_list.end();++itp){
    //~ Polygon_2 polygon=*itp;
    //~ std::list<Polygon_2> partition_polys;
    CGAL::Polygon_2<Kernel,std::list<Kernel::Point_2> > polygon(itp->vertices_begin(),itp->vertices_end());
    std::list<CGAL::Polygon_2<Kernel,std::list<Kernel::Point_2> > > partition_polys;
    
    if (!polygon.is_simple()){
      print_error_message("Polygon must be simple");
      continue;   
    }
    
    if (polygon.orientation()!=CGAL::COUNTERCLOCKWISE)
      polygon.reverse_orientation();
    
    switch(fn){
    case 0:
    CGAL::y_monotone_partition_2(polygon.vertices_begin(), 
                                  polygon.vertices_end(),
                                  std::back_inserter(partition_polys));
    break;
    
    case 1:
    CGAL::greene_approx_convex_partition_2(polygon.vertices_begin(), 
                                  polygon.vertices_end(),
                                  std::back_inserter(partition_polys));
    break;

    case 2:
    CGAL::approx_convex_partition_2(polygon.vertices_begin(), 
                                  polygon.vertices_end(),
                                  std::back_inserter(partition_polys));
    break;
    
    case 3:
    CGAL::optimal_convex_partition_2(polygon.vertices_begin(), 
                                  polygon.vertices_end(),
                                  std::back_inserter(partition_polys));
    break;
    }
    
    draw_in_ipe(partition_polys.begin(),partition_polys.end());
  }
}