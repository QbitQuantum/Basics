static FunctionMeta* FindFunction(lua_State* L, lua_Debug* ar)
{
  // This is slow, it involves string formatting. It's mostly OK, because we're
  // careful not to include this in the timings. It will of course affect cache
  // and other things. Not that we can make a lot of informed decisions about
  // that in an interpreted language anyway.
  if (!lua_getinfo(L, "Sn", ar))
    Croak("couldn't get debug info for function call");

  char buffer[1024];
  snprintf(buffer, sizeof(buffer), "%s;%s;%s;%d",
      ar->name ? ar->name : "", ar->namewhat ? ar->namewhat : "", ar->source, ar->linedefined);
  buffer[(sizeof buffer)-1] = 0;

  const uint32_t hash = Djb2Hash(buffer);
  HashRecord* r = HashTableLookup(&s_Profiler.m_Functions, hash, buffer);

  if (!r) {
    r = LinearAllocate<FunctionMeta>(s_Profiler.m_Allocator);
    r->m_Hash   = hash;
    r->m_String = StrDup(s_Profiler.m_Allocator, buffer);
    r->m_Next   = nullptr;
    HashTableInsert(&s_Profiler.m_Functions, r);
  }
  
  return static_cast<FunctionMeta*>(r);
}