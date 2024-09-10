void MIPrinter::print(const MachineOperand &Op, const TargetRegisterInfo *TRI,
                      unsigned I, bool ShouldPrintRegisterTies, LLT TypeToPrint,
                      bool IsDef) {
  printTargetFlags(Op);
  switch (Op.getType()) {
  case MachineOperand::MO_Register:
    if (Op.isImplicit())
      OS << (Op.isDef() ? "implicit-def " : "implicit ");
    else if (!IsDef && Op.isDef())
      // Print the 'def' flag only when the operand is defined after '='.
      OS << "def ";
    if (Op.isInternalRead())
      OS << "internal ";
    if (Op.isDead())
      OS << "dead ";
    if (Op.isKill())
      OS << "killed ";
    if (Op.isUndef())
      OS << "undef ";
    if (Op.isEarlyClobber())
      OS << "early-clobber ";
    if (Op.isDebug())
      OS << "debug-use ";
    printReg(Op.getReg(), OS, TRI);
    // Print the sub register.
    if (Op.getSubReg() != 0)
      OS << '.' << TRI->getSubRegIndexName(Op.getSubReg());
    if (ShouldPrintRegisterTies && Op.isTied() && !Op.isDef())
      OS << "(tied-def " << Op.getParent()->findTiedOperandIdx(I) << ")";
    if (TypeToPrint.isValid())
      OS << '(' << TypeToPrint << ')';
    break;
  case MachineOperand::MO_Immediate:
    OS << Op.getImm();
    break;
  case MachineOperand::MO_CImmediate:
    Op.getCImm()->printAsOperand(OS, /*PrintType=*/true, MST);
    break;
  case MachineOperand::MO_FPImmediate:
    Op.getFPImm()->printAsOperand(OS, /*PrintType=*/true, MST);
    break;
  case MachineOperand::MO_MachineBasicBlock:
    printMBBReference(*Op.getMBB());
    break;
  case MachineOperand::MO_FrameIndex:
    printStackObjectReference(Op.getIndex());
    break;
  case MachineOperand::MO_ConstantPoolIndex:
    OS << "%const." << Op.getIndex();
    printOffset(Op.getOffset());
    break;
  case MachineOperand::MO_TargetIndex:
    OS << "target-index(";
    if (const auto *Name = getTargetIndexName(
            *Op.getParent()->getParent()->getParent(), Op.getIndex()))
      OS << Name;
    else
      OS << "<unknown>";
    OS << ')';
    printOffset(Op.getOffset());
    break;
  case MachineOperand::MO_JumpTableIndex:
    OS << "%jump-table." << Op.getIndex();
    break;
  case MachineOperand::MO_ExternalSymbol: {
    StringRef Name = Op.getSymbolName();
    OS << '$';
    if (Name.empty()) {
      OS << "\"\"";
    } else {
      printLLVMNameWithoutPrefix(OS, Name);
    }
    printOffset(Op.getOffset());
    break;
  }
  case MachineOperand::MO_GlobalAddress:
    Op.getGlobal()->printAsOperand(OS, /*PrintType=*/false, MST);
    printOffset(Op.getOffset());
    break;
  case MachineOperand::MO_BlockAddress:
    OS << "blockaddress(";
    Op.getBlockAddress()->getFunction()->printAsOperand(OS, /*PrintType=*/false,
                                                        MST);
    OS << ", ";
    printIRBlockReference(*Op.getBlockAddress()->getBasicBlock());
    OS << ')';
    printOffset(Op.getOffset());
    break;
  case MachineOperand::MO_RegisterMask: {
    auto RegMaskInfo = RegisterMaskIds.find(Op.getRegMask());
    if (RegMaskInfo != RegisterMaskIds.end())
      OS << StringRef(TRI->getRegMaskNames()[RegMaskInfo->second]).lower();
    else
      printCustomRegMask(Op.getRegMask(), OS, TRI);
    break;
  }
  case MachineOperand::MO_RegisterLiveOut: {
    const uint32_t *RegMask = Op.getRegLiveOut();
    OS << "liveout(";
    bool IsCommaNeeded = false;
    for (unsigned Reg = 0, E = TRI->getNumRegs(); Reg < E; ++Reg) {
      if (RegMask[Reg / 32] & (1U << (Reg % 32))) {
        if (IsCommaNeeded)
          OS << ", ";
        printReg(Reg, OS, TRI);
        IsCommaNeeded = true;
      }
    }
    OS << ")";
    break;
  }
  case MachineOperand::MO_Metadata:
    Op.getMetadata()->printAsOperand(OS, MST);
    break;
  case MachineOperand::MO_MCSymbol:
    OS << "<mcsymbol " << *Op.getMCSymbol() << ">";
    break;
  case MachineOperand::MO_CFIIndex: {
    const MachineFunction &MF = *Op.getParent()->getParent()->getParent();
    print(MF.getFrameInstructions()[Op.getCFIIndex()], TRI);
    break;
  }
  case MachineOperand::MO_IntrinsicID: {
    Intrinsic::ID ID = Op.getIntrinsicID();
    if (ID < Intrinsic::num_intrinsics)
      OS << "intrinsic(@" << Intrinsic::getName(ID, None) << ')';
    else {
      const MachineFunction &MF = *Op.getParent()->getParent()->getParent();
      const TargetIntrinsicInfo *TII = MF.getTarget().getIntrinsicInfo();
      OS << "intrinsic(@" << TII->getName(ID) << ')';
    }
    break;
  }
  case MachineOperand::MO_Predicate: {
    auto Pred = static_cast<CmpInst::Predicate>(Op.getPredicate());
    OS << (CmpInst::isIntPredicate(Pred) ? "int" : "float") << "pred("
       << CmpInst::getPredicateName(Pred) << ')';
    break;
  }
  }
}