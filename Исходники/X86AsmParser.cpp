bool X86ATTAsmParser::
MatchAndEmitInstruction(SMLoc IDLoc,
                        SmallVectorImpl<MCParsedAsmOperand*> &Operands,
                        MCStreamer &Out) {
  assert(!Operands.empty() && "Unexpect empty operand list!");
  X86Operand *Op = static_cast<X86Operand*>(Operands[0]);
  assert(Op->isToken() && "Leading operand should always be a mnemonic!");

  // First, handle aliases that expand to multiple instructions.
  // FIXME: This should be replaced with a real .td file alias mechanism.
  // Also, MatchInstructionImpl should do actually *do* the EmitInstruction
  // call.
  if (Op->getToken() == "fstsw" || Op->getToken() == "fstcw" ||
      Op->getToken() == "fstsww" || Op->getToken() == "fstcww" ||
      Op->getToken() == "finit" || Op->getToken() == "fsave" ||
      Op->getToken() == "fstenv" || Op->getToken() == "fclex") {
    MCInst Inst;
    Inst.setOpcode(X86::WAIT);
    Out.EmitInstruction(Inst);

    const char *Repl =
      StringSwitch<const char*>(Op->getToken())
        .Case("finit",  "fninit")
        .Case("fsave",  "fnsave")
        .Case("fstcw",  "fnstcw")
        .Case("fstcww",  "fnstcw")
        .Case("fstenv", "fnstenv")
        .Case("fstsw",  "fnstsw")
        .Case("fstsww", "fnstsw")
        .Case("fclex",  "fnclex")
        .Default(0);
    assert(Repl && "Unknown wait-prefixed instruction");
    delete Operands[0];
    Operands[0] = X86Operand::CreateToken(Repl, IDLoc);
  }

  bool WasOriginallyInvalidOperand = false;
  unsigned OrigErrorInfo;
  MCInst Inst;

  // First, try a direct match.
  switch (MatchInstructionImpl(Operands, Inst, OrigErrorInfo)) {
  case Match_Success:
    Out.EmitInstruction(Inst);
    return false;
  case Match_MissingFeature:
    Error(IDLoc, "instruction requires a CPU feature not currently enabled");
    return true;
  case Match_ConversionFail:
    return Error(IDLoc, "unable to convert operands to instruction");
  case Match_InvalidOperand:
    WasOriginallyInvalidOperand = true;
    break;
  case Match_MnemonicFail:
    break;
  }

  // FIXME: Ideally, we would only attempt suffix matches for things which are
  // valid prefixes, and we could just infer the right unambiguous
  // type. However, that requires substantially more matcher support than the
  // following hack.

  // Change the operand to point to a temporary token.
  StringRef Base = Op->getToken();
  SmallString<16> Tmp;
  Tmp += Base;
  Tmp += ' ';
  Op->setTokenValue(Tmp.str());

  // If this instruction starts with an 'f', then it is a floating point stack
  // instruction.  These come in up to three forms for 32-bit, 64-bit, and
  // 80-bit floating point, which use the suffixes s,l,t respectively.
  //
  // Otherwise, we assume that this may be an integer instruction, which comes
  // in 8/16/32/64-bit forms using the b,w,l,q suffixes respectively.
  const char *Suffixes = Base[0] != 'f' ? "bwlq" : "slt\0";
  
  // Check for the various suffix matches.
  Tmp[Base.size()] = Suffixes[0];
  unsigned ErrorInfoIgnore;
  MatchResultTy Match1, Match2, Match3, Match4;
  
  Match1 = MatchInstructionImpl(Operands, Inst, ErrorInfoIgnore);
  Tmp[Base.size()] = Suffixes[1];
  Match2 = MatchInstructionImpl(Operands, Inst, ErrorInfoIgnore);
  Tmp[Base.size()] = Suffixes[2];
  Match3 = MatchInstructionImpl(Operands, Inst, ErrorInfoIgnore);
  Tmp[Base.size()] = Suffixes[3];
  Match4 = MatchInstructionImpl(Operands, Inst, ErrorInfoIgnore);

  // Restore the old token.
  Op->setTokenValue(Base);

  // If exactly one matched, then we treat that as a successful match (and the
  // instruction will already have been filled in correctly, since the failing
  // matches won't have modified it).
  unsigned NumSuccessfulMatches =
    (Match1 == Match_Success) + (Match2 == Match_Success) +
    (Match3 == Match_Success) + (Match4 == Match_Success);
  if (NumSuccessfulMatches == 1) {
    Out.EmitInstruction(Inst);
    return false;
  }

  // Otherwise, the match failed, try to produce a decent error message.

  // If we had multiple suffix matches, then identify this as an ambiguous
  // match.
  if (NumSuccessfulMatches > 1) {
    char MatchChars[4];
    unsigned NumMatches = 0;
    if (Match1 == Match_Success) MatchChars[NumMatches++] = Suffixes[0];
    if (Match2 == Match_Success) MatchChars[NumMatches++] = Suffixes[1];
    if (Match3 == Match_Success) MatchChars[NumMatches++] = Suffixes[2];
    if (Match4 == Match_Success) MatchChars[NumMatches++] = Suffixes[3];

    SmallString<126> Msg;
    raw_svector_ostream OS(Msg);
    OS << "ambiguous instructions require an explicit suffix (could be ";
    for (unsigned i = 0; i != NumMatches; ++i) {
      if (i != 0)
        OS << ", ";
      if (i + 1 == NumMatches)
        OS << "or ";
      OS << "'" << Base << MatchChars[i] << "'";
    }
    OS << ")";
    Error(IDLoc, OS.str());
    return true;
  }

  // Okay, we know that none of the variants matched successfully.

  // If all of the instructions reported an invalid mnemonic, then the original
  // mnemonic was invalid.
  if ((Match1 == Match_MnemonicFail) && (Match2 == Match_MnemonicFail) &&
      (Match3 == Match_MnemonicFail) && (Match4 == Match_MnemonicFail)) {
    if (!WasOriginallyInvalidOperand) {
      Error(IDLoc, "invalid instruction mnemonic '" + Base + "'");
      return true;
    }

    // Recover location info for the operand if we know which was the problem.
    SMLoc ErrorLoc = IDLoc;
    if (OrigErrorInfo != ~0U) {
      if (OrigErrorInfo >= Operands.size())
        return Error(IDLoc, "too few operands for instruction");

      ErrorLoc = ((X86Operand*)Operands[OrigErrorInfo])->getStartLoc();
      if (ErrorLoc == SMLoc()) ErrorLoc = IDLoc;
    }

    return Error(ErrorLoc, "invalid operand for instruction");
  }

  // If one instruction matched with a missing feature, report this as a
  // missing feature.
  if ((Match1 == Match_MissingFeature) + (Match2 == Match_MissingFeature) +
      (Match3 == Match_MissingFeature) + (Match4 == Match_MissingFeature) == 1){
    Error(IDLoc, "instruction requires a CPU feature not currently enabled");
    return true;
  }

  // If one instruction matched with an invalid operand, report this as an
  // operand failure.
  if ((Match1 == Match_InvalidOperand) + (Match2 == Match_InvalidOperand) +
      (Match3 == Match_InvalidOperand) + (Match4 == Match_InvalidOperand) == 1){
    Error(IDLoc, "invalid operand for instruction");
    return true;
  }

  // If all of these were an outright failure, report it in a useless way.
  // FIXME: We should give nicer diagnostics about the exact failure.
  Error(IDLoc, "unknown use of instruction mnemonic without a size suffix");
  return true;
}