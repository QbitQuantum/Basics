inline bool objectCopy(JsonObjectData* dst, const JsonObjectData* src,
                       MemoryPool* pool) {
  if (!dst || !src) return false;
  objectClear(dst);
  for (VariantSlot* s = src->head; s; s = s->next) {
    JsonVariantData* var;
    if (s->value.keyIsOwned)
      var = objectAdd(dst, ZeroTerminatedRamString(s->ownedKey->value), pool);
    else
      var = objectAdd(dst, ZeroTerminatedRamStringConst(s->linkedKey), pool);
    if (!variantCopy(var, &s->value, pool)) return false;
  }
  return true;
}