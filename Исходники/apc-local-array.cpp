ArrayData *APCLocalArray::RemoveInt(ArrayData* ad, int64_t k, bool copy) {
  ArrayData *escalated = Escalate(ad);
  return releaseIfCopied(escalated, escalated->remove(k, false));
}