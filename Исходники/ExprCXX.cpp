CXXPseudoDestructorExpr::CXXPseudoDestructorExpr(ASTContext &Context,
                Expr *Base, bool isArrow, SourceLocation OperatorLoc,
                NestedNameSpecifierLoc QualifierLoc, TypeSourceInfo *ScopeType, 
                SourceLocation ColonColonLoc, SourceLocation TildeLoc, 
                PseudoDestructorTypeStorage DestroyedType)
  : Expr(CXXPseudoDestructorExprClass,
         Context.getPointerType(Context.getFunctionType(Context.VoidTy, 0, 0,
                                         FunctionProtoType::ExtProtoInfo())),
         VK_RValue, OK_Ordinary,
         /*isTypeDependent=*/(Base->isTypeDependent() ||
           (DestroyedType.getTypeSourceInfo() &&
            DestroyedType.getTypeSourceInfo()->getType()->isDependentType())),
         /*isValueDependent=*/Base->isValueDependent(),
         (Base->isInstantiationDependent() ||
          (QualifierLoc &&
           QualifierLoc.getNestedNameSpecifier()->isInstantiationDependent()) ||
          (ScopeType &&
           ScopeType->getType()->isInstantiationDependentType()) ||
          (DestroyedType.getTypeSourceInfo() &&
           DestroyedType.getTypeSourceInfo()->getType()
                                             ->isInstantiationDependentType())),
         // ContainsUnexpandedParameterPack
         (Base->containsUnexpandedParameterPack() ||
          (QualifierLoc && 
           QualifierLoc.getNestedNameSpecifier()
                                        ->containsUnexpandedParameterPack()) ||
          (ScopeType && 
           ScopeType->getType()->containsUnexpandedParameterPack()) ||
          (DestroyedType.getTypeSourceInfo() &&
           DestroyedType.getTypeSourceInfo()->getType()
                                   ->containsUnexpandedParameterPack()))),
    Base(static_cast<Stmt *>(Base)), IsArrow(isArrow),
    OperatorLoc(OperatorLoc), QualifierLoc(QualifierLoc),
    ScopeType(ScopeType), ColonColonLoc(ColonColonLoc), TildeLoc(TildeLoc),
    DestroyedType(DestroyedType) { }