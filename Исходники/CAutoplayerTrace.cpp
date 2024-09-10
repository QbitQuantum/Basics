bool CAutoplayerTrace::SymbolNeedsToBeLogged(CString name) {
  // DLL, as there is no caching and value might change
  if (memcmp(name, "dll$", 4) == 0) return true;
  // Memory-store and recall-commands
  if (memcmp(name, "me_", 3) == 0) return true;
  // OpenPPL-user-variables might also change (once)
  // We don't care about multiple loggings of userchair here
  if (_memicmp(name, "user", 4) == 0) return true;
  // True random numbers that don't get cached,
  // i.e. OH-script "random" and OpenPPL "Random"
  if (memcmp(name, "random", 6) == 0) return true;
  if (memcmp(name, "Random", 6) == 0) return true;
  // Values that already got logged can be ignored
  if (_already_logged_symbols[name] == true) return false;
  // Everything else needs to be logged
  return true;
}