  bool DynamicIDHandler::IsDynamicLookup (LookupResult& R, Scope* S) {
    if (R.getLookupKind() != Sema::LookupOrdinaryName) return false;
    if (R.isForRedeclaration()) return false;
    // FIXME: Figure out better way to handle:
    // C++ [basic.lookup.classref]p1:
    //   In a class member access expression (5.2.5), if the . or -> token is
    //   immediately followed by an identifier followed by a <, the
    //   identifier must be looked up to determine whether the < is the
    //   beginning of a template argument list (14.2) or a less-than operator.
    //   The identifier is first looked up in the class of the object
    //   expression. If the identifier is not found, it is then looked up in
    //   the context of the entire postfix-expression and shall name a class
    //   or function template.
    //
    // We want to ignore object(.|->)member<template>
    if (m_Sema->PP.LookAhead(0).getKind() == tok::less)
      // TODO: check for . or -> in the cached token stream
      return false;

    for (Scope* DepScope = S; DepScope; DepScope = DepScope->getParent()) {
      if (DeclContext* Ctx = static_cast<DeclContext*>(DepScope->getEntity())) {
        return !Ctx->isDependentContext();
      }
    }

    return true;
  }