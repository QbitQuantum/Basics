template <class T> inline uint8_t generator_iter<T>::count()
{
  uint8_t nbr = _mm_popcnt_u32(mask); // popcnt returns a 8 bits value
  for (ind_t ib = iblock+1; ib < bound; ib++)
    nbr += _mm_popcnt_u32(movemask_epi8(m.blocks[ib] == block1));
  return nbr;
};