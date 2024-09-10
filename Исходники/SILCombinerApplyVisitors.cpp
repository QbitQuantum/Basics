/// Returns the address of an object with which the stack location \p ASI is
/// initialized. This is either a init_existential_addr or the source of a
/// copy_addr. Returns a null value if the address does not dominate the
/// alloc_stack user \p ASIUser.
static SILValue getAddressOfStackInit(AllocStackInst *ASI,
                                      SILInstruction *ASIUser) {
    SILInstruction *SingleWrite = nullptr;
    // Check that this alloc_stack is initialized only once.
    for (auto Use : ASI->getUses()) {
        auto *User = Use->getUser();

        // Ignore instructions which don't write to the stack location.
        // Also ignore ASIUser (only kicks in if ASIUser is the original apply).
        if (isa<DeallocStackInst>(User) || isa<DebugValueAddrInst>(User) ||
                isa<DestroyAddrInst>(User) || isa<WitnessMethodInst>(User) ||
                isa<DeinitExistentialAddrInst>(User) ||
                isa<OpenExistentialAddrInst>(User) ||
                User == ASIUser) {
            continue;
        }
        if (auto *CAI = dyn_cast<CopyAddrInst>(User)) {
            if (CAI->getDest() == ASI) {
                if (SingleWrite)
                    return SILValue();
                SingleWrite = CAI;
            }
            continue;
        }
        if (isa<InitExistentialAddrInst>(User)) {
            if (SingleWrite)
                return SILValue();
            SingleWrite = User;
            continue;
        }
        if (isa<ApplyInst>(User) || isa<TryApplyInst>(User)) {
            // Ignore function calls which do not write to the stack location.
            auto Idx = Use->getOperandNumber() - ApplyInst::getArgumentOperandNumber();
            auto Conv = FullApplySite(User).getArgumentConvention(Idx);
            if (Conv != SILArgumentConvention::Indirect_In &&
                    Conv != SILArgumentConvention::Indirect_In_Guaranteed)
                return SILValue();
            continue;
        }
        // Bail if there is any unknown (and potentially writing) instruction.
        return SILValue();
    }
    if (!SingleWrite)
        return SILValue();

    // A very simple dominance check. As ASI is an operand of ASIUser,
    // SingleWrite dominates ASIUser if it is in the same block as ASI or ASIUser.
    SILBasicBlock *BB = SingleWrite->getParent();
    if (BB != ASI->getParent() && BB != ASIUser->getParent())
        return SILValue();

    if (auto *CAI = dyn_cast<CopyAddrInst>(SingleWrite)) {
        // Try to derive the type from the copy_addr that was used to
        // initialize the alloc_stack.
        SILValue CAISrc = CAI->getSrc();
        if (auto *ASI = dyn_cast<AllocStackInst>(CAISrc))
            return getAddressOfStackInit(ASI, CAI);
        return CAISrc;
    }
    return SingleWrite;
}