/*
** Load the record data (flags, ...) - but not the picture
*/
static void LoadRecordData(void) {
  MemHandle t = NULL;
  MemPtr ptr = NULL;
  UInt16 attr = 0;
  UInt32 highDataOffset = 0;
  Int16 len = 0;

  PRINT("Loading Record Data for %hd", p.dbI);

  /* Clear unmasked flag */
  d.unmaskedCurrentRecord = false;

  /* Open and lock the record */
  t = DmQueryRecord(d.dbR, p.dbI);
  if (!t) abort();
  ptr = MemHandleLock(t);

  /* Is the record private? */
  DmRecordInfo(d.dbR, p.dbI, &attr, NULL, NULL);
  d.record_private = attr & dmRecAttrSecret;

  /* Read the header data */
  MemMove(&d.record, ptr, sizeof(DiddleBugRecordType));

  /* Read the additional alarm info */
  highDataOffset = sketchDataOffset + d.record.sketchLength;

  len = StrLen((Char*)(ptr + highDataOffset)) + 1; /* +1 for null char */
  if (d.record_name) MemHandleFree(d.record_name);
  d.record_name = MemHandleNew(len);
  ASSERT(d.record_name);
  MemMove(MemHandleLock(d.record_name), ptr + highDataOffset, len);
  MemHandleUnlock(d.record_name);

  highDataOffset += len;

  len = StrLen((Char*)(ptr + highDataOffset)) + 1; /* +1 for null char */
  if (d.record_note) MemHandleFree(d.record_note);
  d.record_note = MemHandleNew(len);
  ASSERT(d.record_note);
  MemMove(MemHandleLock(d.record_note), ptr + highDataOffset, len);
  MemHandleUnlock(d.record_note);

  highDataOffset += len;

  /* Clear old data since there may not be an extra-data block yet */
  MemSet(&d.record_sound, sizeof(AlarmSoundInfoType), 0);
  d.record_sound.listIndex = -1; /* default */
  /* Read new extra-data (if it exists and is from a compatible version) */
  if (d.record.extraLength == sizeof(AlarmSoundInfoType))
    MemMove(&d.record_sound, ptr + highDataOffset, d.record.extraLength);

  /* Unlock record */
  MemHandleUnlock(t);
}