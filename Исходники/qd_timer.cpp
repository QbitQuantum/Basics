int main(int argc, char *argv[]) {
  unsigned int old_cw;
  fpu_fix_start(&old_cw);

  /* Parse the arguments. */
  char *arg;
  for (int i = 1; i < argc; i++) {
    arg = argv[i];
    if (strcmp(arg, "-h") == 0 || strcmp(arg, "-help") == 0) {
      print_usage();
      std::exit(0);
    } else if (strcmp(arg, "-double") == 0) {
      flag_test_double = true;
    } else if (strcmp(arg, "-dd") == 0) {
      flag_test_dd = true;
    } else if (strcmp(arg, "-qd") == 0) {
      flag_test_qd = true;
    } else if (strcmp(arg, "-all") == 0) {
      flag_test_double = flag_test_dd = flag_test_qd = true;
    } else if (strcmp(arg, "-v") == 0) {
      flag_verbose = true;
    } else if (strcmp(arg, "-long") == 0) {
      long_factor *= 10;
    } else {
      cerr << "Unknown flag `" << arg << "'." << endl;
    }
  }

  /* If no flag, test both double-double and quad-double. */
  if (!flag_test_double && !flag_test_dd && !flag_test_qd) {
    flag_test_dd = true;
    flag_test_qd = true;
  }

  if (flag_test_double) {
    TestSuite<double> test;

    cout << endl;
    cout << "Timing double" << endl;
    cout << "-------------" << endl;
    test.testall();
  }

  if (flag_test_dd) {
    TestSuite<dd_real> test;

    cout << endl;
    cout << "Timing dd_real" << endl;
    cout << "--------------" << endl;
    test.testall();
  }

  if (flag_test_qd) {
    TestSuite<qd_real> test;

    cout << endl;
    cout << "Timing qd_real" << endl;
    cout << "--------------" << endl;
    test.testall();
  }
  
  fpu_fix_end(&old_cw);
  return 0;
}