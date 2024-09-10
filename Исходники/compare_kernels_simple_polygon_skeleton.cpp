void build_skeleton(const char* fname)
{
  typedef typename Kernel::Point_2                                         Point_2;
  typedef CGAL::Polygon_2<Kernel>                                 Polygon_2;
  typedef CGAL::Straight_skeleton_builder_traits_2<Kernel>        SsBuilderTraits;
  typedef CGAL::Straight_skeleton_2<Kernel>                       Ss;
  typedef CGAL::Straight_skeleton_builder_2<SsBuilderTraits,Ss>   SsBuilder;
  
  Polygon_2 pgn;
  
  std::ifstream input(fname);
  
  FT x,y;
  while(input)
  {
    input >> x;
    if (!input) break;
    input >> y;
    if (!input) break;
    pgn.push_back( Point_2( typename Kernel::FT(x), typename Kernel::FT(y) ) );
  }
  input.close();
  
  std::cout << "Polygon has " << pgn.size() <<  " points\n";
  
  if(!pgn.is_counterclockwise_oriented()) {
      std::cerr << "Polygon is not CCW Oriented" << std::endl;
  }
  if(!pgn.is_simple()) {
      std::cerr << "Polygon is not simple" << std::endl;
  }  

  CGAL::Timer time;
  time.start();
  SsBuilder ssb;
  ssb.enter_contour(pgn.vertices_begin(), pgn.vertices_end());
  boost::shared_ptr<Ss> straight_ske = ssb.construct_skeleton();
  time.stop();
  
  std::cout << "Time spent to build skeleton " << time.time() << "\n";
  
  if(!straight_ske->is_valid()) {
      std::cerr << "Straight skeleton is not valid" << std::endl;
  }

  std::cerr.precision(60);
  print_straight_skeleton(*straight_ske);
  
}