PassRefPtr<Structure> Structure::removePropertyTransition(Structure* structure, const Identifier& propertyName, size_t& offset)
{
    ASSERT(!structure->isUncacheableDictionary());

    RefPtr<Structure> transition = toUncacheableDictionaryTransition(structure);

    offset = transition->remove(propertyName);
    ASSERT(offset >= structure->m_anonymousSlotCount);
    ASSERT(structure->m_anonymousSlotCount == transition->m_anonymousSlotCount);

    return transition.release();
}