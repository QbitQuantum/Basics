static void unregisterStructInfo(CacheFragInfo *CacheFrag) {
  // FIXME: if the library is unloaded before finalizeCacheFrag, we should
  // collect the result for later report.
  for (u32 i = 0; i < CacheFrag->NumStructs; ++i) {
    StructInfo *Struct = &CacheFrag->Structs[i];
    StructHashMap::Handle H(&Ctx->StructMap, (uptr)Struct->FieldCounters, true);
    if (H.exists()) {
      VPrintf(2, " Unregister %s: %u fields\n", Struct->StructName,
              Struct->NumFields);
      // FIXME: we should move this call to finalizeCacheFrag once we can
      // iterate over the hash map there.
      computeStructRatio(H);
      --Ctx->NumStructs;
    } else {
      VPrintf(2, " Duplicated %s: %u fields\n", Struct->StructName,
              Struct->NumFields);
    }
  }
  static bool Reported = false;
  if (Ctx->NumStructs == 0 && !Reported) {
    Reported = true;
    reportStructSummary();
  }
}