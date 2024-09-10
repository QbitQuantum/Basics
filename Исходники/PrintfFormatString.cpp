ArgType PrintfSpecifier::getArgType(ASTContext &Ctx,
                                    bool IsObjCLiteral) const {
  const PrintfConversionSpecifier &CS = getConversionSpecifier();

  if (!CS.consumesDataArgument())
    return ArgType::Invalid();

  if (CS.getKind() == ConversionSpecifier::cArg)
    switch (LM.getKind()) {
      case LengthModifier::None:
        return Ctx.IntTy;
      case LengthModifier::AsLong:
      case LengthModifier::AsWide:
        return ArgType(ArgType::WIntTy, "wint_t");
      case LengthModifier::AsShort:
        if (Ctx.getTargetInfo().getTriple().isOSMSVCRT())
          return Ctx.IntTy;
        LLVM_FALLTHROUGH;
      default:
        return ArgType::Invalid();
    }

  if (CS.isIntArg())
    switch (LM.getKind()) {
      case LengthModifier::AsLongDouble:
        // GNU extension.
        return Ctx.LongLongTy;
      case LengthModifier::None:
        return Ctx.IntTy;
      case LengthModifier::AsInt32:
        return ArgType(Ctx.IntTy, "__int32");
      case LengthModifier::AsChar: return ArgType::AnyCharTy;
      case LengthModifier::AsShort: return Ctx.ShortTy;
      case LengthModifier::AsLong: return Ctx.LongTy;
      case LengthModifier::AsLongLong:
      case LengthModifier::AsQuad:
        return Ctx.LongLongTy;
      case LengthModifier::AsInt64:
        return ArgType(Ctx.LongLongTy, "__int64");
      case LengthModifier::AsIntMax:
        return ArgType(Ctx.getIntMaxType(), "intmax_t");
      case LengthModifier::AsSizeT:
        // FIXME: How to get the corresponding signed version of size_t?
        return ArgType();
      case LengthModifier::AsInt3264:
        return Ctx.getTargetInfo().getTriple().isArch64Bit()
                   ? ArgType(Ctx.LongLongTy, "__int64")
                   : ArgType(Ctx.IntTy, "__int32");
      case LengthModifier::AsPtrDiff:
        return ArgType(Ctx.getPointerDiffType(), "ptrdiff_t");
      case LengthModifier::AsAllocate:
      case LengthModifier::AsMAllocate:
      case LengthModifier::AsWide:
        return ArgType::Invalid();
    }

  if (CS.isUIntArg())
    switch (LM.getKind()) {
      case LengthModifier::AsLongDouble:
        // GNU extension.
        return Ctx.UnsignedLongLongTy;
      case LengthModifier::None:
        return Ctx.UnsignedIntTy;
      case LengthModifier::AsInt32:
        return ArgType(Ctx.UnsignedIntTy, "unsigned __int32");
      case LengthModifier::AsChar: return Ctx.UnsignedCharTy;
      case LengthModifier::AsShort: return Ctx.UnsignedShortTy;
      case LengthModifier::AsLong: return Ctx.UnsignedLongTy;
      case LengthModifier::AsLongLong:
      case LengthModifier::AsQuad:
        return Ctx.UnsignedLongLongTy;
      case LengthModifier::AsInt64:
        return ArgType(Ctx.UnsignedLongLongTy, "unsigned __int64");
      case LengthModifier::AsIntMax:
        return ArgType(Ctx.getUIntMaxType(), "uintmax_t");
      case LengthModifier::AsSizeT:
        return ArgType(Ctx.getSizeType(), "size_t");
      case LengthModifier::AsInt3264:
        return Ctx.getTargetInfo().getTriple().isArch64Bit()
                   ? ArgType(Ctx.UnsignedLongLongTy, "unsigned __int64")
                   : ArgType(Ctx.UnsignedIntTy, "unsigned __int32");
      case LengthModifier::AsPtrDiff:
        // FIXME: How to get the corresponding unsigned
        // version of ptrdiff_t?
        return ArgType();
      case LengthModifier::AsAllocate:
      case LengthModifier::AsMAllocate:
      case LengthModifier::AsWide:
        return ArgType::Invalid();
    }

  if (CS.isDoubleArg()) {
    if (LM.getKind() == LengthModifier::AsLongDouble)
      return Ctx.LongDoubleTy;
    return Ctx.DoubleTy;
  }

  if (CS.getKind() == ConversionSpecifier::nArg) {
    switch (LM.getKind()) {
      case LengthModifier::None:
        return ArgType::PtrTo(Ctx.IntTy);
      case LengthModifier::AsChar:
        return ArgType::PtrTo(Ctx.SignedCharTy);
      case LengthModifier::AsShort:
        return ArgType::PtrTo(Ctx.ShortTy);
      case LengthModifier::AsLong:
        return ArgType::PtrTo(Ctx.LongTy);
      case LengthModifier::AsLongLong:
      case LengthModifier::AsQuad:
        return ArgType::PtrTo(Ctx.LongLongTy);
      case LengthModifier::AsIntMax:
        return ArgType::PtrTo(ArgType(Ctx.getIntMaxType(), "intmax_t"));
      case LengthModifier::AsSizeT:
        return ArgType(); // FIXME: ssize_t
      case LengthModifier::AsPtrDiff:
        return ArgType::PtrTo(ArgType(Ctx.getPointerDiffType(), "ptrdiff_t"));
      case LengthModifier::AsLongDouble:
        return ArgType(); // FIXME: Is this a known extension?
      case LengthModifier::AsAllocate:
      case LengthModifier::AsMAllocate:
      case LengthModifier::AsInt32:
      case LengthModifier::AsInt3264:
      case LengthModifier::AsInt64:
      case LengthModifier::AsWide:
        return ArgType::Invalid();
    }
  }

  switch (CS.getKind()) {
    case ConversionSpecifier::sArg:
      if (LM.getKind() == LengthModifier::AsWideChar) {
        if (IsObjCLiteral)
          return ArgType(Ctx.getPointerType(Ctx.UnsignedShortTy.withConst()),
                         "const unichar *");
        return ArgType(ArgType::WCStrTy, "wchar_t *");
      }
      if (LM.getKind() == LengthModifier::AsWide)
        return ArgType(ArgType::WCStrTy, "wchar_t *");
      return ArgType::CStrTy;
    case ConversionSpecifier::SArg:
      if (IsObjCLiteral)
        return ArgType(Ctx.getPointerType(Ctx.UnsignedShortTy.withConst()),
                       "const unichar *");
      if (Ctx.getTargetInfo().getTriple().isOSMSVCRT() &&
          LM.getKind() == LengthModifier::AsShort)
        return ArgType::CStrTy;
      return ArgType(ArgType::WCStrTy, "wchar_t *");
    case ConversionSpecifier::CArg:
      if (IsObjCLiteral)
        return ArgType(Ctx.UnsignedShortTy, "unichar");
      if (Ctx.getTargetInfo().getTriple().isOSMSVCRT() &&
          LM.getKind() == LengthModifier::AsShort)
        return Ctx.IntTy;
      return ArgType(Ctx.WideCharTy, "wchar_t");
    case ConversionSpecifier::pArg:
    case ConversionSpecifier::PArg:
      return ArgType::CPointerTy;
    case ConversionSpecifier::ObjCObjArg:
      return ArgType::ObjCPointerTy;
    default:
      break;
  }

  // FIXME: Handle other cases.
  return ArgType();
}