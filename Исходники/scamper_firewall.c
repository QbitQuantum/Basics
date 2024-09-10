static void firewall_rule_delete(scamper_firewall_entry_t *entry)
{
#if defined(HAVE_IPFW)
  int af;

  if(entry->rule->sfw_5tuple_src->type == SCAMPER_ADDR_TYPE_IPV4)
    af = AF_INET;
  else
    af = AF_INET6;

#ifdef WITHOUT_PRIVSEP
  scamper_firewall_ipfw_del(entry->slot, af);
#else
  scamper_privsep_ipfw_del(entry->slot, af);
#endif
#endif

  /* put the rule back into the freeslots heap */
  if(heap_insert(freeslots, entry) == NULL)
    {
      printerror(errno, strerror, __func__,
		 "could not add entry %d", entry->slot);
      firewall_entry_free(entry);
    }

  /* free up the firewall rule associated with the entry */
  firewall_rule_free(entry->rule);
  entry->rule = NULL;

  return;
}