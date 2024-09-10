static SILInstruction *
constantFoldAndCheckIntegerConversions(BuiltinInst *BI,
                                       const BuiltinInfo &Builtin,
                                       Optional<bool> &ResultsInError) {
  assert(Builtin.ID == BuiltinValueKind::SToSCheckedTrunc ||
         Builtin.ID == BuiltinValueKind::UToUCheckedTrunc ||
         Builtin.ID == BuiltinValueKind::SToUCheckedTrunc ||
         Builtin.ID == BuiltinValueKind::UToSCheckedTrunc ||
         Builtin.ID == BuiltinValueKind::SUCheckedConversion ||
         Builtin.ID == BuiltinValueKind::USCheckedConversion);

  // Check if we are converting a constant integer.
  OperandValueArrayRef Args = BI->getArguments();
  auto *V = dyn_cast<IntegerLiteralInst>(Args[0]);
  if (!V)
    return nullptr;
  APInt SrcVal = V->getValue();

  // Get source type and bit width.
  Type SrcTy = Builtin.Types[0];
  uint32_t SrcBitWidth =
    Builtin.Types[0]->castTo<BuiltinIntegerType>()->getGreatestWidth();

  // Compute the destination (for SrcBitWidth < DestBitWidth) and enough info
  // to check for overflow.
  APInt Result;
  bool OverflowError;
  Type DstTy;

  // Process conversions signed <-> unsigned for same size integers.
  if (Builtin.ID == BuiltinValueKind::SUCheckedConversion ||
      Builtin.ID == BuiltinValueKind::USCheckedConversion) {
    DstTy = SrcTy;
    Result = SrcVal;
    // Report an error if the sign bit is set.
    OverflowError = SrcVal.isNegative();

  // Process truncation from unsigned to signed.
  } else if (Builtin.ID != BuiltinValueKind::UToSCheckedTrunc) {
    assert(Builtin.Types.size() == 2);
    DstTy = Builtin.Types[1];
    uint32_t DstBitWidth =
      DstTy->castTo<BuiltinIntegerType>()->getGreatestWidth();
    //     Result = trunc_IntFrom_IntTo(Val)
    //   For signed destination:
    //     sext_IntFrom(Result) == Val ? Result : overflow_error
    //   For signed destination:
    //     zext_IntFrom(Result) == Val ? Result : overflow_error
    Result = SrcVal.trunc(DstBitWidth);
    // Get the signedness of the destination.
    bool Signed = (Builtin.ID == BuiltinValueKind::SToSCheckedTrunc);
    APInt Ext = Signed ? Result.sext(SrcBitWidth) : Result.zext(SrcBitWidth);
    OverflowError = (SrcVal != Ext);

  // Process the rest of truncations.
  } else {
    assert(Builtin.Types.size() == 2);
    DstTy = Builtin.Types[1];
    uint32_t DstBitWidth =
      Builtin.Types[1]->castTo<BuiltinIntegerType>()->getGreatestWidth();
    // Compute the destination (for SrcBitWidth < DestBitWidth):
    //   Result = trunc_IntTo(Val)
    //   Trunc  = trunc_'IntTo-1bit'(Val)
    //   zext_IntFrom(Trunc) == Val ? Result : overflow_error
    Result = SrcVal.trunc(DstBitWidth);
    APInt TruncVal = SrcVal.trunc(DstBitWidth - 1);
    OverflowError = (SrcVal != TruncVal.zext(SrcBitWidth));
  }

  // Check for overflow.
  if (OverflowError) {
    // If we are not asked to emit overflow diagnostics, just return nullptr on
    // overflow.
    if (!ResultsInError.hasValue())
      return nullptr;

    SILLocation Loc = BI->getLoc();
    SILModule &M = BI->getModule();
    const ApplyExpr *CE = Loc.getAsASTNode<ApplyExpr>();
    Type UserSrcTy;
    Type UserDstTy;
    // Primitive heuristics to get the user-written type.
    // Eventually we might be able to use SILLocation (when it contains info
    // about inlined call chains).
    if (CE) {
      if (const TupleType *RTy = CE->getArg()->getType()->getAs<TupleType>()) {
        if (RTy->getNumElements() == 1) {
          UserSrcTy = RTy->getElementType(0);
          UserDstTy = CE->getType();
        }
      } else {
        UserSrcTy = CE->getArg()->getType();
        UserDstTy = CE->getType();
      }
    }
    
 
    // Assume that we are converting from a literal if the Source size is
    // 2048. Is there a better way to identify conversions from literals?
    bool Literal = (SrcBitWidth == 2048);

    // FIXME: This will prevent hard error in cases the error is coming
    // from ObjC interoperability code. Currently, we treat NSUInteger as
    // Int.
    if (Loc.getSourceLoc().isInvalid()) {
      // Otherwise emit the appropriate diagnostic and set ResultsInError.
      if (Literal)
        diagnose(M.getASTContext(), Loc.getSourceLoc(),
                 diag::integer_literal_overflow_warn,
                 UserDstTy.isNull() ? DstTy : UserDstTy);
      else
        diagnose(M.getASTContext(), Loc.getSourceLoc(),
                 diag::integer_conversion_overflow_warn,
                 UserSrcTy.isNull() ? SrcTy : UserSrcTy,
                 UserDstTy.isNull() ? DstTy : UserDstTy);

      ResultsInError = Optional<bool>(true);
      return nullptr;
    }

    // Otherwise report the overflow error.
    if (Literal) {
      bool SrcTySigned, DstTySigned;
      std::tie(SrcTySigned, DstTySigned) = getTypeSignedness(Builtin);
      SmallString<10> SrcAsString;
      SrcVal.toString(SrcAsString, /*radix*/10, SrcTySigned);

      // Try to print user-visible types if they are available.
      if (!UserDstTy.isNull()) {
        auto diagID = diag::integer_literal_overflow;
        
        // If this is a negative literal in an unsigned type, use a specific
        // diagnostic.
        if (SrcTySigned && !DstTySigned && SrcVal.isNegative())
          diagID = diag::negative_integer_literal_overflow_unsigned;
        
        diagnose(M.getASTContext(), Loc.getSourceLoc(),
                 diagID, UserDstTy, SrcAsString);
      // Otherwise, print the Builtin Types.
      } else {
        bool SrcTySigned, DstTySigned;
        std::tie(SrcTySigned, DstTySigned) = getTypeSignedness(Builtin);
        diagnose(M.getASTContext(), Loc.getSourceLoc(),
                 diag::integer_literal_overflow_builtin_types,
                 DstTySigned, DstTy, SrcAsString);
      }
    } else {
      if (Builtin.ID == BuiltinValueKind::SUCheckedConversion) {
        diagnose(M.getASTContext(), Loc.getSourceLoc(),
                 diag::integer_conversion_sign_error,
                 UserDstTy.isNull() ? DstTy : UserDstTy);
      } else {
        // Try to print user-visible types if they are available.
        if (!UserSrcTy.isNull()) {
          diagnose(M.getASTContext(), Loc.getSourceLoc(),
                   diag::integer_conversion_overflow,
                   UserSrcTy, UserDstTy);

        // Otherwise, print the Builtin Types.
        } else {
          // Since builtin types are sign-agnostic, print the signedness
          // separately.
          bool SrcTySigned, DstTySigned;
          std::tie(SrcTySigned, DstTySigned) = getTypeSignedness(Builtin);
          diagnose(M.getASTContext(), Loc.getSourceLoc(),
                   diag::integer_conversion_overflow_builtin_types,
                   SrcTySigned, SrcTy, DstTySigned, DstTy);
        }
      }
    }

    ResultsInError = Optional<bool>(true);
    return nullptr;
  }

  // The call to the builtin should be replaced with the constant value.
  return constructResultWithOverflowTuple(BI, Result, false);

}