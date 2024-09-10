static SourceLocation getValidSourceLocation(const Stmt* S,
                                             LocationOrAnalysisContext LAC) {
  SourceLocation L = S->getLocStart();
  assert(!LAC.isNull() && "A valid LocationContext or AnalysisContext should "
                          "be passed to PathDiagnosticLocation upon creation.");

  // S might be a temporary statement that does not have a location in the
  // source code, so find an enclosing statement and use it's location.
  if (!L.isValid()) {

    ParentMap *PM = 0;
    if (LAC.is<const LocationContext*>())
      PM = &LAC.get<const LocationContext*>()->getParentMap();
    else
      PM = &LAC.get<AnalysisContext*>()->getParentMap();

    while (!L.isValid()) {
      S = PM->getParent(S);
      L = S->getLocStart();
    }
  }

  return L;
}