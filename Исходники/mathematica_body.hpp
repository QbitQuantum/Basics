std::string ToMathematica(Quantity<D> const& quantity) {
  std::string s = DebugString(quantity);
  if (IsFinite(quantity)) {
    s.replace(s.find("e"), 1, "*^");
  }
  std::string const number = ToMathematica(quantity / SIUnit<Quantity<D>>());
  std::size_t const split = s.find(" ");
  std::string const units = Escape(s.substr(split, s.size()));
  return Apply(
      "SetPrecision",
      {Apply("Quantity", {number, units}), "MachinePrecision"});
}