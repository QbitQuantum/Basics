inline void parseAndSet_b(const TString& input, TString arg, bool& value) {
  TString newval = parseArg(input, arg);
  if (!newval.IsNull()) {
    if (newval.IsBin()) value = newval.Atoi();
    else if (newval == "true") value = true;
    else if (newval == "false") value = false;
  }
}