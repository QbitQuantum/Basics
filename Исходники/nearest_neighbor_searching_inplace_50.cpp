int main() {
  const unsigned int N = 50;
  CGAL::Timer timer;
  timer.start();

  std::vector<Point_3> points, queries;
  Point_3 p;

  std::ifstream point_stream("points.xyz");
  while(point_stream >> p){
    points.push_back(p);

  }

  My_point_property_map ppmap(points);
  Distance tr_dist(ppmap);

  std::ifstream query_stream("queries.xyz");
  while(query_stream >> p ){
    queries.push_back(p);

  }
  timer.stop();
  std::cerr << "reading points took " << timer.time() << " sec." << std::endl;


  timer.reset();
  timer.start();
  Tree tree( boost::counting_iterator<std::size_t>(0),
             boost::counting_iterator<std::size_t>(points.size()),
             Splitter(),
             Traits(ppmap));
  tree.build();
  timer.stop();
  std::cerr << "tree construction took " << timer.time() << " sec." << std::endl;


  // Initialize the search structure, and search all N points
  
  double d = 0;
  timer.reset();
  timer.start();
  for(int i = 0; i < queries.size(); i++){
    K_neighbor_search search(tree, queries[i], 50, 0, true, tr_dist);

    // report the N nearest neighbors and their distance
    // This should sort all N points by increasing distance from origin
    for(K_neighbor_search::iterator it = search.begin(); it != search.end(); ++it){
      //std::cout << it->first << std::endl;
      d += get(ppmap,it->first).x();
    }
  }
  timer.stop();
  std::cerr << d << std::endl;
  std::cerr << queries.size() << " queries in " << timer.time() << " sec." << std::endl;

  return 0;
}