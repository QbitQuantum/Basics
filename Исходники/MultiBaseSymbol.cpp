MultiBaseSymbol Terram::Foundation::operator^(const MultiBaseSymbol &a,
                                              int16_t exponent) noexcept {
  if (exponent == 0) {
    return MultiBaseSymbol::identity();
  }

  auto bases_a = a.bases();

  transform(bases_a.begin(), bases_a.end(), bases_a.begin(),
            [=](Symbol s) { return s ^ exponent; });

  return MultiBaseSymbol(bases_a);
}