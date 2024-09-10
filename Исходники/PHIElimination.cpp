/// LowerPHINode - Lower the PHI node at the top of the specified block,
///
void PHIElimination::LowerPHINode(MachineBasicBlock &MBB,
                                  MachineBasicBlock::iterator LastPHIIt) {
    ++NumLowered;

    MachineBasicBlock::iterator AfterPHIsIt = llvm::next(LastPHIIt);

    // Unlink the PHI node from the basic block, but don't delete the PHI yet.
    MachineInstr *MPhi = MBB.remove(MBB.begin());

    unsigned NumSrcs = (MPhi->getNumOperands() - 1) / 2;
    unsigned DestReg = MPhi->getOperand(0).getReg();
    assert(MPhi->getOperand(0).getSubReg() == 0 && "Can't handle sub-reg PHIs");
    bool isDead = MPhi->getOperand(0).isDead();

    // Create a new register for the incoming PHI arguments.
    MachineFunction &MF = *MBB.getParent();
    unsigned IncomingReg = 0;
    bool reusedIncoming = false;  // Is IncomingReg reused from an earlier PHI?

    // Insert a register to register copy at the top of the current block (but
    // after any remaining phi nodes) which copies the new incoming register
    // into the phi node destination.
    const TargetInstrInfo *TII = MF.getTarget().getInstrInfo();
    if (isSourceDefinedByImplicitDef(MPhi, MRI))
        // If all sources of a PHI node are implicit_def, just emit an
        // implicit_def instead of a copy.
        BuildMI(MBB, AfterPHIsIt, MPhi->getDebugLoc(),
                TII->get(TargetOpcode::IMPLICIT_DEF), DestReg);
    else {
        // Can we reuse an earlier PHI node? This only happens for critical edges,
        // typically those created by tail duplication.
        unsigned &entry = LoweredPHIs[MPhi];
        if (entry) {
            // An identical PHI node was already lowered. Reuse the incoming register.
            IncomingReg = entry;
            reusedIncoming = true;
            ++NumReused;
            DEBUG(dbgs() << "Reusing " << PrintReg(IncomingReg) << " for " << *MPhi);
        } else {
            const TargetRegisterClass *RC = MF.getRegInfo().getRegClass(DestReg);
            entry = IncomingReg = MF.getRegInfo().createVirtualRegister(RC);
        }
        BuildMI(MBB, AfterPHIsIt, MPhi->getDebugLoc(),
                TII->get(TargetOpcode::COPY), DestReg)
        .addReg(IncomingReg);
    }

    // Update live variable information if there is any.
    if (LV) {
        MachineInstr *PHICopy = prior(AfterPHIsIt);

        if (IncomingReg) {
            LiveVariables::VarInfo &VI = LV->getVarInfo(IncomingReg);

            // Increment use count of the newly created virtual register.
            LV->setPHIJoin(IncomingReg);

            // When we are reusing the incoming register, it may already have been
            // killed in this block. The old kill will also have been inserted at
            // AfterPHIsIt, so it appears before the current PHICopy.
            if (reusedIncoming)
                if (MachineInstr *OldKill = VI.findKill(&MBB)) {
                    DEBUG(dbgs() << "Remove old kill from " << *OldKill);
                    LV->removeVirtualRegisterKilled(IncomingReg, OldKill);
                    DEBUG(MBB.dump());
                }

            // Add information to LiveVariables to know that the incoming value is
            // killed.  Note that because the value is defined in several places (once
            // each for each incoming block), the "def" block and instruction fields
            // for the VarInfo is not filled in.
            LV->addVirtualRegisterKilled(IncomingReg, PHICopy);
        }

        // Since we are going to be deleting the PHI node, if it is the last use of
        // any registers, or if the value itself is dead, we need to move this
        // information over to the new copy we just inserted.
        LV->removeVirtualRegistersKilled(MPhi);

        // If the result is dead, update LV.
        if (isDead) {
            LV->addVirtualRegisterDead(DestReg, PHICopy);
            LV->removeVirtualRegisterDead(DestReg, MPhi);
        }
    }

    // Update LiveIntervals for the new copy or implicit def.
    if (LIS) {
        MachineInstr *NewInstr = prior(AfterPHIsIt);
        SlotIndex DestCopyIndex = LIS->InsertMachineInstrInMaps(NewInstr);

        SlotIndex MBBStartIndex = LIS->getMBBStartIdx(&MBB);
        if (IncomingReg) {
            // Add the region from the beginning of MBB to the copy instruction to
            // IncomingReg's live interval.
            LiveInterval &IncomingLI = LIS->getOrCreateInterval(IncomingReg);
            VNInfo *IncomingVNI = IncomingLI.getVNInfoAt(MBBStartIndex);
            if (!IncomingVNI)
                IncomingVNI = IncomingLI.getNextValue(MBBStartIndex,
                                                      LIS->getVNInfoAllocator());
            IncomingLI.addRange(LiveRange(MBBStartIndex,
                                          DestCopyIndex.getRegSlot(),
                                          IncomingVNI));
        }

        LiveInterval &DestLI = LIS->getInterval(DestReg);
        assert(DestLI.begin() != DestLI.end() &&
               "PHIs should have nonempty LiveIntervals.");
        if (DestLI.endIndex().isDead()) {
            // A dead PHI's live range begins and ends at the start of the MBB, but
            // the lowered copy, which will still be dead, needs to begin and end at
            // the copy instruction.
            VNInfo *OrigDestVNI = DestLI.getVNInfoAt(MBBStartIndex);
            assert(OrigDestVNI && "PHI destination should be live at block entry.");
            DestLI.removeRange(MBBStartIndex, MBBStartIndex.getDeadSlot());
            DestLI.createDeadDef(DestCopyIndex.getRegSlot(),
                                 LIS->getVNInfoAllocator());
            DestLI.removeValNo(OrigDestVNI);
        } else {
            // Otherwise, remove the region from the beginning of MBB to the copy
            // instruction from DestReg's live interval.
            DestLI.removeRange(MBBStartIndex, DestCopyIndex.getRegSlot());
            VNInfo *DestVNI = DestLI.getVNInfoAt(DestCopyIndex.getRegSlot());
            assert(DestVNI && "PHI destination should be live at its definition.");
            DestVNI->def = DestCopyIndex.getRegSlot();
        }
    }

    // Adjust the VRegPHIUseCount map to account for the removal of this PHI node.
    for (unsigned i = 1; i != MPhi->getNumOperands(); i += 2)
        --VRegPHIUseCount[BBVRegPair(MPhi->getOperand(i+1).getMBB()->getNumber(),
                                     MPhi->getOperand(i).getReg())];

    // Now loop over all of the incoming arguments, changing them to copy into the
    // IncomingReg register in the corresponding predecessor basic block.
    SmallPtrSet<MachineBasicBlock*, 8> MBBsInsertedInto;
    for (int i = NumSrcs - 1; i >= 0; --i) {
        unsigned SrcReg = MPhi->getOperand(i*2+1).getReg();
        unsigned SrcSubReg = MPhi->getOperand(i*2+1).getSubReg();
        bool SrcUndef = MPhi->getOperand(i*2+1).isUndef() ||
                        isImplicitlyDefined(SrcReg, MRI);
        assert(TargetRegisterInfo::isVirtualRegister(SrcReg) &&
               "Machine PHI Operands must all be virtual registers!");

        // Get the MachineBasicBlock equivalent of the BasicBlock that is the source
        // path the PHI.
        MachineBasicBlock &opBlock = *MPhi->getOperand(i*2+2).getMBB();

        // Check to make sure we haven't already emitted the copy for this block.
        // This can happen because PHI nodes may have multiple entries for the same
        // basic block.
        if (!MBBsInsertedInto.insert(&opBlock))
            continue;  // If the copy has already been emitted, we're done.

        // Find a safe location to insert the copy, this may be the first terminator
        // in the block (or end()).
        MachineBasicBlock::iterator InsertPos =
            findPHICopyInsertPoint(&opBlock, &MBB, SrcReg);

        // Insert the copy.
        MachineInstr *NewSrcInstr = 0;
        if (!reusedIncoming && IncomingReg) {
            if (SrcUndef) {
                // The source register is undefined, so there is no need for a real
                // COPY, but we still need to ensure joint dominance by defs.
                // Insert an IMPLICIT_DEF instruction.
                NewSrcInstr = BuildMI(opBlock, InsertPos, MPhi->getDebugLoc(),
                                      TII->get(TargetOpcode::IMPLICIT_DEF),
                                      IncomingReg);

                // Clean up the old implicit-def, if there even was one.
                if (MachineInstr *DefMI = MRI->getVRegDef(SrcReg))
                    if (DefMI->isImplicitDef())
                        ImpDefs.insert(DefMI);
            } else {
                NewSrcInstr = BuildMI(opBlock, InsertPos, MPhi->getDebugLoc(),
                                      TII->get(TargetOpcode::COPY), IncomingReg)
                              .addReg(SrcReg, 0, SrcSubReg);
            }
        }

        // We only need to update the LiveVariables kill of SrcReg if this was the
        // last PHI use of SrcReg to be lowered on this CFG edge and it is not live
        // out of the predecessor. We can also ignore undef sources.
        if (LV && !SrcUndef &&
                !VRegPHIUseCount[BBVRegPair(opBlock.getNumber(), SrcReg)] &&
                !LV->isLiveOut(SrcReg, opBlock)) {
            // We want to be able to insert a kill of the register if this PHI (aka,
            // the copy we just inserted) is the last use of the source value. Live
            // variable analysis conservatively handles this by saying that the value
            // is live until the end of the block the PHI entry lives in. If the value
            // really is dead at the PHI copy, there will be no successor blocks which
            // have the value live-in.

            // Okay, if we now know that the value is not live out of the block, we
            // can add a kill marker in this block saying that it kills the incoming
            // value!

            // In our final twist, we have to decide which instruction kills the
            // register.  In most cases this is the copy, however, terminator
            // instructions at the end of the block may also use the value. In this
            // case, we should mark the last such terminator as being the killing
            // block, not the copy.
            MachineBasicBlock::iterator KillInst = opBlock.end();
            MachineBasicBlock::iterator FirstTerm = opBlock.getFirstTerminator();
            for (MachineBasicBlock::iterator Term = FirstTerm;
                    Term != opBlock.end(); ++Term) {
                if (Term->readsRegister(SrcReg))
                    KillInst = Term;
            }

            if (KillInst == opBlock.end()) {
                // No terminator uses the register.

                if (reusedIncoming || !IncomingReg) {
                    // We may have to rewind a bit if we didn't insert a copy this time.
                    KillInst = FirstTerm;
                    while (KillInst != opBlock.begin()) {
                        --KillInst;
                        if (KillInst->isDebugValue())
                            continue;
                        if (KillInst->readsRegister(SrcReg))
                            break;
                    }
                } else {
                    // We just inserted this copy.
                    KillInst = prior(InsertPos);
                }
            }
            assert(KillInst->readsRegister(SrcReg) && "Cannot find kill instruction");

            // Finally, mark it killed.
            LV->addVirtualRegisterKilled(SrcReg, KillInst);

            // This vreg no longer lives all of the way through opBlock.
            unsigned opBlockNum = opBlock.getNumber();
            LV->getVarInfo(SrcReg).AliveBlocks.reset(opBlockNum);
        }

        if (LIS) {
            if (NewSrcInstr) {
                LIS->InsertMachineInstrInMaps(NewSrcInstr);
                LIS->addLiveRangeToEndOfBlock(IncomingReg, NewSrcInstr);
            }

            if (!SrcUndef &&
                    !VRegPHIUseCount[BBVRegPair(opBlock.getNumber(), SrcReg)]) {
                LiveInterval &SrcLI = LIS->getInterval(SrcReg);

                bool isLiveOut = false;
                for (MachineBasicBlock::succ_iterator SI = opBlock.succ_begin(),
                        SE = opBlock.succ_end(); SI != SE; ++SI) {
                    SlotIndex startIdx = LIS->getMBBStartIdx(*SI);
                    VNInfo *VNI = SrcLI.getVNInfoAt(startIdx);

                    // Definitions by other PHIs are not truly live-in for our purposes.
                    if (VNI && VNI->def != startIdx) {
                        isLiveOut = true;
                        break;
                    }
                }

                if (!isLiveOut) {
                    MachineBasicBlock::iterator KillInst = opBlock.end();
                    MachineBasicBlock::iterator FirstTerm = opBlock.getFirstTerminator();
                    for (MachineBasicBlock::iterator Term = FirstTerm;
                            Term != opBlock.end(); ++Term) {
                        if (Term->readsRegister(SrcReg))
                            KillInst = Term;
                    }

                    if (KillInst == opBlock.end()) {
                        // No terminator uses the register.

                        if (reusedIncoming || !IncomingReg) {
                            // We may have to rewind a bit if we didn't just insert a copy.
                            KillInst = FirstTerm;
                            while (KillInst != opBlock.begin()) {
                                --KillInst;
                                if (KillInst->isDebugValue())
                                    continue;
                                if (KillInst->readsRegister(SrcReg))
                                    break;
                            }
                        } else {
                            // We just inserted this copy.
                            KillInst = prior(InsertPos);
                        }
                    }
                    assert(KillInst->readsRegister(SrcReg) &&
                           "Cannot find kill instruction");

                    SlotIndex LastUseIndex = LIS->getInstructionIndex(KillInst);
                    SrcLI.removeRange(LastUseIndex.getRegSlot(),
                                      LIS->getMBBEndIdx(&opBlock));
                }
            }
        }
    }

    // Really delete the PHI instruction now, if it is not in the LoweredPHIs map.
    if (reusedIncoming || !IncomingReg) {
        if (LIS)
            LIS->RemoveMachineInstrFromMaps(MPhi);
        MF.DeleteMachineInstr(MPhi);
    }
}