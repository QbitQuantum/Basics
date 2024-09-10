void profileWriteEntry(std::ofstream &f, T *a) {
  ProfilingData_ENTRY s;
  s.thisp=ptrToLong(a);
  profileWrite(f, s);
}