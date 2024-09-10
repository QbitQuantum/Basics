int main()
{

  std::vector<Point_3> points;
  Point_3 p;

  while(std::cin >> p){
    points.push_back(p);
  }
  Timer timer;
  timer.start();
  int N = 0;
  for(int i = 0; i < 5; i++){
    spatial_sort(points.begin(), points.end());
  }
  timer.stop();
  
  std::cerr << timer.time() << " sec" << std::endl;
  return 0;
}