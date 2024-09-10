void PerformanceDebugger::report_context(InlinedScope* s) {
  if (!DebugPerformance) return;
  Reporter r(this);
  GrowableArray<Expr*>* temps = s->contextTemporaries();
  const int len = temps->length();
  int nused = 0;
  for (int i = 0; i < len; i++) {
    PReg* r = temps->at(i)->preg();
    if (r->uplevelR() || r->uplevelW() || (r->isBlockPReg() && !r->isUnused())) nused++;
  }
  if (nused == 0) {
    str->print("  could not eliminate context of scope %s (fixable compiler restriction; should be eliminated)\n", s->key()->print_string());
  } else {
    str->print("  could not eliminate context of scope %s; temp(s) still used: ", s->key()->print_string());
    for (int j = 0; j < len; j++) {
      PReg* r = temps->at(j)->preg();
      if (r->uplevelR() || r->uplevelW()) {
	str->print("%d ", j);
      } else if (r->isBlockPReg() && !r->isUnused()) {
	str->print("%d (non-inlined block)", j);
      }
    }
    str->print("\n");
  } 
}