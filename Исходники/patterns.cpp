UINT64 _inline longhash1(UINT64 key)
{
  key += ~(key << 32);
  key ^= _rotr64(key,22);
  key += ~(key << 13);
  key ^= _rotr64(key,8);
  key += (key << 3);
  key ^= _rotr64(key,15);
  key += ~(key << 27);
  key ^= _rotr64(key,31);
  return key;
}