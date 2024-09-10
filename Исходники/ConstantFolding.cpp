APInt swift::constantFoldCast(APInt val, const BuiltinInfo &BI) {
  // Get the cast result.
  Type SrcTy = BI.Types[0];
  Type DestTy = BI.Types.size() == 2 ? BI.Types[1] : Type();
  uint32_t SrcBitWidth =
  SrcTy->castTo<BuiltinIntegerType>()->getGreatestWidth();
  uint32_t DestBitWidth =
  DestTy->castTo<BuiltinIntegerType>()->getGreatestWidth();
  
  APInt CastResV;
  if (SrcBitWidth == DestBitWidth) {
    return val;
  } else switch (BI.ID) {
    default : llvm_unreachable("Invalid case.");
    case BuiltinValueKind::Trunc:
    case BuiltinValueKind::TruncOrBitCast:
      return val.trunc(DestBitWidth);
    case BuiltinValueKind::ZExt:
    case BuiltinValueKind::ZExtOrBitCast:
      return val.zext(DestBitWidth);
      break;
    case BuiltinValueKind::SExt:
    case BuiltinValueKind::SExtOrBitCast:
      return val.sext(DestBitWidth);
  }
}