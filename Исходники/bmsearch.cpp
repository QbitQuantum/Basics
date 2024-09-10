int32_t BadCharacterTable::hash(uint32_t ce)
{
    return UCOL_PRIMARYORDER(ce) % HASH_TABLE_SIZE;
}