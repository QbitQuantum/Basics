DeclContext *DeclContext::getInnermostTypeContext() {
  DeclContext *Result = this;
  while (true) {
    switch (Result->getContextKind()) {
    case DeclContextKind::AbstractClosureExpr:
    case DeclContextKind::Initializer:
    case DeclContextKind::TopLevelCodeDecl:
    case DeclContextKind::AbstractFunctionDecl:
    case DeclContextKind::SerializedLocal:
      Result = Result->getParent();
      continue;

    case DeclContextKind::Module:
    case DeclContextKind::FileUnit:
      return nullptr;

    case DeclContextKind::ExtensionDecl:
    case DeclContextKind::NominalTypeDecl:
      return Result;
    }
  }
}