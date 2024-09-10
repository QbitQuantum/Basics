// FIXME: With some changes to their callers, all of the below functions
// could be re-worked to use emitInjectEnum().
ManagedValue
SILGenFunction::emitInjectOptional(SILLocation loc,
                                   ManagedValue v,
                                   CanType inputFormalType,
                                   CanType substFormalType,
                                   const TypeLowering &expectedTL,
                                   SGFContext ctxt) {
  // Optional's payload is currently maximally abstracted. FIXME: Eventually
  // it shouldn't be.
  auto opaque = AbstractionPattern::getOpaque();

  OptionalTypeKind substOTK;
  auto substObjectType = substFormalType.getAnyOptionalObjectType(substOTK);

  auto loweredTy = getLoweredType(opaque, substObjectType);
  if (v.getType() != loweredTy)
    v = emitTransformedValue(loc, v,
                             AbstractionPattern(inputFormalType), inputFormalType,
                             opaque, substObjectType);

  auto someDecl = getASTContext().getOptionalSomeDecl(substOTK);
  SILType optTy = getLoweredType(substFormalType);
  if (v.getType().isAddress()) {
    auto buf = getBufferForExprResult(loc, optTy.getObjectType(), ctxt);
    auto payload = B.createInitEnumDataAddr(loc, buf, someDecl,
                                            v.getType());
    // FIXME: Is it correct to use IsTake here even if v doesn't have a cleanup?
    B.createCopyAddr(loc, v.forward(*this), payload,
                     IsTake, IsInitialization);
    B.createInjectEnumAddr(loc, buf, someDecl);
    v = manageBufferForExprResult(buf, expectedTL, ctxt);
  } else {
    auto some = B.createEnum(loc, v.getValue(), someDecl, optTy);
    v = ManagedValue(some, v.getCleanup());
  }

  return v;
}