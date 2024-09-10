int main()
{
  CGAL::Timer timer;
  timer.start();
  _test_cls_alpha_shape_3<Alpha_shape_3>();
  _test_cls_alpha_shape_3_exact<EAlpha_shape_3>();

  std::cerr << timer.time() << " sec." << std::endl;
  return 0;
}