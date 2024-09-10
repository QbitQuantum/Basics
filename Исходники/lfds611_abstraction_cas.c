static LFDS611_INLINE lfds611_atom_t lfds611_abstraction_cas( volatile lfds611_atom_t *destination, lfds611_atom_t exchange, lfds611_atom_t compare )
{
  lfds611_atom_t
  rv;

  assert( destination != NULL );
  // TRD : exchange can be any value in its range
  // TRD : compare can be any value in its range

  LFDS611_BARRIER_COMPILER_FULL;

  rv = (lfds611_atom_t) _InterlockedCompareExchangePointer( (void * volatile *) destination, (void *) exchange, (void *) compare );

  LFDS611_BARRIER_COMPILER_FULL;

  return( rv );
}