bool CSymbolEngineOpenPPLUserVariables::EvaluateSymbol(const char *name, double *result, bool log /* = false */) {
  FAST_EXIT_ON_OPENPPL_SYMBOLS(name);
  if (_memicmp(name, "user", 4) != 0) {
    // Not a user-variable
    return false;
  }
  if (memcmp(name+4, "chair", 5) == 0) {
    // Symbol "userchair", not a user-variable
    return false;
  }
  // Try to look it up
  if (_user_variables[name]) {
    write_log(preferences.debug_symbolengine_open_ppl(),
      "[CSymbolEngineOpenPPLUserVariables] user-variable exists: %s\n", name);
    *result = double(true);
    return true;
  }
  write_log(preferences.debug_symbolengine_open_ppl(),
    "[CSymbolEngineOpenPPLUserVariables] user-variable does not exist: %s\n", name);
  *result = double(false);
  return true;
}