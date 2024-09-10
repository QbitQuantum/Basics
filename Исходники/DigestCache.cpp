void DigestCacheSet(DigestCache* self, const char* filename, uint32_t hash, uint64_t timestamp, const HashDigest& digest)
{
  ReadWriteLockWrite(&self->m_Lock);

  DigestCacheRecord* r;

  if (nullptr != (r = (DigestCacheRecord*) HashTableLookup(&self->m_Table, hash, filename)))
  {
    r->m_Timestamp     = timestamp;
    r->m_ContentDigest = digest;
    r->m_AccessTime    = self->m_AccessTime;
  }
  else
  {
    r = LinearAllocate<DigestCacheRecord>(&self->m_Allocator);
    r->m_Hash          = hash;
    r->m_ContentDigest = digest;
    r->m_Next          = nullptr;
    r->m_String        = StrDup(&self->m_Allocator, filename);
    r->m_Timestamp     = timestamp;
    r->m_AccessTime    = self->m_AccessTime;
    HashTableInsert(&self->m_Table, r);
  }

  ReadWriteUnlockWrite(&self->m_Lock);
}