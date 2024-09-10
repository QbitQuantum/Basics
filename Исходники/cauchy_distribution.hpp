  result_type operator()(Engine& eng)
  {
    // Can we have a boost::mathconst please?
    const result_type pi = result_type(3.14159265358979323846);
#ifndef BOOST_NO_STDC_NAMESPACE
    using std::tan;
#endif
    return _median + _sigma * tan(pi*(eng()-result_type(0.5)));
  }