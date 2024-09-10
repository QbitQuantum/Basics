bool Sema::ActOnSuperScopeSpecifier(SourceLocation SuperLoc,
                                    SourceLocation ColonColonLoc,
                                    CXXScopeSpec &SS) {
  CXXRecordDecl *RD = nullptr;
  for (Scope *S = getCurScope(); S; S = S->getParent()) {
    if (S->isFunctionScope()) {
      if (CXXMethodDecl *MD = dyn_cast<CXXMethodDecl>(S->getEntity()))
        RD = MD->getParent();
      break;
    }
    if (S->isClassScope()) {
      RD = cast<CXXRecordDecl>(S->getEntity());
      break;
    }
  }

  if (!RD) {
    Diag(SuperLoc, diag::err_invalid_super_scope);
    return true;
  } else if (RD->isLambda()) {
    Diag(SuperLoc, diag::err_super_in_lambda_unsupported);
    return true;
  } else if (RD->getNumBases() == 0) {
    Diag(SuperLoc, diag::err_no_base_classes) << RD->getName();
    return true;
  }

  SS.MakeSuper(Context, RD, SuperLoc, ColonColonLoc);
  return false;
}