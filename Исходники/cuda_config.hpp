inline bool isfinite(T arg) {
#ifndef _MSC_VER
  return (std::isfinite)(arg);
#else
  return _finite(arg) != 0;
#endif
}