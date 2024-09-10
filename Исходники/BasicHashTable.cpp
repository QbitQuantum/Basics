void BasicHashTable::assignKey(TableEntry *entry, char const *key)
{
    // The way we assign the key depends upon its type:
    if (fKeyType == STRING_HASH_KEYS)
    {
        entry->key = strDup(key);
    }
    else if (fKeyType == ONE_WORD_HASH_KEYS)
    {
        entry->key = key;
    }
    else if (fKeyType > 0)
    {
        unsigned *keyFrom = (unsigned *)key;
        unsigned *keyTo = new unsigned[fKeyType];
        for (int i = 0; i < fKeyType; ++i) keyTo[i] = keyFrom[i];

        entry->key = (char const *)keyTo;
    }
}