SILType RValue::getLoweredImplodedTupleType(SILGenFunction &SGF) const & {
  SILType loweredType = getLoweredType(SGF);
  if (loweredType.isAddressOnly(SGF.getModule()) &&
      SGF.silConv.useLoweredAddresses())
    return loweredType.getAddressType();
  return loweredType.getObjectType();
}