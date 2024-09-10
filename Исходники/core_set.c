void embb_core_set_init(embb_core_set_t* core_set, int initializer) {
  assert(core_set != NULL);
  assert(embb_core_count_available() < 64 &&
    "Core sets are only supported up to 64 processors!");

  /* Cache windows processor grouping information */
  if (processor_info.group_count == 0) {
    /* Set relation group */
    LOGICAL_PROCESSOR_RELATIONSHIP rel = (LOGICAL_PROCESSOR_RELATIONSHIP)4;
    /* Assume only one element of SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX is
       returned to the buffer. */
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX buffer;
    /* The length is that of the buffer */
    DWORD length = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
    BOOL status = GetLogicalProcessorInformationEx(rel, &buffer, &length);
    assert(status == TRUE);
    EMBB_UNUSED_IN_RELEASE(status);
    processor_info.group_count = buffer.Group.ActiveGroupCount;
    for (unsigned short i = 0; i < processor_info.group_count; i++) {
      processor_info.processor_counts[i] =
        (unsigned short)(buffer.Group.GroupInfo[i].ActiveProcessorCount);
    }
  }

  if (initializer == 0) {
    embb_bitset_clear_all(&core_set->rep);
  } else {
    embb_bitset_set_n(&core_set->rep, embb_core_count_available());
  }
}