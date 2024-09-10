ValueObjectSP
GoUserExpression::GoInterpreter::VisitBasicLit(const lldb_private::GoASTBasicLit *e)
{
    std::string value = e->GetValue().m_value.str();
    if (e->GetValue().m_type != GoLexer::LIT_INTEGER)
    {
        m_error.SetErrorStringWithFormat("Unsupported literal %s", value.c_str());
        return nullptr;
    }
    errno = 0;
    int64_t intvalue = strtol(value.c_str(), nullptr, 0);
    if (errno != 0)
    {
        m_error.SetErrorToErrno();
        return nullptr;
    }
    DataBufferSP buf(new DataBufferHeap(sizeof(intvalue), 0));
    TargetSP target = m_exe_ctx.GetTargetSP();
    if (!target)
    {
        m_error.SetErrorString("No target");
        return nullptr;
    }
    ByteOrder order = target->GetArchitecture().GetByteOrder();
    uint8_t addr_size = target->GetArchitecture().GetAddressByteSize();
    DataEncoder enc(buf, order, addr_size);
    enc.PutU64(0, static_cast<uint64_t>(intvalue));
    DataExtractor data(buf, order, addr_size);

    CompilerType type = LookupType(target, ConstString("int64"));
    return ValueObject::CreateValueObjectFromData(nullptr, data, m_exe_ctx, type);
}