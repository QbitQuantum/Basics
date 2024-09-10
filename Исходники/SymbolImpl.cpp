Ref<RegisteredSymbolImpl> RegisteredSymbolImpl::create(StringImpl& rep, SymbolRegistry& symbolRegistry)
{
    auto* ownerRep = (rep.bufferOwnership() == BufferSubstring) ? rep.substringBuffer() : &rep;
    ASSERT(ownerRep->bufferOwnership() != BufferSubstring);
    if (rep.is8Bit())
        return adoptRef(*new RegisteredSymbolImpl(rep.m_data8, rep.length(), *ownerRep, symbolRegistry));
    return adoptRef(*new RegisteredSymbolImpl(rep.m_data16, rep.length(), *ownerRep, symbolRegistry));
}