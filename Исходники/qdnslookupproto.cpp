void QDnsLookupProto::abort()
{
  QDnsLookup *item = qscriptvalue_cast<QDnsLookup*>(thisObject());
  if (item)
    item->abort();
}