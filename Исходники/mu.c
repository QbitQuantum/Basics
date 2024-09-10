//----------------------------------------------------------------------------
// MemUFlushPattern:
//
//  Flush a pattern of 72 bit times (per DQ) from cache.  This procedure is used
//  to ensure cache miss on the next read training.
//
//              In: Address   - Physical address to be flushed
//                  ClCount   - number of cachelines to be flushed
//FUNC_ATTRIBUTE(noinline)
VOID
MemUFlushPattern (
  IN       UINT32 Address,
  IN       UINT16 ClCount
  )
{
  UINTN Index;

  // ssd - theory: a tlb flush is needed to avoid problems with clflush
  __writemsr (0x20F, __readmsr (0x20F));

  for (Index = 0; Index < ClCount; Index++) {
    // mfence prevents speculative execution of the clflush
    _mm_mfence ();
    _mm_clflush_fs ((void *) (size_t) (Address + Index * 64));
  }
}