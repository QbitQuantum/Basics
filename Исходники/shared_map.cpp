ArrayData *SharedMap::remove(const StringData* k, bool copy) {
  ArrayData *escalated = SharedMap::escalate();
  return releaseIfCopied(escalated, escalated->remove(k, false));
}