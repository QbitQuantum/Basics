/// ComputeMaskedBits - Determine which of the bits specified in Mask are
/// known to be either zero or one and return them in the KnownZero/KnownOne
/// bit sets.  This code only analyzes bits in Mask, in order to short-circuit
/// processing.
/// NOTE: we cannot consider 'undef' to be "IsZero" here.  The problem is that
/// we cannot optimize based on the assumption that it is zero without changing
/// it to be an explicit zero.  If we don't change it to zero, other code could
/// optimized based on the contradictory assumption that it is non-zero.
/// Because instcombine aggressively folds operations with undef args anyway,
/// this won't lose us code quality.
void llvm::ComputeMaskedBits(Value *V, const APInt &Mask,
                             APInt &KnownZero, APInt &KnownOne,
                             TargetData *TD, unsigned Depth) {
  const unsigned MaxDepth = 6;
  assert(V && "No Value?");
  assert(Depth <= MaxDepth && "Limit Search Depth");
  unsigned BitWidth = Mask.getBitWidth();
  assert((V->getType()->isInteger() || isa<PointerType>(V->getType())) &&
         "Not integer or pointer type!");
  assert((!TD || TD->getTypeSizeInBits(V->getType()) == BitWidth) &&
         (!isa<IntegerType>(V->getType()) ||
          V->getType()->getPrimitiveSizeInBits() == BitWidth) &&
         KnownZero.getBitWidth() == BitWidth && 
         KnownOne.getBitWidth() == BitWidth &&
         "V, Mask, KnownOne and KnownZero should have same BitWidth");

  if (ConstantInt *CI = dyn_cast<ConstantInt>(V)) {
    // We know all of the bits for a constant!
    KnownOne = CI->getValue() & Mask;
    KnownZero = ~KnownOne & Mask;
    return;
  }
  // Null is all-zeros.
  if (isa<ConstantPointerNull>(V)) {
    KnownOne.clear();
    KnownZero = Mask;
    return;
  }
  // The address of an aligned GlobalValue has trailing zeros.
  if (GlobalValue *GV = dyn_cast<GlobalValue>(V)) {
    unsigned Align = GV->getAlignment();
    if (Align == 0 && TD && GV->getType()->getElementType()->isSized()) 
      Align = TD->getPrefTypeAlignment(GV->getType()->getElementType());
    if (Align > 0)
      KnownZero = Mask & APInt::getLowBitsSet(BitWidth,
                                              CountTrailingZeros_32(Align));
    else
      KnownZero.clear();
    KnownOne.clear();
    return;
  }

  KnownZero.clear(); KnownOne.clear();   // Start out not knowing anything.

  if (Depth == MaxDepth || Mask == 0)
    return;  // Limit search depth.

  User *I = dyn_cast<User>(V);
  if (!I) return;

  APInt KnownZero2(KnownZero), KnownOne2(KnownOne);
  switch (getOpcode(I)) {
  default: break;
  case Instruction::And: {
    // If either the LHS or the RHS are Zero, the result is zero.
    ComputeMaskedBits(I->getOperand(1), Mask, KnownZero, KnownOne, TD, Depth+1);
    APInt Mask2(Mask & ~KnownZero);
    ComputeMaskedBits(I->getOperand(0), Mask2, KnownZero2, KnownOne2, TD,
                      Depth+1);
    assert((KnownZero & KnownOne) == 0 && "Bits known to be one AND zero?"); 
    assert((KnownZero2 & KnownOne2) == 0 && "Bits known to be one AND zero?"); 
    
    // Output known-1 bits are only known if set in both the LHS & RHS.
    KnownOne &= KnownOne2;
    // Output known-0 are known to be clear if zero in either the LHS | RHS.
    KnownZero |= KnownZero2;
    return;
  }
  case Instruction::Or: {
    ComputeMaskedBits(I->getOperand(1), Mask, KnownZero, KnownOne, TD, Depth+1);
    APInt Mask2(Mask & ~KnownOne);
    ComputeMaskedBits(I->getOperand(0), Mask2, KnownZero2, KnownOne2, TD,
                      Depth+1);
    assert((KnownZero & KnownOne) == 0 && "Bits known to be one AND zero?"); 
    assert((KnownZero2 & KnownOne2) == 0 && "Bits known to be one AND zero?"); 
    
    // Output known-0 bits are only known if clear in both the LHS & RHS.
    KnownZero &= KnownZero2;
    // Output known-1 are known to be set if set in either the LHS | RHS.
    KnownOne |= KnownOne2;
    return;
  }
  case Instruction::Xor: {
    ComputeMaskedBits(I->getOperand(1), Mask, KnownZero, KnownOne, TD, Depth+1);
    ComputeMaskedBits(I->getOperand(0), Mask, KnownZero2, KnownOne2, TD,
                      Depth+1);
    assert((KnownZero & KnownOne) == 0 && "Bits known to be one AND zero?"); 
    assert((KnownZero2 & KnownOne2) == 0 && "Bits known to be one AND zero?"); 
    
    // Output known-0 bits are known if clear or set in both the LHS & RHS.
    APInt KnownZeroOut = (KnownZero & KnownZero2) | (KnownOne & KnownOne2);
    // Output known-1 are known to be set if set in only one of the LHS, RHS.
    KnownOne = (KnownZero & KnownOne2) | (KnownOne & KnownZero2);
    KnownZero = KnownZeroOut;
    return;
  }
  case Instruction::Mul: {
    APInt Mask2 = APInt::getAllOnesValue(BitWidth);
    ComputeMaskedBits(I->getOperand(1), Mask2, KnownZero, KnownOne, TD,Depth+1);
    ComputeMaskedBits(I->getOperand(0), Mask2, KnownZero2, KnownOne2, TD,
                      Depth+1);
    assert((KnownZero & KnownOne) == 0 && "Bits known to be one AND zero?"); 
    assert((KnownZero2 & KnownOne2) == 0 && "Bits known to be one AND zero?"); 
    
    // If low bits are zero in either operand, output low known-0 bits.
    // Also compute a conserative estimate for high known-0 bits.
    // More trickiness is possible, but this is sufficient for the
    // interesting case of alignment computation.
    KnownOne.clear();
    unsigned TrailZ = KnownZero.countTrailingOnes() +
                      KnownZero2.countTrailingOnes();
    unsigned LeadZ =  std::max(KnownZero.countLeadingOnes() +
                               KnownZero2.countLeadingOnes(),
                               BitWidth) - BitWidth;

    TrailZ = std::min(TrailZ, BitWidth);
    LeadZ = std::min(LeadZ, BitWidth);
    KnownZero = APInt::getLowBitsSet(BitWidth, TrailZ) |
                APInt::getHighBitsSet(BitWidth, LeadZ);
    KnownZero &= Mask;
    return;
  }
  case Instruction::UDiv: {
    // For the purposes of computing leading zeros we can conservatively
    // treat a udiv as a logical right shift by the power of 2 known to
    // be less than the denominator.
    APInt AllOnes = APInt::getAllOnesValue(BitWidth);
    ComputeMaskedBits(I->getOperand(0),
                      AllOnes, KnownZero2, KnownOne2, TD, Depth+1);
    unsigned LeadZ = KnownZero2.countLeadingOnes();

    KnownOne2.clear();
    KnownZero2.clear();
    ComputeMaskedBits(I->getOperand(1),
                      AllOnes, KnownZero2, KnownOne2, TD, Depth+1);
    unsigned RHSUnknownLeadingOnes = KnownOne2.countLeadingZeros();
    if (RHSUnknownLeadingOnes != BitWidth)
      LeadZ = std::min(BitWidth,
                       LeadZ + BitWidth - RHSUnknownLeadingOnes - 1);

    KnownZero = APInt::getHighBitsSet(BitWidth, LeadZ) & Mask;
    return;
  }
  case Instruction::Select:
    ComputeMaskedBits(I->getOperand(2), Mask, KnownZero, KnownOne, TD, Depth+1);
    ComputeMaskedBits(I->getOperand(1), Mask, KnownZero2, KnownOne2, TD,
                      Depth+1);
    assert((KnownZero & KnownOne) == 0 && "Bits known to be one AND zero?"); 
    assert((KnownZero2 & KnownOne2) == 0 && "Bits known to be one AND zero?"); 

    // Only known if known in both the LHS and RHS.
    KnownOne &= KnownOne2;
    KnownZero &= KnownZero2;
    return;
  case Instruction::FPTrunc:
  case Instruction::FPExt:
  case Instruction::FPToUI:
  case Instruction::FPToSI:
  case Instruction::SIToFP:
  case Instruction::UIToFP:
    return; // Can't work with floating point.
  case Instruction::PtrToInt:
  case Instruction::IntToPtr:
    // We can't handle these if we don't know the pointer size.
    if (!TD) return;
    // FALL THROUGH and handle them the same as zext/trunc.
  case Instruction::ZExt:
  case Instruction::Trunc: {
    // Note that we handle pointer operands here because of inttoptr/ptrtoint
    // which fall through here.
    const Type *SrcTy = I->getOperand(0)->getType();
    unsigned SrcBitWidth = TD ?
      TD->getTypeSizeInBits(SrcTy) :
      SrcTy->getPrimitiveSizeInBits();
    APInt MaskIn(Mask);
    MaskIn.zextOrTrunc(SrcBitWidth);
    KnownZero.zextOrTrunc(SrcBitWidth);
    KnownOne.zextOrTrunc(SrcBitWidth);
    ComputeMaskedBits(I->getOperand(0), MaskIn, KnownZero, KnownOne, TD,
                      Depth+1);
    KnownZero.zextOrTrunc(BitWidth);
    KnownOne.zextOrTrunc(BitWidth);
    // Any top bits are known to be zero.
    if (BitWidth > SrcBitWidth)
      KnownZero |= APInt::getHighBitsSet(BitWidth, BitWidth - SrcBitWidth);
    return;
  }
  case Instruction::BitCast: {
    const Type *SrcTy = I->getOperand(0)->getType();
    if (SrcTy->isInteger() || isa<PointerType>(SrcTy)) {
      ComputeMaskedBits(I->getOperand(0), Mask, KnownZero, KnownOne, TD,
                        Depth+1);
      return;
    }
    break;
  }
  case Instruction::SExt: {
    // Compute the bits in the result that are not present in the input.
    const IntegerType *SrcTy = cast<IntegerType>(I->getOperand(0)->getType());
    unsigned SrcBitWidth = SrcTy->getBitWidth();
      
    APInt MaskIn(Mask); 
    MaskIn.trunc(SrcBitWidth);
    KnownZero.trunc(SrcBitWidth);
    KnownOne.trunc(SrcBitWidth);
    ComputeMaskedBits(I->getOperand(0), MaskIn, KnownZero, KnownOne, TD,
                      Depth+1);
    assert((KnownZero & KnownOne) == 0 && "Bits known to be one AND zero?"); 
    KnownZero.zext(BitWidth);
    KnownOne.zext(BitWidth);

    // If the sign bit of the input is known set or clear, then we know the
    // top bits of the result.
    if (KnownZero[SrcBitWidth-1])             // Input sign bit known zero
      KnownZero |= APInt::getHighBitsSet(BitWidth, BitWidth - SrcBitWidth);
    else if (KnownOne[SrcBitWidth-1])           // Input sign bit known set
      KnownOne |= APInt::getHighBitsSet(BitWidth, BitWidth - SrcBitWidth);
    return;
  }
  case Instruction::Shl:
    // (shl X, C1) & C2 == 0   iff   (X & C2 >>u C1) == 0
    if (ConstantInt *SA = dyn_cast<ConstantInt>(I->getOperand(1))) {
      uint64_t ShiftAmt = SA->getLimitedValue(BitWidth);
      APInt Mask2(Mask.lshr(ShiftAmt));
      ComputeMaskedBits(I->getOperand(0), Mask2, KnownZero, KnownOne, TD,
                        Depth+1);
      assert((KnownZero & KnownOne) == 0 && "Bits known to be one AND zero?"); 
      KnownZero <<= ShiftAmt;
      KnownOne  <<= ShiftAmt;
      KnownZero |= APInt::getLowBitsSet(BitWidth, ShiftAmt); // low bits known 0
      return;
    }
    break;
  case Instruction::LShr:
    // (ushr X, C1) & C2 == 0   iff  (-1 >> C1) & C2 == 0
    if (ConstantInt *SA = dyn_cast<ConstantInt>(I->getOperand(1))) {
      // Compute the new bits that are at the top now.
      uint64_t ShiftAmt = SA->getLimitedValue(BitWidth);
      
      // Unsigned shift right.
      APInt Mask2(Mask.shl(ShiftAmt));
      ComputeMaskedBits(I->getOperand(0), Mask2, KnownZero,KnownOne, TD,
                        Depth+1);
      assert((KnownZero & KnownOne) == 0&&"Bits known to be one AND zero?"); 
      KnownZero = APIntOps::lshr(KnownZero, ShiftAmt);
      KnownOne  = APIntOps::lshr(KnownOne, ShiftAmt);
      // high bits known zero.
      KnownZero |= APInt::getHighBitsSet(BitWidth, ShiftAmt);
      return;
    }
    break;
  case Instruction::AShr:
    // (ashr X, C1) & C2 == 0   iff  (-1 >> C1) & C2 == 0
    if (ConstantInt *SA = dyn_cast<ConstantInt>(I->getOperand(1))) {
      // Compute the new bits that are at the top now.
      uint64_t ShiftAmt = SA->getLimitedValue(BitWidth);
      
      // Signed shift right.
      APInt Mask2(Mask.shl(ShiftAmt));
      ComputeMaskedBits(I->getOperand(0), Mask2, KnownZero, KnownOne, TD,
                        Depth+1);
      assert((KnownZero & KnownOne) == 0&&"Bits known to be one AND zero?"); 
      KnownZero = APIntOps::lshr(KnownZero, ShiftAmt);
      KnownOne  = APIntOps::lshr(KnownOne, ShiftAmt);
        
      APInt HighBits(APInt::getHighBitsSet(BitWidth, ShiftAmt));
      if (KnownZero[BitWidth-ShiftAmt-1])    // New bits are known zero.
        KnownZero |= HighBits;
      else if (KnownOne[BitWidth-ShiftAmt-1])  // New bits are known one.
        KnownOne |= HighBits;
      return;
    }
    break;
  case Instruction::Sub: {
    if (ConstantInt *CLHS = dyn_cast<ConstantInt>(I->getOperand(0))) {
      // We know that the top bits of C-X are clear if X contains less bits
      // than C (i.e. no wrap-around can happen).  For example, 20-X is
      // positive if we can prove that X is >= 0 and < 16.
      if (!CLHS->getValue().isNegative()) {
        unsigned NLZ = (CLHS->getValue()+1).countLeadingZeros();
        // NLZ can't be BitWidth with no sign bit
        APInt MaskV = APInt::getHighBitsSet(BitWidth, NLZ+1);
        ComputeMaskedBits(I->getOperand(1), MaskV, KnownZero2, KnownOne2,
                          TD, Depth+1);
    
        // If all of the MaskV bits are known to be zero, then we know the
        // output top bits are zero, because we now know that the output is
        // from [0-C].
        if ((KnownZero2 & MaskV) == MaskV) {
          unsigned NLZ2 = CLHS->getValue().countLeadingZeros();
          // Top bits known zero.
          KnownZero = APInt::getHighBitsSet(BitWidth, NLZ2) & Mask;
        }
      }        
    }
  }
  // fall through
  case Instruction::Add: {
    // If one of the operands has trailing zeros, than the bits that the
    // other operand has in those bit positions will be preserved in the
    // result. For an add, this works with either operand. For a subtract,
    // this only works if the known zeros are in the right operand.
    APInt LHSKnownZero(BitWidth, 0), LHSKnownOne(BitWidth, 0);
    APInt Mask2 = APInt::getLowBitsSet(BitWidth,
                                       BitWidth - Mask.countLeadingZeros());
    ComputeMaskedBits(I->getOperand(0), Mask2, LHSKnownZero, LHSKnownOne, TD,
                      Depth+1);
    assert((LHSKnownZero & LHSKnownOne) == 0 &&
           "Bits known to be one AND zero?");
    unsigned LHSKnownZeroOut = LHSKnownZero.countTrailingOnes();

    ComputeMaskedBits(I->getOperand(1), Mask2, KnownZero2, KnownOne2, TD, 
                      Depth+1);
    assert((KnownZero2 & KnownOne2) == 0 && "Bits known to be one AND zero?"); 
    unsigned RHSKnownZeroOut = KnownZero2.countTrailingOnes();

    // Determine which operand has more trailing zeros, and use that
    // many bits from the other operand.
    if (LHSKnownZeroOut > RHSKnownZeroOut) {
      if (getOpcode(I) == Instruction::Add) {
        APInt Mask = APInt::getLowBitsSet(BitWidth, LHSKnownZeroOut);
        KnownZero |= KnownZero2 & Mask;
        KnownOne  |= KnownOne2 & Mask;
      } else {
        // If the known zeros are in the left operand for a subtract,
        // fall back to the minimum known zeros in both operands.
        KnownZero |= APInt::getLowBitsSet(BitWidth,
                                          std::min(LHSKnownZeroOut,
                                                   RHSKnownZeroOut));
      }
    } else if (RHSKnownZeroOut >= LHSKnownZeroOut) {
      APInt Mask = APInt::getLowBitsSet(BitWidth, RHSKnownZeroOut);
      KnownZero |= LHSKnownZero & Mask;
      KnownOne  |= LHSKnownOne & Mask;
    }
    return;
  }
  case Instruction::SRem:
    if (ConstantInt *Rem = dyn_cast<ConstantInt>(I->getOperand(1))) {
      APInt RA = Rem->getValue();
      if (RA.isPowerOf2() || (-RA).isPowerOf2()) {
        APInt LowBits = RA.isStrictlyPositive() ? (RA - 1) : ~RA;
        APInt Mask2 = LowBits | APInt::getSignBit(BitWidth);
        ComputeMaskedBits(I->getOperand(0), Mask2, KnownZero2, KnownOne2, TD, 
                          Depth+1);

        // If the sign bit of the first operand is zero, the sign bit of
        // the result is zero. If the first operand has no one bits below
        // the second operand's single 1 bit, its sign will be zero.
        if (KnownZero2[BitWidth-1] || ((KnownZero2 & LowBits) == LowBits))
          KnownZero2 |= ~LowBits;

        KnownZero |= KnownZero2 & Mask;

        assert((KnownZero & KnownOne) == 0&&"Bits known to be one AND zero?"); 
      }
    }
    break;
  case Instruction::URem: {
    if (ConstantInt *Rem = dyn_cast<ConstantInt>(I->getOperand(1))) {
      APInt RA = Rem->getValue();
      if (RA.isPowerOf2()) {
        APInt LowBits = (RA - 1);
        APInt Mask2 = LowBits & Mask;
        KnownZero |= ~LowBits & Mask;
        ComputeMaskedBits(I->getOperand(0), Mask2, KnownZero, KnownOne, TD,
                          Depth+1);
        assert((KnownZero & KnownOne) == 0&&"Bits known to be one AND zero?");
        break;
      }
    }

    // Since the result is less than or equal to either operand, any leading
    // zero bits in either operand must also exist in the result.
    APInt AllOnes = APInt::getAllOnesValue(BitWidth);
    ComputeMaskedBits(I->getOperand(0), AllOnes, KnownZero, KnownOne,
                      TD, Depth+1);
    ComputeMaskedBits(I->getOperand(1), AllOnes, KnownZero2, KnownOne2,
                      TD, Depth+1);

    unsigned Leaders = std::max(KnownZero.countLeadingOnes(),
                                KnownZero2.countLeadingOnes());
    KnownOne.clear();
    KnownZero = APInt::getHighBitsSet(BitWidth, Leaders) & Mask;
    break;
  }

  case Instruction::Alloca:
  case Instruction::Malloc: {
    AllocationInst *AI = cast<AllocationInst>(V);
    unsigned Align = AI->getAlignment();
    if (Align == 0 && TD) {
      if (isa<AllocaInst>(AI))
        Align = TD->getABITypeAlignment(AI->getType()->getElementType());
      else if (isa<MallocInst>(AI)) {
        // Malloc returns maximally aligned memory.
        Align = TD->getABITypeAlignment(AI->getType()->getElementType());
        Align =
          std::max(Align,
                   (unsigned)TD->getABITypeAlignment(Type::DoubleTy));
        Align =
          std::max(Align,
                   (unsigned)TD->getABITypeAlignment(Type::Int64Ty));
      }
    }
    
    if (Align > 0)
      KnownZero = Mask & APInt::getLowBitsSet(BitWidth,
                                              CountTrailingZeros_32(Align));
    break;
  }
  case Instruction::GetElementPtr: {
    // Analyze all of the subscripts of this getelementptr instruction
    // to determine if we can prove known low zero bits.
    APInt LocalMask = APInt::getAllOnesValue(BitWidth);
    APInt LocalKnownZero(BitWidth, 0), LocalKnownOne(BitWidth, 0);
    ComputeMaskedBits(I->getOperand(0), LocalMask,
                      LocalKnownZero, LocalKnownOne, TD, Depth+1);
    unsigned TrailZ = LocalKnownZero.countTrailingOnes();

    gep_type_iterator GTI = gep_type_begin(I);
    for (unsigned i = 1, e = I->getNumOperands(); i != e; ++i, ++GTI) {
      Value *Index = I->getOperand(i);
      if (const StructType *STy = dyn_cast<StructType>(*GTI)) {
        // Handle struct member offset arithmetic.
        if (!TD) return;
        const StructLayout *SL = TD->getStructLayout(STy);
        unsigned Idx = cast<ConstantInt>(Index)->getZExtValue();
        uint64_t Offset = SL->getElementOffset(Idx);
        TrailZ = std::min(TrailZ,
                          CountTrailingZeros_64(Offset));
      } else {
        // Handle array index arithmetic.
        const Type *IndexedTy = GTI.getIndexedType();
        if (!IndexedTy->isSized()) return;
        unsigned GEPOpiBits = Index->getType()->getPrimitiveSizeInBits();
        uint64_t TypeSize = TD ? TD->getTypeAllocSize(IndexedTy) : 1;
        LocalMask = APInt::getAllOnesValue(GEPOpiBits);
        LocalKnownZero = LocalKnownOne = APInt(GEPOpiBits, 0);
        ComputeMaskedBits(Index, LocalMask,
                          LocalKnownZero, LocalKnownOne, TD, Depth+1);
        TrailZ = std::min(TrailZ,
                          unsigned(CountTrailingZeros_64(TypeSize) +
                                   LocalKnownZero.countTrailingOnes()));
      }
    }
    
    KnownZero = APInt::getLowBitsSet(BitWidth, TrailZ) & Mask;
    break;
  }
  case Instruction::PHI: {
    PHINode *P = cast<PHINode>(I);
    // Handle the case of a simple two-predecessor recurrence PHI.
    // There's a lot more that could theoretically be done here, but
    // this is sufficient to catch some interesting cases.
    if (P->getNumIncomingValues() == 2) {
      for (unsigned i = 0; i != 2; ++i) {
        Value *L = P->getIncomingValue(i);
        Value *R = P->getIncomingValue(!i);
        User *LU = dyn_cast<User>(L);
        if (!LU)
          continue;
        unsigned Opcode = getOpcode(LU);
        // Check for operations that have the property that if
        // both their operands have low zero bits, the result
        // will have low zero bits.
        if (Opcode == Instruction::Add ||
            Opcode == Instruction::Sub ||
            Opcode == Instruction::And ||
            Opcode == Instruction::Or ||
            Opcode == Instruction::Mul) {
          Value *LL = LU->getOperand(0);
          Value *LR = LU->getOperand(1);
          // Find a recurrence.
          if (LL == I)
            L = LR;
          else if (LR == I)
            L = LL;
          else
            break;
          // Ok, we have a PHI of the form L op= R. Check for low
          // zero bits.
          APInt Mask2 = APInt::getAllOnesValue(BitWidth);
          ComputeMaskedBits(R, Mask2, KnownZero2, KnownOne2, TD, Depth+1);
          Mask2 = APInt::getLowBitsSet(BitWidth,
                                       KnownZero2.countTrailingOnes());

          // We need to take the minimum number of known bits
          APInt KnownZero3(KnownZero), KnownOne3(KnownOne);
          ComputeMaskedBits(L, Mask2, KnownZero3, KnownOne3, TD, Depth+1);

          KnownZero = Mask &
                      APInt::getLowBitsSet(BitWidth,
                                           std::min(KnownZero2.countTrailingOnes(),
                                                    KnownZero3.countTrailingOnes()));
          break;
        }
      }
    }

    // Otherwise take the unions of the known bit sets of the operands,
    // taking conservative care to avoid excessive recursion.
    if (Depth < MaxDepth - 1 && !KnownZero && !KnownOne) {
      KnownZero = APInt::getAllOnesValue(BitWidth);
      KnownOne = APInt::getAllOnesValue(BitWidth);
      for (unsigned i = 0, e = P->getNumIncomingValues(); i != e; ++i) {
        // Skip direct self references.
        if (P->getIncomingValue(i) == P) continue;

        KnownZero2 = APInt(BitWidth, 0);
        KnownOne2 = APInt(BitWidth, 0);
        // Recurse, but cap the recursion to one level, because we don't
        // want to waste time spinning around in loops.
        ComputeMaskedBits(P->getIncomingValue(i), KnownZero | KnownOne,
                          KnownZero2, KnownOne2, TD, MaxDepth-1);
        KnownZero &= KnownZero2;
        KnownOne &= KnownOne2;
        // If all bits have been ruled out, there's no need to check
        // more operands.
        if (!KnownZero && !KnownOne)
          break;
      }
    }
    break;
  }
  case Instruction::Call:
    if (IntrinsicInst *II = dyn_cast<IntrinsicInst>(I)) {
      switch (II->getIntrinsicID()) {
      default: break;
      case Intrinsic::ctpop:
      case Intrinsic::ctlz:
      case Intrinsic::cttz: {
        unsigned LowBits = Log2_32(BitWidth)+1;
        KnownZero = APInt::getHighBitsSet(BitWidth, BitWidth - LowBits);
        break;
      }
      }
    }
    break;
  }
}