void BDCE::determineLiveOperandBits(const Instruction *UserI,
                                    const Instruction *I, unsigned OperandNo,
                                    const APInt &AOut, APInt &AB,
                                    APInt &KnownZero, APInt &KnownOne,
                                    APInt &KnownZero2, APInt &KnownOne2) {
  unsigned BitWidth = AB.getBitWidth();

  // We're called once per operand, but for some instructions, we need to
  // compute known bits of both operands in order to determine the live bits of
  // either (when both operands are instructions themselves). We don't,
  // however, want to do this twice, so we cache the result in APInts that live
  // in the caller. For the two-relevant-operands case, both operand values are
  // provided here.
  auto ComputeKnownBits =
      [&](unsigned BitWidth, const Value *V1, const Value *V2) {
        const DataLayout &DL = I->getModule()->getDataLayout();
        KnownZero = APInt(BitWidth, 0);
        KnownOne = APInt(BitWidth, 0);
        computeKnownBits(const_cast<Value *>(V1), KnownZero, KnownOne, DL, 0,
                         AC, UserI, DT);

        if (V2) {
          KnownZero2 = APInt(BitWidth, 0);
          KnownOne2 = APInt(BitWidth, 0);
          computeKnownBits(const_cast<Value *>(V2), KnownZero2, KnownOne2, DL,
                           0, AC, UserI, DT);
        }
      };

  switch (UserI->getOpcode()) {
  default: break;
  case Instruction::Call:
  case Instruction::Invoke:
    if (const IntrinsicInst *II = dyn_cast<IntrinsicInst>(UserI))
      switch (II->getIntrinsicID()) {
      default: break;
      case Intrinsic::bswap:
        // The alive bits of the input are the swapped alive bits of
        // the output.
        AB = AOut.byteSwap();
        break;
      case Intrinsic::ctlz:
        if (OperandNo == 0) {
          // We need some output bits, so we need all bits of the
          // input to the left of, and including, the leftmost bit
          // known to be one.
          ComputeKnownBits(BitWidth, I, nullptr);
          AB = APInt::getHighBitsSet(BitWidth,
                 std::min(BitWidth, KnownOne.countLeadingZeros()+1));
        }
        break;
      case Intrinsic::cttz:
        if (OperandNo == 0) {
          // We need some output bits, so we need all bits of the
          // input to the right of, and including, the rightmost bit
          // known to be one.
          ComputeKnownBits(BitWidth, I, nullptr);
          AB = APInt::getLowBitsSet(BitWidth,
                 std::min(BitWidth, KnownOne.countTrailingZeros()+1));
        }
        break;
      }
    break;
  case Instruction::Add:
  case Instruction::Sub:
    // Find the highest live output bit. We don't need any more input
    // bits than that (adds, and thus subtracts, ripple only to the
    // left).
    AB = APInt::getLowBitsSet(BitWidth, AOut.getActiveBits());
    break;
  case Instruction::Shl:
    if (OperandNo == 0)
      if (ConstantInt *CI =
            dyn_cast<ConstantInt>(UserI->getOperand(1))) {
        uint64_t ShiftAmt = CI->getLimitedValue(BitWidth-1);
        AB = AOut.lshr(ShiftAmt);

        // If the shift is nuw/nsw, then the high bits are not dead
        // (because we've promised that they *must* be zero).
        const ShlOperator *S = cast<ShlOperator>(UserI);
        if (S->hasNoSignedWrap())
          AB |= APInt::getHighBitsSet(BitWidth, ShiftAmt+1);
        else if (S->hasNoUnsignedWrap())
          AB |= APInt::getHighBitsSet(BitWidth, ShiftAmt);
      }
    break;
  case Instruction::LShr:
    if (OperandNo == 0)
      if (ConstantInt *CI =
            dyn_cast<ConstantInt>(UserI->getOperand(1))) {
        uint64_t ShiftAmt = CI->getLimitedValue(BitWidth-1);
        AB = AOut.shl(ShiftAmt);

        // If the shift is exact, then the low bits are not dead
        // (they must be zero).
        if (cast<LShrOperator>(UserI)->isExact())
          AB |= APInt::getLowBitsSet(BitWidth, ShiftAmt);
      }
    break;
  case Instruction::AShr:
    if (OperandNo == 0)
      if (ConstantInt *CI =
            dyn_cast<ConstantInt>(UserI->getOperand(1))) {
        uint64_t ShiftAmt = CI->getLimitedValue(BitWidth-1);
        AB = AOut.shl(ShiftAmt);
        // Because the high input bit is replicated into the
        // high-order bits of the result, if we need any of those
        // bits, then we must keep the highest input bit.
        if ((AOut & APInt::getHighBitsSet(BitWidth, ShiftAmt))
            .getBoolValue())
          AB.setBit(BitWidth-1);

        // If the shift is exact, then the low bits are not dead
        // (they must be zero).
        if (cast<AShrOperator>(UserI)->isExact())
          AB |= APInt::getLowBitsSet(BitWidth, ShiftAmt);
      }
    break;
  case Instruction::And:
    AB = AOut;

    // For bits that are known zero, the corresponding bits in the
    // other operand are dead (unless they're both zero, in which
    // case they can't both be dead, so just mark the LHS bits as
    // dead).
    if (OperandNo == 0) {
      ComputeKnownBits(BitWidth, I, UserI->getOperand(1));
      AB &= ~KnownZero2;
    } else {
      if (!isa<Instruction>(UserI->getOperand(0)))
        ComputeKnownBits(BitWidth, UserI->getOperand(0), I);
      AB &= ~(KnownZero & ~KnownZero2);
    }
    break;
  case Instruction::Or:
    AB = AOut;

    // For bits that are known one, the corresponding bits in the
    // other operand are dead (unless they're both one, in which
    // case they can't both be dead, so just mark the LHS bits as
    // dead).
    if (OperandNo == 0) {
      ComputeKnownBits(BitWidth, I, UserI->getOperand(1));
      AB &= ~KnownOne2;
    } else {
      if (!isa<Instruction>(UserI->getOperand(0)))
        ComputeKnownBits(BitWidth, UserI->getOperand(0), I);
      AB &= ~(KnownOne & ~KnownOne2);
    }
    break;
  case Instruction::Xor:
  case Instruction::PHI:
    AB = AOut;
    break;
  case Instruction::Trunc:
    AB = AOut.zext(BitWidth);
    break;
  case Instruction::ZExt:
    AB = AOut.trunc(BitWidth);
    break;
  case Instruction::SExt:
    AB = AOut.trunc(BitWidth);
    // Because the high input bit is replicated into the
    // high-order bits of the result, if we need any of those
    // bits, then we must keep the highest input bit.
    if ((AOut & APInt::getHighBitsSet(AOut.getBitWidth(),
                                      AOut.getBitWidth() - BitWidth))
        .getBoolValue())
      AB.setBit(BitWidth-1);
    break;
  case Instruction::Select:
    if (OperandNo != 0)
      AB = AOut;
    break;
  }
}