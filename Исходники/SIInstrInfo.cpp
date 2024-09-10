void SIInstrInfo::moveToVALU(MachineInstr &TopInst) const {
  SmallVector<MachineInstr *, 128> Worklist;
  Worklist.push_back(&TopInst);

  while (!Worklist.empty()) {
    MachineInstr *Inst = Worklist.pop_back_val();
    unsigned NewOpcode = getVALUOp(*Inst);
    if (NewOpcode == AMDGPU::INSTRUCTION_LIST_END)
      continue;

    MachineRegisterInfo &MRI = Inst->getParent()->getParent()->getRegInfo();

    // Use the new VALU Opcode.
    const MCInstrDesc &NewDesc = get(NewOpcode);
    Inst->setDesc(NewDesc);

    // Remove any references to SCC. Vector instructions can't read from it, and
    // We're just about to add the implicit use / defs of VCC, and we don't want
    // both.
    for (unsigned i = Inst->getNumOperands() - 1; i > 0; --i) {
      MachineOperand &Op = Inst->getOperand(i);
      if (Op.isReg() && Op.getReg() == AMDGPU::SCC)
        Inst->RemoveOperand(i);
    }

    // Add the implict and explicit register definitions.
    if (NewDesc.ImplicitUses) {
      for (unsigned i = 0; NewDesc.ImplicitUses[i]; ++i) {
        unsigned Reg = NewDesc.ImplicitUses[i];
        Inst->addOperand(MachineOperand::CreateReg(Reg, false, true));
      }
    }

    if (NewDesc.ImplicitDefs) {
      for (unsigned i = 0; NewDesc.ImplicitDefs[i]; ++i) {
        unsigned Reg = NewDesc.ImplicitDefs[i];
        Inst->addOperand(MachineOperand::CreateReg(Reg, true, true));
      }
    }

    legalizeOperands(Inst);

    // Update the destination register class.
    const TargetRegisterClass *NewDstRC = getOpRegClass(*Inst, 0);

    switch (Inst->getOpcode()) {
      // For target instructions, getOpRegClass just returns the virtual
      // register class associated with the operand, so we need to find an
      // equivalent VGPR register class in order to move the instruction to the
      // VALU.
    case AMDGPU::COPY:
    case AMDGPU::PHI:
    case AMDGPU::REG_SEQUENCE:
      if (RI.hasVGPRs(NewDstRC))
        continue;
      NewDstRC = RI.getEquivalentVGPRClass(NewDstRC);
      if (!NewDstRC)
        continue;
      break;
    default:
      break;
    }

    unsigned DstReg = Inst->getOperand(0).getReg();
    unsigned NewDstReg = MRI.createVirtualRegister(NewDstRC);
    MRI.replaceRegWith(DstReg, NewDstReg);

    for (MachineRegisterInfo::use_iterator I = MRI.use_begin(NewDstReg),
           E = MRI.use_end(); I != E; ++I) {
      MachineInstr &UseMI = *I;
      if (!canReadVGPR(UseMI, I.getOperandNo())) {
        Worklist.push_back(&UseMI);
      }
    }
  }
}