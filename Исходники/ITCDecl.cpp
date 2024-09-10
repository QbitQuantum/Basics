//===----------------------------------------------------------------------===//
// Inheritance clause handling
//===----------------------------------------------------------------------===//
static std::tuple<TypeResolutionOptions, DeclContext *,
                  MutableArrayRef<TypeLoc>>
decomposeInheritedClauseDecl(
  llvm::PointerUnion<TypeDecl *, ExtensionDecl *> decl) {
  TypeResolutionOptions options;
  DeclContext *dc;
  MutableArrayRef<TypeLoc> inheritanceClause;
  if (auto typeDecl = decl.dyn_cast<TypeDecl *>()) {
    inheritanceClause = typeDecl->getInherited();
    if (auto nominal = dyn_cast<NominalTypeDecl>(typeDecl)) {
      dc = nominal;
      options |= TypeResolutionFlags::GenericSignature;
      options |= TypeResolutionFlags::InheritanceClause;
      options |= TypeResolutionFlags::AllowUnavailableProtocol;
    } else {
      dc = typeDecl->getDeclContext();

      if (isa<GenericTypeParamDecl>(typeDecl)) {
        // For generic parameters, we want name lookup to look at just the
        // signature of the enclosing entity.
        if (auto nominal = dyn_cast<NominalTypeDecl>(dc)) {
          dc = nominal;
          options |= TypeResolutionFlags::GenericSignature;
        } else if (auto ext = dyn_cast<ExtensionDecl>(dc)) {
          dc = ext;
          options |= TypeResolutionFlags::GenericSignature;
        } else if (auto func = dyn_cast<AbstractFunctionDecl>(dc)) {
          dc = func;
          options |= TypeResolutionFlags::GenericSignature;
        } else if (!dc->isModuleScopeContext()) {
          // Skip the generic parameter's context entirely.
          dc = dc->getParent();
        }
      }
    }
  } else {
    auto ext = decl.get<ExtensionDecl *>();
    inheritanceClause = ext->getInherited();
    dc = ext;
    options |= TypeResolutionFlags::GenericSignature;
    options |= TypeResolutionFlags::InheritanceClause;
    options |= TypeResolutionFlags::AllowUnavailableProtocol;
  }

  return std::make_tuple(options, dc, inheritanceClause);
}