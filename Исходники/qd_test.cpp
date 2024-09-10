int main(int argc, char *argv[]) {
  
  bool pass = true;
  unsigned int old_cw;
  fpu_fix_start(&old_cw);

  /* Parse the arguments. */
  char *arg;
  for (int i = 1; i < argc; i++) {
    arg = argv[i];
    if (strcmp(arg, "-h") == 0 || strcmp(arg, "-help") == 0) {
      print_usage();
      exit(0);
    } else if (strcmp(arg, "-dd") == 0) {
      flag_test_dd = true;
    } else if (strcmp(arg, "-qd") == 0) {
      flag_test_qd = true;
    } else if (strcmp(arg, "-all") == 0) {
      flag_test_dd = flag_test_qd = true;
    } else if (strcmp(arg, "-v") == 0 || strcmp(arg, "-verbose") == 0) {
      flag_verbose = true;
    } else {
      cerr << "Unknown flag `" << arg << "'." << endl;
    }
  }

  /* If no flag, test both double-double and quad-double. */
  if (!flag_test_dd && !flag_test_qd) {
    flag_test_dd = true;
    flag_test_qd = true;
  }

  if (flag_test_dd) {
    TestSuite<dd_real> dd_test;

    cout << endl;
    cout << "Testing dd_real ..." << endl;
    if (flag_verbose)
      cout << "sizeof(dd_real) = " << sizeof(dd_real) << endl;
    pass &= dd_test.testall();
  }

  if (flag_test_qd) {
    TestSuite<qd_real> qd_test;

    cout << endl;
    cout << "Testing qd_real ..." << endl;
    if (flag_verbose)
      cout << "sizeof(qd_real) = " << sizeof(qd_real) << endl;
    pass &= qd_test.testall();
  }
  
  fpu_fix_end(&old_cw);
  return (pass ? 0 : 1);
}