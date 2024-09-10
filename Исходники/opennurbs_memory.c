size_t onmsize( const void* memblock )
{
  size_t sz = 0;

  if (memblock) 
  {
#if defined(ON_COMPILER_MSC)
    sz = _msize( (void*)memblock );
#elif defined(ON_COMPILER_XCODE)
    sz = malloc_size( (void*)memblock );
#else
    // No predictable function exists and
    // nothing in core opennurbs code uses
    // onmsize().  If you find a portable
    // way to support another compiler or 
    // platform, then report it to the support
    // contact on http://opennurbs.org and
    // the code will be added in the next release.
    ON_ERROR("onmsize not implemented on this compiler or platform.");
    sz = 0;
#endif
  }

  return sz;
}