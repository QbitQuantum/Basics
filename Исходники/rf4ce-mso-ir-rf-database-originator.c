static EmberStatus setEntry(uint8_t index,
                            const EmberAfRf4ceMsoIrRfDatabaseEntry *entry)
{
  // When a new entry comes in, we always remove the old entry, even though the
  // new entry might not fit.  The rationale is that the old entry is being
  // replaced because it is no longer valid for the peripheral devices in the
  // system.  Reverting to a default entry seems better than keeping the old,
  // invalid entry.
  uint32_t reclaimableBytes = calculateHeapUsage(&database[index]);
  if (reclaimableBytes != 0) {
    uint8_t *head;
    uint8_t i;

    // If the space we think we are using is ever less than what we think we
    // can reclaim, then something has gone very wrong.
    assert(reclaimableBytes <= USED_HEAP_SPACE());

    // The RF payloads and the IR code are all stored contiguously in the heap,
    // although some of them may be empty.  We just need to find whichever one
    // is first.  If we expect to have one but can't find it or we do find it
    // but its not actually within the heap area, then something has gone very
    // wrong.
    head = findHead(&database[index]);
    assert(head != NULL);
    assert(heap <= head);
    assert(head + reclaimableBytes <= tail);

    // Rewind the tail pointer and all the RF payload and IR code pointers for
    // entries that follow the old one.  This makes them point to where they
    // should after the heap is adjusted.  This means the pointers are NOT
    // valid until the heap is adjusted.
    tail -= reclaimableBytes;
    for (i = 0; i < COUNTOF(database); i++) {
      if (head < database[i].rfPressedDescriptor.payload) {
        database[i].rfPressedDescriptor.payload -= reclaimableBytes;
      }
      if (head < database[i].rfRepeatedDescriptor.payload) {
        database[i].rfRepeatedDescriptor.payload -= reclaimableBytes;
      }
      if (head < database[i].rfReleasedDescriptor.payload) {
        database[i].rfReleasedDescriptor.payload -= reclaimableBytes;
      }
      if (head < database[i].irDescriptor.irCode) {
        database[i].irDescriptor.irCode -= reclaimableBytes;
      }
    }

    // Move the stuff after the old entry so it immediately follows the stuff
    // preceding the old entry.  The old entry is now gone and the tail, RF
    // payload, and IR pointers are all valid again.
    MEMMOVE(head, head + reclaimableBytes, tail - head);

    // Wipe the stuff following the new tail.
    MEMSET(tail, 0, reclaimableBytes);
  }

  // The free space is the unused space and includes what we reclaimed from the
  // old entry.  If we don't have enough room, we drop the new entry and leave
  // a default in its place.
  if (FREE_HEAP_SPACE() < calculateHeapUsage(entry)) {
    SET_DEFAULT(&database[index]);
    return EMBER_TABLE_FULL;
  }

  // The basic structure of the new entry is copied as is to the database.  The
  // variable-sized portion of each descriptor is copied into the heap and then
  // the pointer to that data from the database is adjusted to point into the
  // heap.
  MEMCOPY(&database[index], entry, sizeof(EmberAfRf4ceMsoIrRfDatabaseEntry));
  database[index].rfPressedDescriptor.payload
    = copyRfPayload(emberAfRf4ceMsoIrRfDatabaseEntryHasRfPressedDescriptor(entry),
                    &entry->rfPressedDescriptor);
  database[index].rfRepeatedDescriptor.payload
    = copyRfPayload(emberAfRf4ceMsoIrRfDatabaseEntryHasRfRepeatedDescriptor(entry),
                    &entry->rfRepeatedDescriptor);
  database[index].rfReleasedDescriptor.payload
    = copyRfPayload(emberAfRf4ceMsoIrRfDatabaseEntryHasRfReleasedDescriptor(entry),
                    &entry->rfReleasedDescriptor);
  database[index].irDescriptor.irCode
    = copyIrCode(emberAfRf4ceMsoIrRfDatabaseEntryHasIrDescriptor(entry),
                 &entry->irDescriptor);

  return EMBER_SUCCESS;
}