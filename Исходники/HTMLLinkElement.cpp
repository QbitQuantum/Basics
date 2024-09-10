void HTMLLinkElement::OnDNSPrefetchDeferred() {
  UnsetFlags(HTML_LINK_DNS_PREFETCH_REQUESTED);
  SetFlags(HTML_LINK_DNS_PREFETCH_DEFERRED);
}