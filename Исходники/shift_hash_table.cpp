ull ShiftHashTable::scale_hash(ull hash)
{
  return llround(hash * scale_multiplier);
}