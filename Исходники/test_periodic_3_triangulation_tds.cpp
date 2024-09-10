// just reusing the tests from the T3 package to check whether the
// periodic vertices and cells fulfill the requirements.
int main(int, char**)
{
  CGAL::Timer timer;
  timer.start();
  _test_cls_periodic_3_tds_3(Tds());
  std::cerr << timer.time() << " sec." << std::endl;
  return 0;
}