hash_enum_remove_queues(const void *aThread_ptr,
                        nsCOMPtr<nsIEventQueue>& aEldestQueue,
                        void* closure)
{
  // 'aQueue' should be the eldest queue.
  nsCOMPtr<nsPIEventQueueChain> pie(do_QueryInterface(aEldestQueue));
  nsCOMPtr<nsIEventQueue> q;

  // stop accepting events for youngest to oldest
  pie->GetYoungest(getter_AddRefs(q));
  while (q) {
    q->StopAcceptingEvents();

    nsCOMPtr<nsPIEventQueueChain> pq(do_QueryInterface(q));
    pq->GetElder(getter_AddRefs(q));
  }

  return PL_DHASH_REMOVE;
}