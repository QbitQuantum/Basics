  result_type operator()(Engine& eng)
  {
#ifndef BOOST_NO_STDC_NAMESPACE
    using std::log;
    using std::floor;
#endif
    return IntType(floor(log(RealType(1)-eng()) / _log_p)) + IntType(1);
  }