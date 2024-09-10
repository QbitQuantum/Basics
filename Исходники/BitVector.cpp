void BitVector::dump(PrintStream& out) {
  for (size_t i = 0; i < size(); ++i) {
    if (get(i))
      out.printf("1");
    else
      out.printf("-");
  }
}