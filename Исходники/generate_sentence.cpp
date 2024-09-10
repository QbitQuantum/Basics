int nrand(const int n) {
  if (n <= 0 || n > RAND_MAX) {
    throw domain_error("Argument to nrand is out of range.");
  }

  time_t t = time(nullptr);
  srand(t);
  const int r = rand() % n;
  cout << "r = " << r << endl;
  return r;
}