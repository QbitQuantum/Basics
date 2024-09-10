 static std::ptrdiff_t invoke( const char jobz, const fortran_int_t n,
         VectorD& d, VectorE& e, MatrixZ& z, detail::workspace2< WORK,
         IWORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixZ >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorD >::type >::type,
             typename remove_const< typename bindings::value_type<
             VectorE >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorD >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixZ >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorD >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorE >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixZ >::value) );
     BOOST_ASSERT( bindings::size(e) >= n-1 );
     BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
             min_size_iwork( jobz, n ));
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_work( jobz, n ));
     BOOST_ASSERT( bindings::size_minor(z) == 1 ||
             bindings::stride_minor(z) == 1 );
     BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
     BOOST_ASSERT( n >= 0 );
     return detail::stevd( jobz, n, bindings::begin_value(d),
             bindings::begin_value(e), bindings::begin_value(z),
             bindings::stride_major(z),
             bindings::begin_value(work.select(real_type())),
             bindings::size(work.select(real_type())),
             bindings::begin_value(work.select(fortran_int_t())),
             bindings::size(work.select(fortran_int_t())) );
 }