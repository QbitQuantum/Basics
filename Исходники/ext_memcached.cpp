Variant c_Memcached::t_getbykey(CStrRef server_key, CStrRef key,
                                CVarRef cache_cb /*= null_variant*/,
                                VRefParam cas_token /*= null_variant*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcached, Memcached::getbykey);
  m_impl->rescode = q_Memcached_RES_SUCCESS;
  if (key.empty()) {
    m_impl->rescode = q_Memcached_RES_BAD_KEY_PROVIDED;
    return false;
  }

  memcached_behavior_set(&m_impl->memcached, MEMCACHED_BEHAVIOR_SUPPORT_CAS,
                         cas_token.isReferenced() ? 1 : 0);
  const char *myServerKey = server_key.empty() ? NULL : server_key.c_str();
  size_t myServerKeyLen = server_key.length();
  const char *myKey = key.c_str();
  size_t myKeyLen = key.length();
  memcached_return status = memcached_mget_by_key(&m_impl->memcached,
      myServerKey, myServerKeyLen, &myKey, &myKeyLen, 1);
  if (!handleError(status)) return false;

  Variant returnValue;
  MemcachedResultWrapper result(&m_impl->memcached);
  if (!memcached_fetch_result(&m_impl->memcached, &result.value, &status)) {
    if (status == MEMCACHED_END) status = MEMCACHED_NOTFOUND;
    if (status == MEMCACHED_NOTFOUND && !cache_cb.isNull()) {
      status = doCacheCallback(cache_cb, key, returnValue);
      if (!handleError(status)) return false;
      if (cas_token.isReferenced()) cas_token = 0.0;
      return returnValue;
    }
    handleError(status);
    return false;
  }

  if (!toObject(returnValue, result.value)) {
    m_impl->rescode = q_Memcached_RES_PAYLOAD_FAILURE;
    return false;
  }
  if (cas_token.isReferenced()) {
    cas_token = (double) memcached_result_cas(&result.value);
  }
  return returnValue;
}