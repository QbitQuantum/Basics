static LFDS611_INLINE                   lfds611_atom_t
lfds611_abstraction_increment (
  volatile lfds611_atom_t * value)
{
  lfds611_atom_t                          rv;

  assert (value != NULL);
  LFDS611_BARRIER_COMPILER_FULL;
  rv = (lfds611_atom_t) _InterlockedIncrement64 ((__int64 *) value);
  LFDS611_BARRIER_COMPILER_FULL;
  return (rv);
}