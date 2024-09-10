static DWARFExpression MakeLocationExpressionInternal(lldb::ModuleSP module,
                                                      StreamWriter &&writer) {
  const ArchSpec &architecture = module->GetArchitecture();
  ByteOrder byte_order = architecture.GetByteOrder();
  uint32_t address_size = architecture.GetAddressByteSize();
  uint32_t byte_size = architecture.GetDataByteSize();
  if (byte_order == eByteOrderInvalid || address_size == 0)
    return DWARFExpression(nullptr);

  RegisterKind register_kind = eRegisterKindDWARF;
  StreamBuffer<32> stream(Stream::eBinary, address_size, byte_order);

  if (!writer(stream, register_kind))
    return DWARFExpression(nullptr);

  DataBufferSP buffer =
      std::make_shared<DataBufferHeap>(stream.GetData(), stream.GetSize());
  DataExtractor extractor(buffer, byte_order, address_size, byte_size);
  DWARFExpression result(module, extractor, nullptr, 0, buffer->GetByteSize());
  result.SetRegisterKind(register_kind);

  return result;
}