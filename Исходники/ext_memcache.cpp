bool c_Memcache::t_add(CStrRef key, CVarRef var, int flag /*= 0*/,
                       int expire /*= 0*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::add);
  if (key.empty()) {
    raise_warning("Key cannot be empty");
    return false;
  }

  String serialized = memcache_prepare_for_storage(var, flag);

  memcached_return_t ret = memcached_add(&m_memcache,
                                        key.c_str(), key.length(),
                                        serialized.c_str(),
                                        serialized.length(),
                                        expire, flag);

  return (ret == MEMCACHED_SUCCESS);
}