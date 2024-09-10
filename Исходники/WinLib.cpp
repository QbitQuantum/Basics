refalrts::FnResult CoreP_MFileSystemP_GetFileAttributes(refalrts::Iter arg_begin, refalrts::Iter arg_end) {
  refalrts::Iter bb_0 = arg_begin;
  refalrts::Iter be_0 = arg_end;
  refalrts::move_left( bb_0, be_0 );
  refalrts::move_left( bb_0, be_0 );
  refalrts::move_right( bb_0, be_0 );
  refalrts::Iter eFileName_b_1;
  refalrts::Iter eFileName_e_1;
  // e.FileName
  eFileName_b_1 = bb_0;
  refalrts::use( eFileName_b_1 );
  eFileName_e_1 = be_0;
  refalrts::use( eFileName_e_1 );

  std::vector<char> filename;

  refalrts::FnResult res =
    string_from_seq(filename, eFileName_b_1, eFileName_e_1);

  if( res == refalrts::cRecognitionImpossible ) {
    return refalrts::cRecognitionImpossible;
  }

  WIN32_FIND_DATA find_file_data;

  HANDLE hFind = FindFirstFile( & filename[0], & find_file_data );

  if( hFind == INVALID_HANDLE_VALUE ) {
    refalrts::reset_allocator();
    refalrts::Iter res = arg_begin;

    refalrts::Iter nSF = 0;
    if( ! refalrts::alloc_ident( nSF, & FailsL_<int>::name ) )
      return refalrts::cNoMemory;

    res = refalrts::splice_elem( res, nSF );
    refalrts::use( res );
    refalrts::splice_to_freelist( arg_begin, arg_end );

    return refalrts::cSuccess;
  } else {
    std::string full_name( find_file_data.cFileName );

    if( ! get_full_name( full_name ) ) {
      refalrts::reset_allocator();
      refalrts::Iter res = arg_begin;
    
      refalrts::Iter nSF = 0;
      if( ! refalrts::alloc_ident( nSF, & FailsL_<int>::name ) )
        return refalrts::cNoMemory;
    
      res = refalrts::splice_elem( res, nSF );
      refalrts::use( res );
      refalrts::splice_to_freelist( arg_begin, arg_end );
    
      return refalrts::cSuccess;
    } else {
      bool is_directory =
        ((find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);

      SYSTEMTIME file_system_time = { 0 };

      FileTimeToSystemTime(
        & find_file_data.ftLastWriteTime, & file_system_time
      );

      refalrts::reset_allocator();
      refalrts::Iter res = arg_begin;
      refalrts::Iter nSF = 0;
      if( ! refalrts::alloc_ident( nSF, & SuccessL_<int>::name ) )
        return refalrts::cNoMemory;
      refalrts::Iter n0 = 0;
      if( ! refalrts::alloc_open_bracket( n0 ) )
        return refalrts::cNoMemory;
      refalrts::Iter n1 = 0;
      if( ! refalrts::alloc_ident( n1, & DateTimeL_<int>::name ) )
        return refalrts::cNoMemory;
      refalrts::Iter n2 = 0;
      if( ! refalrts::alloc_number( n2, file_system_time.wYear ) )
        return refalrts::cNoMemory;
      refalrts::Iter n3 = 0;
      if( ! refalrts::alloc_number( n3, file_system_time.wMonth ) )
        return refalrts::cNoMemory;
      refalrts::Iter n4 = 0;
      if( ! refalrts::alloc_number( n4, file_system_time.wDay ) )
        return refalrts::cNoMemory;
      refalrts::Iter n5 = 0;
      if( ! refalrts::alloc_number( n5, file_system_time.wHour ) )
        return refalrts::cNoMemory;
      refalrts::Iter n6 = 0;
      if( ! refalrts::alloc_number( n6, file_system_time.wMinute ) )
        return refalrts::cNoMemory;
      refalrts::Iter n7 = 0;
      if( ! refalrts::alloc_number( n7, file_system_time.wSecond ) )
        return refalrts::cNoMemory;
      refalrts::Iter n8 = 0;
      if( ! refalrts::alloc_number( n8, file_system_time.wMilliseconds ) )
        return refalrts::cNoMemory;
      refalrts::Iter n9 = 0;
      if( ! refalrts::alloc_close_bracket( n9 ) )
        return refalrts::cNoMemory;
      refalrts::Iter n10 = 0;
      if( ! refalrts::alloc_open_bracket( n10 ) )
        return refalrts::cNoMemory;
      refalrts::Iter n11 = 0;
      if( ! refalrts::alloc_ident( n11, & SizeL_<int>::name ) )
        return refalrts::cNoMemory;
      refalrts::Iter n12 = 0;

      if( is_directory ) {
        if( ! refalrts::alloc_ident( n12, & DirL_<int>::name ) )
          return refalrts::cNoMemory;
      } else {
        if( ! refalrts::alloc_number( n12, 1000UL ) )
          return refalrts::cNoMemory;
      }

      refalrts::Iter n14 = 0;
      if( ! refalrts::alloc_close_bracket( n14 ) )
        return refalrts::cNoMemory;
      refalrts::Iter n15 = 0;
      if( ! refalrts::alloc_open_bracket( n15 ) )
        return refalrts::cNoMemory;
      refalrts::Iter n16 = 0;
      if( ! refalrts::alloc_ident( n16, & LongNameL_<int>::name ) )
        return refalrts::cNoMemory;

      refalrts::Iter fullname_b = 0;
      refalrts::Iter fullname_e = 0;

      bool name_allocated =
        refalrts::alloc_string( fullname_b, fullname_e, full_name.c_str() );

      if( ! name_allocated )
        return refalrts::cNoMemory;

      refalrts::Iter n26 = 0;
      if( ! refalrts::alloc_close_bracket( n26 ) )
        return refalrts::cNoMemory;

      refalrts::link_brackets( n15, n26 );
      res = refalrts::splice_elem( res, n26 );
      res = refalrts::splice_evar( res, fullname_b, fullname_e );
      res = refalrts::splice_elem( res, n16 );
      res = refalrts::splice_elem( res, n15 );
      refalrts::link_brackets( n10, n14 );
      res = refalrts::splice_elem( res, n14 );
      res = refalrts::splice_elem( res, n12 );
      res = refalrts::splice_elem( res, n11 );
      res = refalrts::splice_elem( res, n10 );
      refalrts::link_brackets( n0, n9 );
      res = refalrts::splice_elem( res, n9 );
      res = refalrts::splice_elem( res, n8 );
      res = refalrts::splice_elem( res, n7 );
      res = refalrts::splice_elem( res, n6 );
      res = refalrts::splice_elem( res, n5 );
      res = refalrts::splice_elem( res, n4 );
      res = refalrts::splice_elem( res, n3 );
      res = refalrts::splice_elem( res, n2 );
      res = refalrts::splice_elem( res, n1 );
      res = refalrts::splice_elem( res, n0 );
      res = refalrts::splice_elem( res, nSF );
      refalrts::use( res );
      refalrts::splice_to_freelist( arg_begin, arg_end );
  
      return refalrts::cSuccess;
    }
  }
}