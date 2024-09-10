int main()
{
  int i, loops=10000000;
  CGAL::Timer t;
  double dt;

#if 0

// Those timings were made on my laptop, which is now not mine anymore,
// so I need to make them again to be able to make useful comparisons...
// Maybe automazing the process would be useful to test on different
// platforms...

  //                   mp   / mp1  / mp2  / mp3

  // Cartesian       : 3.44 / 2.71 / 2.67 / 3.5
  // PointC2         : 2.27 / 2.26 / 2.17 / 2.78
  // Advanced kernel : 2.25 / 2.26 / 2.17 / 2.78
  // SimpleCartesian : 1.23 (1.21) (= without the wrapper classes)
  // Homogeneous     : 4.46 (3.47)

  dt = t.time(); t.start();
  for (i=0; i<loops; i++)
    Point2 C = CGAL::midpoint(A,B);

#else

  // Cartesian       : 4.13 / 3.68 / 3.63 / 4.65
  // PointC2         : 3.29 / 3.29 / 3.16 / 3.5
  // Advanced kernel : 3.29 / 3.29 / 3.16 / 3.51
  // SimpleCartesian : 1.32 (1.21)
  // Homogeneous     : 5.23 (4.22)

  Point2 C;
  dt = t.time(); t.start();
  for (i=0; i<loops; i++)
    C = CGAL::midpoint(A,B);

#endif

  t.stop();
  std::cout << "time = " << t.time()-dt << std::endl;

  return 0;
}