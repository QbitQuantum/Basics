void time_insertion_and_check(pp_int V, int n, int d,
  CGAL::Convex_hull_d<R>& C, std::string s, bool check=true)
{
  typedef typename CGAL::Convex_hull_d<R>::chull_has_local_non_convexity
    chull_has_local_non_convexity;
  typedef typename CGAL::Convex_hull_d<R>::chull_has_double_coverage
    chull_has_double_coverage;
  typedef typename CGAL::Convex_hull_d<R>::
    chull_has_center_on_wrong_side_of_hull_facet
    chull_has_center_on_wrong_side_of_hull_facet;

  std::cout << " timing of " << s << std::endl;
  std::vector< CGAL::Point_d<R> > P(n); int i;
  for(i=0; i<n; ++i)
    P[i] = CGAL::Point_d<R>(d,V[i],V[i]+d,1);

  timer.reset(); timer.start(); // float ti = used_time();
  for(i=0; i<n; ++i) {
    C.insert(P[i]);
    if (i%10==0) std::cout << i << " points inserted" << std::endl;
  }
  timer.stop();
  double t = timer.time(); timer.reset(); // float t = used_time(ti);
  (*p_table_file) << s << "\t" << d << " " << n << " "
                  << C.number_of_vertices() << " " << C.number_of_facets()
                  << "\t" << t;
  C.print_statistics();
  std::cout << "used time for inserts  " << t << std::endl;

  C.clear(d);
  timer.start(); // ti = used_time();
  C.initialize(P.begin(),P.end());
  timer.stop(); t = timer.time(); timer.reset();
  // t = used_time(ti);
  C.print_statistics();
  std::cout << "used time for inserts  " << t << std::endl;

  if (check) {
    timer.start();
    std::cout << "entering check" << std::endl;
    try { C.is_valid(true); }
    catch ( chull_has_local_non_convexity )
    { std::cerr << "local non-convexity determined\n"; }
    catch ( chull_has_double_coverage )
    { std::cerr << "double coverage determined\n"; }
    catch ( chull_has_center_on_wrong_side_of_hull_facet )
    { std::cerr << "facet center problem determined\n"; }

    // t = used_time(ti);
    timer.stop(); t = timer.time();
    (*p_table_file) << "\t" << t <<std::endl;
    std::cout<<"used time for sanity check  "<< t <<std::endl<<std::endl;
  } else {
    (*p_table_file) << "\t" << "no"<<std::endl;
    std::cout<<"no check"<<std::endl;
  }
  p_table_file->flush();
}