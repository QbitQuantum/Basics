/// \brief Return the fully qualified type, including fully-qualified
/// versions of any template parameters.
QualType getFullyQualifiedType(QualType QT, const ASTContext &Ctx) {
  // In case of myType* we need to strip the pointer first, fully
  // qualify and attach the pointer once again.
  if (isa<PointerType>(QT.getTypePtr())) {
    // Get the qualifiers.
    Qualifiers Quals = QT.getQualifiers();
    QT = getFullyQualifiedType(QT->getPointeeType(), Ctx);
    QT = Ctx.getPointerType(QT);
    // Add back the qualifiers.
    QT = Ctx.getQualifiedType(QT, Quals);
    return QT;
  }

  // In case of myType& we need to strip the reference first, fully
  // qualify and attach the reference once again.
  if (isa<ReferenceType>(QT.getTypePtr())) {
    // Get the qualifiers.
    bool IsLValueRefTy = isa<LValueReferenceType>(QT.getTypePtr());
    Qualifiers Quals = QT.getQualifiers();
    QT = getFullyQualifiedType(QT->getPointeeType(), Ctx);
    // Add the r- or l-value reference type back to the fully
    // qualified one.
    if (IsLValueRefTy)
      QT = Ctx.getLValueReferenceType(QT);
    else
      QT = Ctx.getRValueReferenceType(QT);
    // Add back the qualifiers.
    QT = Ctx.getQualifiedType(QT, Quals);
    return QT;
  }

  // Remove the part of the type related to the type being a template
  // parameter (we won't report it as part of the 'type name' and it
  // is actually make the code below to be more complex (to handle
  // those)
  while (isa<SubstTemplateTypeParmType>(QT.getTypePtr())) {
    // Get the qualifiers.
    Qualifiers Quals = QT.getQualifiers();

    QT = dyn_cast<SubstTemplateTypeParmType>(QT.getTypePtr())->desugar();

    // Add back the qualifiers.
    QT = Ctx.getQualifiedType(QT, Quals);
  }

  NestedNameSpecifier *Prefix = nullptr;
  Qualifiers PrefixQualifiers;
  ElaboratedTypeKeyword Keyword = ETK_None;
  if (const auto *ETypeInput = dyn_cast<ElaboratedType>(QT.getTypePtr())) {
    QT = ETypeInput->getNamedType();
    Keyword = ETypeInput->getKeyword();
  }
  // Create a nested name specifier if needed (i.e. if the decl context
  // is not the global scope.
  Prefix = createNestedNameSpecifierForScopeOf(Ctx, QT.getTypePtr(),
                                               true /*FullyQualified*/);

  // move the qualifiers on the outer type (avoid 'std::const string'!)
  if (Prefix) {
    PrefixQualifiers = QT.getLocalQualifiers();
    QT = QualType(QT.getTypePtr(), 0);
  }

  // In case of template specializations iterate over the arguments and
  // fully qualify them as well.
  if (isa<const TemplateSpecializationType>(QT.getTypePtr()) ||
      isa<const RecordType>(QT.getTypePtr())) {
    // We are asked to fully qualify and we have a Record Type (which
    // may pont to a template specialization) or Template
    // Specialization Type. We need to fully qualify their arguments.

    Qualifiers Quals = QT.getLocalQualifiers();
    const Type *TypePtr = getFullyQualifiedTemplateType(Ctx, QT.getTypePtr());
    QT = Ctx.getQualifiedType(TypePtr, Quals);
  }
  if (Prefix || Keyword != ETK_None) {
    QT = Ctx.getElaboratedType(Keyword, Prefix, QT);
    QT = Ctx.getQualifiedType(QT, PrefixQualifiers);
  }
  return QT;
}