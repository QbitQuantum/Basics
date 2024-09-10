static MCOperand GetSymbolRef(const MachineOperand &MO, const MCSymbol *Symbol,
                              AsmPrinter &Printer, bool isDarwin) {
  MCContext &Ctx = Printer.OutContext;
  MCSymbolRefExpr::VariantKind RefKind = MCSymbolRefExpr::VK_None;

  unsigned access = MO.getTargetFlags() & PPCII::MO_ACCESS_MASK;

  switch (access) {
    case PPCII::MO_TPREL_LO:
      RefKind = MCSymbolRefExpr::VK_PPC_TPREL_LO;
      break;
    case PPCII::MO_TPREL_HA:
      RefKind = MCSymbolRefExpr::VK_PPC_TPREL_HA;
      break;
    case PPCII::MO_DTPREL_LO:
      RefKind = MCSymbolRefExpr::VK_PPC_DTPREL_LO;
      break;
    case PPCII::MO_TLSLD_LO:
      RefKind = MCSymbolRefExpr::VK_PPC_GOT_TLSLD_LO;
      break;
    case PPCII::MO_TOC_LO:
      RefKind = MCSymbolRefExpr::VK_PPC_TOC_LO;
      break;
    case PPCII::MO_TLS:
      RefKind = MCSymbolRefExpr::VK_PPC_TLS;
      break;
    case PPCII::MO_TLSGD:
      RefKind = MCSymbolRefExpr::VK_PPC_TLSGD;
      break;
    case PPCII::MO_TLSLD:
      RefKind = MCSymbolRefExpr::VK_PPC_TLSLD;
      break;
  }

  if (MO.getTargetFlags() == PPCII::MO_PLT_OR_STUB && !isDarwin)
    RefKind = MCSymbolRefExpr::VK_PLT;

  const MCExpr *Expr = MCSymbolRefExpr::Create(Symbol, RefKind, Ctx);

  if (!MO.isJTI() && MO.getOffset())
    Expr = MCBinaryExpr::CreateAdd(Expr,
                                   MCConstantExpr::Create(MO.getOffset(), Ctx),
                                   Ctx);

  // Subtract off the PIC base if required.
  if (MO.getTargetFlags() & PPCII::MO_PIC_FLAG) {
    const MachineFunction *MF = MO.getParent()->getParent()->getParent();
    
    const MCExpr *PB = MCSymbolRefExpr::Create(MF->getPICBaseSymbol(), Ctx);
    Expr = MCBinaryExpr::CreateSub(Expr, PB, Ctx);
  }

  // Add ha16() / lo16() markers if required.
  switch (access) {
    case PPCII::MO_LO:
      Expr = PPCMCExpr::CreateLo(Expr, isDarwin, Ctx);
      break;
    case PPCII::MO_HA:
      Expr = PPCMCExpr::CreateHa(Expr, isDarwin, Ctx);
      break;
  }

  return MCOperand::CreateExpr(Expr);
}