bool cResponsePacket::add_double(double d)
{
  if (!checkExtend(sizeof(double))) return false;
  uint64_t ull;
  memcpy(&ull,&d,sizeof(double));
  *(uint64_t*)&buffer[bufUsed] = htonll(ull);
  bufUsed += sizeof(uint64_t);
  return true;
}