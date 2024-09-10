GlobalDataTypeRegistry::RegistResult GlobalDataTypeRegistry::remove(Entry* dtd)
{
    if (!dtd)
    {
        UAVCAN_ASSERT(0);
        return RegistResultInvalidParams;
    }
    if (isFrozen())
    {
        return RegistResultFrozen;
    }

    List* list = selectList(dtd->descriptor.getKind());
    if (!list)
    {
        return RegistResultInvalidParams;
    }

    list->remove(dtd);       // If this call came from regist<>(), that would be enough
    Entry* p = list->get();  // But anyway
    while (p)
    {
        Entry* const next = p->getNextListNode();
        if (p->descriptor.match(dtd->descriptor.getKind(), dtd->descriptor.getFullName()))
        {
            list->remove(p);
        }
        p = next;
    }
    return RegistResultOk;
}