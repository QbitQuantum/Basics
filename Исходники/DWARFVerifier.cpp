unsigned DWARFVerifier::verifyDebugInfoAttribute(const DWARFDie &Die,
                                                 DWARFAttribute &AttrValue) {
  unsigned NumErrors = 0;
  auto ReportError = [&](const Twine &TitleMsg) {
    ++NumErrors;
    error() << TitleMsg << '\n';
    Die.dump(OS, 0, DumpOpts);
    OS << "\n";
  };

  const DWARFObject &DObj = DCtx.getDWARFObj();
  const auto Attr = AttrValue.Attr;
  switch (Attr) {
  case DW_AT_ranges:
    // Make sure the offset in the DW_AT_ranges attribute is valid.
    if (auto SectionOffset = AttrValue.Value.getAsSectionOffset()) {
      if (*SectionOffset >= DObj.getRangeSection().Data.size())
        ReportError("DW_AT_ranges offset is beyond .debug_ranges bounds:");
      break;
    }
    ReportError("DIE has invalid DW_AT_ranges encoding:");
    break;
  case DW_AT_stmt_list:
    // Make sure the offset in the DW_AT_stmt_list attribute is valid.
    if (auto SectionOffset = AttrValue.Value.getAsSectionOffset()) {
      if (*SectionOffset >= DObj.getLineSection().Data.size())
        ReportError("DW_AT_stmt_list offset is beyond .debug_line bounds: " +
                    llvm::formatv("{0:x8}", *SectionOffset));
      break;
    }
    ReportError("DIE has invalid DW_AT_stmt_list encoding:");
    break;
  case DW_AT_location: {
    auto VerifyLocation = [&](StringRef D) {
      DWARFUnit *U = Die.getDwarfUnit();
      DataExtractor Data(D, DCtx.isLittleEndian(), 0);
      DWARFExpression Expression(Data, U->getVersion(),
                                 U->getAddressByteSize());
      bool Error = llvm::any_of(Expression, [](DWARFExpression::Operation &Op) {
        return Op.isError();
      });
      if (Error)
        ReportError("DIE contains invalid DWARF expression:");
    };
    if (Optional<ArrayRef<uint8_t>> Expr = AttrValue.Value.getAsBlock()) {
      // Verify inlined location.
      VerifyLocation(llvm::toStringRef(*Expr));
    } else if (auto LocOffset = AttrValue.Value.getAsUnsignedConstant()) {
      // Verify location list.
      if (auto DebugLoc = DCtx.getDebugLoc())
        if (auto LocList = DebugLoc->getLocationListAtOffset(*LocOffset))
          for (const auto &Entry : LocList->Entries)
            VerifyLocation({Entry.Loc.data(), Entry.Loc.size()});
    }
    break;
  }

  default:
    break;
  }
  return NumErrors;
}