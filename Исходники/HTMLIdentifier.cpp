void HTMLIdentifier::addNames(QualifiedName** names, unsigned namesCount, unsigned indexOffset)
{
    IdentifierTable& table = identifierTable();
    for (unsigned i = 0; i < namesCount; ++i) {
        StringImpl* name = names[i]->localName().impl();
        unsigned hash = name->hash();
        unsigned index = i + indexOffset;
        IdentifierEntry entry(index, name);
        IdentifierTable::AddResult addResult = table.add(hash, entry);
        maxNameLength = std::max(maxNameLength, name->length());
        // Ensure we're using the same hashing algorithm to get and set.
        ASSERT_UNUSED(addResult, !addResult.isNewEntry || HTMLIdentifier::findIndex(name->characters(), name->length()) == index);
        // We expect some hash collisions, but only for identical strings.
        // Since all of these names are AtomicStrings pointers should be equal.
        // Note: If you hit this ASSERT, then we had a hash collision among
        // HTMLNames strings, and we need to re-design how we use this hash!
        ASSERT_UNUSED(addResult, !addResult.isNewEntry || name == addResult.iterator->value.second);
    }
}