// R_386_PLT32: PLT(S) + A - P
X86RelocationFactory::Result plt32(Relocation& pReloc,
                                   const MCLDInfo& pLDInfo,
                                   X86RelocationFactory& pParent)
{
  // PLT_S depends on if there is a PLT entry.
  X86RelocationFactory::Address PLT_S;
  if((pReloc.symInfo()->reserved() & X86GNULDBackend::ReservePLT))
    PLT_S = helper_PLT(pReloc, pParent);
  else
    PLT_S = pReloc.symValue();
  RelocationFactory::DWord   A       = pReloc.target() + pReloc.addend();
  X86RelocationFactory::Address P = pReloc.place(pParent.getLayout());
  pReloc.target() = PLT_S + A - P;
  return X86RelocationFactory::OK;
}