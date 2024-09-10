guint
gum_peek_private_memory_usage (void)
{
  guint total_size = 0;
  BOOL success;
  PROCESS_HEAP_ENTRY entry;

  success = HeapLock (_gum_memory_heap);
  g_assert (success);

  entry.lpData = NULL;
  while (HeapWalk (_gum_memory_heap, &entry) != FALSE)
  {
    if ((entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) != 0)
      total_size += entry.cbData;
  }

  success = HeapUnlock (_gum_memory_heap);
  g_assert (success);

  return total_size;
}