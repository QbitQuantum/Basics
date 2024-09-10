int
main(int argc, char* argv[])
{
#ifndef CGAL_PCENTER_NO_OUTPUT
  CGAL::set_pretty_mode(cerr);
#endif // CGAL_PCENTER_NO_OUTPUT

  int number_of_points;
  int random_seed;

  // handle command line arguments:
  if (argc < 2 || (number_of_points = atoi(argv[1])) <= 0) {
    cerr << "usage: " << argv[0]
         << " num [random_seed]" << endl;
    exit(1);
  }
  if (argc < 3) {

#ifndef CGAL_PCENTER_NO_OUTPUT
    cerr << "No random seed specified - generating it" << endl;
#endif // CGAL_PCENTER_NO_OUTPUT

    // generate random seed
    random_seed = CGAL::get_default_random().get_int(0, (1 << 30));
  }
  else
    random_seed = atoi(argv[2]);

  // define random source:
  Random rnd(random_seed);

#ifndef CGAL_PCENTER_NO_OUTPUT
  cerr << "random seed is " << random_seed << endl;
#endif // CGAL_PCENTER_NO_OUTPUT
  PCont input_points;
  CGAL::cpp11::copy_n(Point_generator(1, rnd),
                number_of_points,
                back_inserter(input_points));

  for (int p(2); p < 5; ++p) {
#ifndef CGAL_PCENTER_NO_OUTPUT
    cerr << "** computing " << p << "-centers:" << endl;
#endif // CGAL_PCENTER_NO_OUTPUT

    PCont centers;
    FT result;
    Timer t;
    t.start();
    rectangular_p_center_2(
      input_points.begin(),
      input_points.end(),
      back_inserter(centers),
      result,
      p);
    t.stop();
#ifndef CGAL_PCENTER_NO_OUTPUT
    cerr << "[time: " << t.time() << " sec]" << endl;
#endif // CGAL_PCENTER_NO_OUTPUT

#ifdef CGAL_USE_LEDA
    // check that all points are covered
    CGAL::I_Infinity_distance_2< K > dist;
    #ifdef _MSC_VER
    {
    #endif
    for (iterator i = input_points.begin(); i != input_points.end(); ++i) {
      iterator j = centers.begin();
      do {
        if (dist(*i, *j) <= result / FT(2))
          break;
        if (++j == centers.end()) {
    #ifndef _MSC_VER
          cerr << "Error: Point " << *i << " is not covered." << endl;
    #else
          cerr << "Error: A point is not covered." << endl;
    #endif
          assert(j != centers.end());
        }
      } while (j != centers.end());
    }
    #ifdef _MSC_VER
    }
    #endif
    
    // check that there is at least one square with two points
    // on opposite sides
    CGAL::I_Signed_x_distance_2< K > xdist;
    CGAL::I_Signed_y_distance_2< K > ydist;
    bool boundary = false;
    #ifdef _MSC_VER
    {
    #endif
    for (iterator i = centers.begin(); i != centers.end(); ++i) {
      int left = 0, right = 0, bottom = 0, top = 0;
      for (iterator j = input_points.begin(); j != input_points.end(); ++j) {
        if (xdist(*i, *j) == result / FT(2))
          ++left;
        if (xdist(*j, *i) == result / FT(2))
          ++right;
        if (ydist(*j, *i) == result / FT(2))
          ++top;
        if (ydist(*i, *j) == result / FT(2))
          ++bottom;
      }
      if ( (left > 0 && right > 0) || (top > 0 && bottom > 0) )
        boundary = true;
    }
    #ifdef _MSC_VER
    }
    #endif
    if (!boundary)
      cerr << "Error: No square has two points on boundary." << endl;
    assert(boundary);
#endif // CGAL_USE_LEDA

  } // for (int p(2); p < 5; ++p)

  return 0;
} 