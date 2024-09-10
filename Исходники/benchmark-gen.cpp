void
run_benchmark(SDG& sdg)
{  
  load_cin_file(std::cin, sdg);

  CGAL::Timer timer;
  timer.start();
  if(! sdg.is_valid(true, 1) ){
    std::cerr << "invalid data structure" << std::endl;
  } else {
    std::cerr << "valid data structure" << std::endl;
  }
  timer.stop();
  std::cerr << "Data structure checking time = " << timer.time() << "s\n";
}