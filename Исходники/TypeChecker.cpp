/// Ensure that the outer generic parameters of the given generic
/// context have been configured.
static void configureOuterGenericParams(const GenericContext *dc) {
  auto genericParams = dc->getGenericParams();

  // If we already configured the outer parameters, we're done.
  if (genericParams && genericParams->getOuterParameters())
    return;

  DeclContext *outerDC = dc->getParent();
  while (!outerDC->isModuleScopeContext()) {
    if (auto outerDecl = outerDC->getAsDecl()) {
      if (auto outerGenericDC = outerDecl->getAsGenericContext()) {
        if (genericParams)
          genericParams->setOuterParameters(outerGenericDC->getGenericParams());

        configureOuterGenericParams(outerGenericDC);
        return;
      }
    }

    outerDC = outerDC->getParent();
  }
}