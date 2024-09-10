/* Free the whole mcode heap. */
void luaJIT_freemcodeheap(jit_State *J)
{
  if (J->mcodeheap) HeapDestroy((HANDLE)J->mcodeheap);
}