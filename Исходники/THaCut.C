//_____________________________________________________________________________
THaCut::EvalMode THaCut::ParsePrefix( TString& expr )
{
  // Parse the given expression for a mode prefix (e.g. "OR:")
  // and return its value. If the expression does not have a mode prefix,
  // return the default kAND (=0).
  // The expression is expected to have all whitespace removed.
  // If the prefix was found, it is stripped from the expression.
  // If a mode prefix seems to be present, but is not found in
  // the defined modes, return kModeErr.

  const EvalMode kDefaultMode = kOR;
  const char* const here = "THaCut";

  struct ModeDef_t {
    const char* prefix;
    EvalMode    mode;
  };
  const ModeDef_t mode_defs[] = {
    { "OR", kOR }, { "ANY", kOR }, { "AND", kAND }, { "ALL", kAND },
    { "XOR", kXOR }, { "ONE", kXOR }, { "ONEOF", kXOR }, { 0, kModeErr }
  };

  Ssiz_t colon = expr.Index(":");
  if( colon == kNPOS )
    return kDefaultMode;

  const ModeDef_t* def = mode_defs;
  while( def->prefix ) {
    if( expr.BeginsWith(def->prefix) &&
	static_cast<Ssiz_t>(strlen(def->prefix)) == colon ) {
      expr.Remove(0,colon+1);
      break;
    }
    ++def;
  }
  EvalMode mode = def->mode;

  if( mode == kModeErr ) {
    TString prefix = expr(0,colon);
    Error(here, "Unknown prefix %s", prefix.Data() );
  } else if( expr.Length() == 0 ) {
    Error(here, "expression may not be empty");
    mode = kModeErr;
  }
  if( mode == kModeErr )
    SetBit(kError);
  return mode;
}