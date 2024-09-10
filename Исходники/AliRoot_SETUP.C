Bool_t SETUP_LoadLibraries(const TString &libs) {

  // Loads a list of colon-separated libraries. Returns kTRUE on success, kFALSE
  // if at least one library couldn't load properly. Does not check for double
  // loads (but ROOT does).

  TString l;
  Ssiz_t from;

  while ( libs.Tokenize(l, from, ":") ) {
    if (l.IsNull()) continue;
    if (!l.BeginsWith("lib")) l.Prepend("lib");
    if (l.EndsWith(".so")) l.Remove(l.Length()-3, l.Length());

    ::Info(gMessTag.Data(), ">> Loading library %s...", l.Data());

    if (gSystem->Load(l.Data()) < 0) {
       ::Error(gMessTag.Data(), "Error loading %s, aborting", l.Data());
       return kFALSE;  // failure
    }
  }

  return kTRUE;  // success

  return 0;
}