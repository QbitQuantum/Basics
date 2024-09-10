/// Starting at a given context (a Decl or DeclContext), look for a
/// code context that is not a closure (a lambda, block, etc.).
template <class T> static Decl *getNonClosureContext(T *D) {
  if (getKind(D) == Decl::CXXMethod) {
    CXXMethodDecl *MD = cast<CXXMethodDecl>(D);
    if (MD->getOverloadedOperator() == OO_Call &&
        MD->getParent()->isLambda())
      return getNonClosureContext(MD->getParent()->getParent());
    return MD;
  } else if (FunctionDecl *FD = dyn_cast<FunctionDecl>(D)) {
    return FD;
  } else if (ObjCMethodDecl *MD = dyn_cast<ObjCMethodDecl>(D)) {
    return MD;
  } else if (BlockDecl *BD = dyn_cast<BlockDecl>(D)) {
    return getNonClosureContext(BD->getParent());
  } else if (CapturedDecl *CD = dyn_cast<CapturedDecl>(D)) {
    return getNonClosureContext(CD->getParent());
  } else {
    return 0;
  }
}