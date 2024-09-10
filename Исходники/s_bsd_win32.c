void
delete_resolver_queries(const struct DNSQuery *query)
{
  WSACancelAsyncRequest(query->handle);
  dlinkDelete(&query->node, &dns_queries);
}