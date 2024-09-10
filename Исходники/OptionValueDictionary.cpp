void OptionValueDictionary::DumpValue(const ExecutionContext *exe_ctx,
                                      Stream &strm, uint32_t dump_mask) {
  const Type dict_type = ConvertTypeMaskToType(m_type_mask);
  if (dump_mask & eDumpOptionType) {
    if (m_type_mask != eTypeInvalid)
      strm.Printf("(%s of %ss)", GetTypeAsCString(),
                  GetBuiltinTypeAsCString(dict_type));
    else
      strm.Printf("(%s)", GetTypeAsCString());
  }
  if (dump_mask & eDumpOptionValue) {
    const bool one_line = dump_mask & eDumpOptionCommand;
    if (dump_mask & eDumpOptionType)
      strm.PutCString(" =");

    collection::iterator pos, end = m_values.end();

    if (!one_line)
      strm.IndentMore();

    for (pos = m_values.begin(); pos != end; ++pos) {
      OptionValue *option_value = pos->second.get();

      if (one_line)
        strm << ' ';
      else
        strm.EOL();

      strm.Indent(pos->first.GetCString());

      const uint32_t extra_dump_options = m_raw_value_dump ? eDumpOptionRaw : 0;
      switch (dict_type) {
      default:
      case eTypeArray:
      case eTypeDictionary:
      case eTypeProperties:
      case eTypeFileSpecList:
      case eTypePathMap:
        strm.PutChar(' ');
        option_value->DumpValue(exe_ctx, strm, dump_mask | extra_dump_options);
        break;

      case eTypeBoolean:
      case eTypeChar:
      case eTypeEnum:
      case eTypeFileSpec:
      case eTypeFormat:
      case eTypeSInt64:
      case eTypeString:
      case eTypeUInt64:
      case eTypeUUID:
        // No need to show the type for dictionaries of simple items
        strm.PutCString("=");
        option_value->DumpValue(exe_ctx, strm,
                                (dump_mask & (~eDumpOptionType)) |
                                    extra_dump_options);
        break;
      }
    }
    if (!one_line)
      strm.IndentLess();
  }
}