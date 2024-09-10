int euler_solver<3>(string& solution) {

  constexpr long long test_val = 600851475143LL;

  long long curr_val = test_val;

  Prime my_prime;

  Cap<long long> capi([] (const long long &x) -> bool { return x <= sqrt(test_val); });

  auto term = capi.wrap(my_prime);

  for (const auto &i : term) {
    if (divisible(curr_val, i)) {
      curr_val /= i;
      if (curr_val == 1LL) {
        curr_val = i;
        break;
      }
    }
  }

  solution = to_string(curr_val);

  return EulerStatus::SUCCESS;

}