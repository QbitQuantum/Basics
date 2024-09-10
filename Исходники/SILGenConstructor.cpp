void SILGenFunction::emitMemberInitializers(DeclContext *dc,
                                            VarDecl *selfDecl,
                                            NominalTypeDecl *nominal) {
  for (auto member : nominal->getMembers()) {
    // Find instance pattern binding declarations that have initializers.
    if (auto pbd = dyn_cast<PatternBindingDecl>(member)) {
      if (pbd->isStatic()) continue;

      for (auto entry : pbd->getPatternList()) {
        auto init = entry.getInit();
        if (!init) continue;

        // Cleanup after this initialization.
        FullExpr scope(Cleanups, entry.getPattern());

        // Get the substitutions for the constructor context.
        SubstitutionList subs;
        auto *genericEnv = dc->getGenericEnvironmentOfContext();

        DeclContext *typeDC = dc;
        while (!typeDC->isTypeContext())
          typeDC = typeDC->getParent();
        auto typeGenericSig = typeDC->getGenericSignatureOfContext();

        if (genericEnv && typeGenericSig) {
          // Generate a set of substitutions for the initialization function,
          // whose generic signature is that of the type context, and whose
          // replacement types are the archetypes of the initializer itself.
          SmallVector<Substitution, 4> subsVec;
          typeGenericSig->getSubstitutions(
                       [&](SubstitutableType *type) {
                         if (auto gp = type->getAs<GenericTypeParamType>()) {
                           return genericEnv->mapTypeIntoContext(gp);
                         }

                         return Type(type);
                       },
                       [](CanType dependentType,
                           Type conformingReplacementType,
                           ProtocolType *conformedProtocol) {
                         return ProtocolConformanceRef(
                                  conformedProtocol->getDecl());
                       },
                       subsVec);
          subs = SGM.getASTContext().AllocateCopy(subsVec);
        }

        // Get the type of the initialization result, in terms
        // of the constructor context's archetypes.
        CanType resultType = getInitializationTypeInContext(
            pbd->getDeclContext(), dc, entry.getPattern())->getCanonicalType();
        AbstractionPattern origResultType(resultType);

        // FIXME: Can emitMemberInit() share code with
        // InitializationForPattern in SILGenDecl.cpp?
        RValue result = emitApplyOfStoredPropertyInitializer(
                                  init, entry, subs,
                                  resultType, origResultType,
                                  SGFContext());

        emitMemberInit(*this, selfDecl, entry.getPattern(), std::move(result));
      }
    }
    
    // Introduce behavior initialization markers for properties that need them.
    if (auto var = dyn_cast<VarDecl>(member)) {
      if (var->isStatic()) continue;
      if (!var->hasBehaviorNeedingInitialization()) continue;
      
      // Get the initializer method for behavior.
      auto init = var->getBehavior()->InitStorageDecl;
      SILValue initFn = getBehaviorInitStorageFn(*this, var);
      
      // Get the behavior's storage we need to initialize.
      auto storage = var->getBehavior()->StorageDecl;
      LValue storageRef = emitLValueForMemberInit(*this, var, selfDecl,storage);
      // Shed any reabstraction over the member.
      while (storageRef.isLastComponentTranslation())
        storageRef.dropLastTranslationComponent();
      
      auto storageAddr = emitAddressOfLValue(var, std::move(storageRef),
                                             AccessKind::ReadWrite);
      
      // Get the setter.
      auto setterFn = getBehaviorSetterFn(*this, var);
      auto self = emitSelfForMemberInit(*this, var, selfDecl);
      
      auto mark = B.createMarkUninitializedBehavior(var,
               initFn, init.getSubstitutions(), storageAddr.getValue(),
               setterFn, getForwardingSubstitutions(), self.getValue(),
               getLoweredType(var->getType()).getAddressType());
      
      // The mark instruction stands in for the behavior property.
      VarLocs[var].value = mark;
    }
  }
}