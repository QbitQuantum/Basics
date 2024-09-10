SILLinkage SILDeclRef::getLinkage(ForDefinition_t forDefinition) const {
  if (getAbstractClosureExpr()) {
    return isSerialized() ? SILLinkage::Shared : SILLinkage::Private;
  }

  // Add External to the linkage (e.g. Public -> PublicExternal) if this is a
  // declaration not a definition.
  auto maybeAddExternal = [&](SILLinkage linkage) {
    return forDefinition ? linkage : addExternalToLinkage(linkage);
  };

  // Native function-local declarations have shared linkage.
  // FIXME: @objc declarations should be too, but we currently have no way
  // of marking them "used" other than making them external. 
  ValueDecl *d = getDecl();
  DeclContext *moduleContext = d->getDeclContext();
  while (!moduleContext->isModuleScopeContext()) {
    if (!isForeign && moduleContext->isLocalContext()) {
      return isSerialized() ? SILLinkage::Shared : SILLinkage::Private;
    }
    moduleContext = moduleContext->getParent();
  }

  // Enum constructors and curry thunks either have private or shared
  // linkage, dependings are essentially the same as thunks, they are
  // emitted by need and have shared linkage.
  if (isEnumElement() || isCurried) {
    switch (d->getEffectiveAccess()) {
    case AccessLevel::Private:
    case AccessLevel::FilePrivate:
      return maybeAddExternal(SILLinkage::Private);

    case AccessLevel::Internal:
    case AccessLevel::Public:
    case AccessLevel::Open:
      return SILLinkage::Shared;
    }
  }

  // Calling convention thunks have shared linkage.
  if (isForeignToNativeThunk())
    return SILLinkage::Shared;

  // If a function declares a @_cdecl name, its native-to-foreign thunk
  // is exported with the visibility of the function.
  if (isNativeToForeignThunk() && !d->getAttrs().hasAttribute<CDeclAttr>())
    return SILLinkage::Shared;

  // Declarations imported from Clang modules have shared linkage.
  if (isClangImported())
    return SILLinkage::Shared;

  // Default argument generators of Public functions have PublicNonABI linkage
  // if the function was type-checked in Swift 4 mode.
  if (kind == SILDeclRef::Kind::DefaultArgGenerator) {
    if (isSerialized())
      return maybeAddExternal(SILLinkage::PublicNonABI);
  }

  enum class Limit {
    /// No limit.
    None,
    /// The declaration is emitted on-demand; it should end up with internal
    /// or shared linkage.
    OnDemand,
    /// The declaration should never be made public.
    NeverPublic 
  };
  auto limit = Limit::None;

  // ivar initializers and destroyers are completely contained within the class
  // from which they come, and never get seen externally.
  if (isIVarInitializerOrDestroyer()) {
    limit = Limit::NeverPublic;
  }

  // Stored property initializers get the linkage of their containing type.
  if (isStoredPropertyInitializer()) {
    // Three cases:
    //
    // 1) Type is formally @_fixed_layout. Root initializers can be declared
    //    @inlinable. The property initializer must only reference
    //    public symbols, and is serialized, so we give it PublicNonABI linkage.
    //
    // 2) Type is not formally @_fixed_layout and the module is not resilient.
    //    Root initializers can be declared @inlinable. This is the annoying
    //    case. We give the initializer public linkage if the type is public.
    //
    // 3) Type is resilient. The property initializer is never public because
    //    root initializers cannot be @inlinable.
    //
    // FIXME: Get rid of case 2 somehow.
    if (isSerialized())
      return maybeAddExternal(SILLinkage::PublicNonABI);

    d = cast<NominalTypeDecl>(d->getDeclContext());

    // FIXME: This should always be true.
    if (d->getDeclContext()->getParentModule()->getResilienceStrategy() ==
        ResilienceStrategy::Resilient)
      limit = Limit::NeverPublic;
  }

  // The global addressor is never public for resilient globals.
  if (kind == Kind::GlobalAccessor) {
    if (cast<VarDecl>(d)->isResilient()) {
      limit = Limit::NeverPublic;
    }
  }

  // Forced-static-dispatch functions are created on-demand and have
  // at best shared linkage.
  if (auto fn = dyn_cast<FuncDecl>(d)) {
    if (fn->hasForcedStaticDispatch()) {
      limit = Limit::OnDemand;
    }
  }
  
  auto effectiveAccess = d->getEffectiveAccess();
  
  // Private setter implementations for an internal storage declaration should
  // be internal as well, so that a dynamically-writable
  // keypath can be formed from other files.
  if (auto accessor = dyn_cast<AccessorDecl>(d)) {
    if (accessor->isSetter()
       && accessor->getStorage()->getEffectiveAccess() == AccessLevel::Internal)
      effectiveAccess = AccessLevel::Internal;
  }

  switch (effectiveAccess) {
  case AccessLevel::Private:
  case AccessLevel::FilePrivate:
    return maybeAddExternal(SILLinkage::Private);

  case AccessLevel::Internal:
    if (limit == Limit::OnDemand)
      return SILLinkage::Shared;
    return maybeAddExternal(SILLinkage::Hidden);

  case AccessLevel::Public:
  case AccessLevel::Open:
    if (limit == Limit::OnDemand)
      return SILLinkage::Shared;
    if (limit == Limit::NeverPublic)
      return maybeAddExternal(SILLinkage::Hidden);
    return maybeAddExternal(SILLinkage::Public);
  }
  llvm_unreachable("unhandled access");
}