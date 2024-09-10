bool AMDGPUMCInstLower::lowerOperand(const MachineOperand &MO,
                                     MCOperand &MCOp) const {
  switch (MO.getType()) {
  default:
    llvm_unreachable("unknown operand type");
  case MachineOperand::MO_Immediate:
    MCOp = MCOperand::createImm(MO.getImm());
    return true;
  case MachineOperand::MO_Register:
    MCOp = MCOperand::createReg(AMDGPU::getMCReg(MO.getReg(), ST));
    return true;
  case MachineOperand::MO_MachineBasicBlock: {
    if (MO.getTargetFlags() != 0) {
      MCOp = MCOperand::createExpr(
        getLongBranchBlockExpr(*MO.getParent()->getParent(), MO));
    } else {
      MCOp = MCOperand::createExpr(
        MCSymbolRefExpr::create(MO.getMBB()->getSymbol(), Ctx));
    }

    return true;
  }
  case MachineOperand::MO_GlobalAddress: {
    const GlobalValue *GV = MO.getGlobal();
    SmallString<128> SymbolName;
    AP.getNameWithPrefix(SymbolName, GV);
    MCSymbol *Sym = Ctx.getOrCreateSymbol(SymbolName);
    const MCExpr *SymExpr =
      MCSymbolRefExpr::create(Sym, getVariantKind(MO.getTargetFlags()),Ctx);
    const MCExpr *Expr = MCBinaryExpr::createAdd(SymExpr,
      MCConstantExpr::create(MO.getOffset(), Ctx), Ctx);
    MCOp = MCOperand::createExpr(Expr);
    return true;
  }
  case MachineOperand::MO_ExternalSymbol: {
    MCSymbol *Sym = Ctx.getOrCreateSymbol(StringRef(MO.getSymbolName()));
    Sym->setExternal(true);
    const MCSymbolRefExpr *Expr = MCSymbolRefExpr::create(Sym, Ctx);
    MCOp = MCOperand::createExpr(Expr);
    return true;
  }
  }
}