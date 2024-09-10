bool MachObjectWriter::isSymbolRefDifferenceFullyResolvedImpl(
    const MCAssembler &Asm, const MCSymbol &SymA, const MCFragment &FB,
    bool InSet, bool IsPCRel) const {
  if (InSet)
    return true;

  // The effective address is
  //     addr(atom(A)) + offset(A)
  //   - addr(atom(B)) - offset(B)
  // and the offsets are not relocatable, so the fixup is fully resolved when
  //  addr(atom(A)) - addr(atom(B)) == 0.
  const MCSymbol &SA = findAliasedSymbol(SymA);
  const MCSection &SecA = SA.getSection();
  const MCSection &SecB = *FB.getParent();

  if (IsPCRel) {
    // The simple (Darwin, except on x86_64) way of dealing with this was to
    // assume that any reference to a temporary symbol *must* be a temporary
    // symbol in the same atom, unless the sections differ. Therefore, any PCrel
    // relocation to a temporary symbol (in the same section) is fully
    // resolved. This also works in conjunction with absolutized .set, which
    // requires the compiler to use .set to absolutize the differences between
    // symbols which the compiler knows to be assembly time constants, so we
    // don't need to worry about considering symbol differences fully resolved.
    //
    // If the file isn't using sub-sections-via-symbols, we can make the
    // same assumptions about any symbol that we normally make about
    // assembler locals.

    bool hasReliableSymbolDifference = isX86_64();
    if (!hasReliableSymbolDifference) {
      if (!SA.isInSection() || &SecA != &SecB ||
          (!SA.isTemporary() && FB.getAtom() != SA.getFragment()->getAtom() &&
           Asm.getSubsectionsViaSymbols()))
        return false;
      return true;
    }
    // For Darwin x86_64, there is one special case when the reference IsPCRel.
    // If the fragment with the reference does not have a base symbol but meets
    // the simple way of dealing with this, in that it is a temporary symbol in
    // the same atom then it is assumed to be fully resolved.  This is needed so
    // a relocation entry is not created and so the static linker does not
    // mess up the reference later.
    else if(!FB.getAtom() &&
            SA.isTemporary() && SA.isInSection() && &SecA == &SecB){
      return true;
    }
  }

  // If they are not in the same section, we can't compute the diff.
  if (&SecA != &SecB)
    return false;

  const MCFragment *FA = SA.getFragment();

  // Bail if the symbol has no fragment.
  if (!FA)
    return false;

  // If the atoms are the same, they are guaranteed to have the same address.
  if (FA->getAtom() == FB.getAtom())
    return true;

  // Otherwise, we can't prove this is fully resolved.
  return false;
}