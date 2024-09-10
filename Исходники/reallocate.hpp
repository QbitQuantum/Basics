  //============================================================================
  inline byte* reallocate ( byte* ptr
                          , std::size_t nbytes
                          , std::size_t obytes
                          , std::size_t align
                          )
  {
    byte* result(ptr);

    if( (obytes < nbytes) || !is_aligned(ptr,align) )
    {
      #if defined(BOOST_MSVC)
      //========================================================================
      // MSVC systems use _aligned_realloc
      //========================================================================
      if( !(  result
           =  reinterpret_cast<byte*>(_aligned_realloc(ptr, nbytes, align))
           )
        )
      {
        BOOST_THROW_EXCEPTION( std::bad_alloc() );
        result = 0;
      }
      #else
      //========================================================================
      // Other systems allocate/copy/deallocate
      //========================================================================
      byte* tmp = allocate(nbytes, align);
      std::memcpy(tmp,ptr,obytes);
      deallocate(ptr,obytes,align);
      result = tmp;
      #endif
    }

    return result;
  }