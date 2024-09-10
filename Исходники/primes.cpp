int main()
{
  while (!cin.eof()) {
    // How many primes to test? And should we print them?
    cerr << "Input Number: ";
    int n = 0;
    CS207::getline_parsed(cin, n);
    if (n <= 0)
      break;

    cerr << "Print Primes (y/n): ";
    char confirm = 'n';
    CS207::getline_parsed(cin, confirm);
    bool print_primes = (confirm == 'y' || confirm == 'Y');

    CS207::Clock timer;

    // Loop and count primes from 2 up to n
    int num_primes = 0;
    for (int i = 2; i <= n; ++i) {
      if (is_prime(i)) {
        ++num_primes;
        if (print_primes)
          cout << i << endl;
      }
    }

    double elapsed_time = timer.seconds();

    cout << "There are " << num_primes
         << " primes less than or equal to " << n << ".\n"
         << "Found in " << (1000 * elapsed_time) << " milliseconds.\n\n";
  }

  return 0;
}