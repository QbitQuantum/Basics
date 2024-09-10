const RsPointerType* TypeSystem::getPointerType(const std::string& name, AddressDesc desc)
{
    const RsType* bt = getTypeInfo(name);
    return getPointerType(bt, desc);
}