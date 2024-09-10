int main(int argc, char* argv[])
{
  CGAL::Timer timer;
  // first param is dimension
  // second param is number of points
  int dimension = 4;
  int n = 100;
  int m = 100;

  if (argc > 1 && std::string(argv[1])== std::string("-h")) {
    std::cout<<"usage: "<<argv[0]<<" [dim] [#points] [max coords]\n";
    return 1;
  }
  if (argc > 1)  dimension = atoi(argv[1]);
  if (argc > 2)  n = atoi(argv[2]);
  if (argc > 3)  m = atoi(argv[2]);

  Delaunay_d T(dimension);
  std::list<Point_d> L;

  random_points_in_range(n,dimension,-m,m,L);

  timer.start();
  int i=0;
  std::list<Point_d>::iterator it;
  for(it = L.begin(); it!=L.end(); ++it) {
    T.insert(*it); i++;
    if (i%10==0)
      std::cout << i << " points inserted" << std::endl;
  }
  timer.stop();
  std::cout << "used time for inserts  " << timer.time() << std::endl;

  std::cout << "entering check" << std::endl;

  timer.reset();
  timer.start();
  T.is_valid();
  timer.stop();
  std::cout << "used time for sanity check  " << timer.time() << std::endl;
  

  std::cout << "entering nearest neighbor location" << std::endl;
  L.clear();
  random_points_in_range(n/10,dimension,-m,m,L);

  timer.reset();
  timer.start();
  i = 0;
  for(it = L.begin(); it!=L.end(); ++it) {
    T.nearest_neighbor(*it); i++;
    if (i%10==0) std::cout << i << " points located" << std::endl;
  }
  timer.stop();
  std::cout << "used time for location  " << timer.time() << std::endl;

  T.print_statistics();
  std::cout << "done" << std::endl;
  return 0;
}