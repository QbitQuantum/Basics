 static std::ptrdiff_t invoke( const char uplo, const char compq,
         const fortran_int_t n, VectorD& d, VectorE& e, MatrixU& u,
         MatrixVT& vt, VectorQ& q, VectorIQ& iq, detail::workspace2< WORK,
         IWORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixU >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixVT >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorD >::type >::type,
             typename remove_const< typename bindings::value_type<
             VectorE >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorD >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixU >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorD >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixVT >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorD >::type >::type,
             typename remove_const< typename bindings::value_type<
             VectorQ >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorD >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorE >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixU >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVT >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorQ >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorIQ >::value) );
     BOOST_ASSERT( bindings::size(e) >= n-1 );
     BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
             min_size_iwork( n ));
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_work( compq, n ));
     BOOST_ASSERT( bindings::size_minor(u) == 1 ||
             bindings::stride_minor(u) == 1 );
     BOOST_ASSERT( bindings::size_minor(vt) == 1 ||
             bindings::stride_minor(vt) == 1 );
     BOOST_ASSERT( compq == 'N' || compq == 'P' || compq == 'I' );
     BOOST_ASSERT( n >= 0 );
     return detail::bdsdc( uplo, compq, n, bindings::begin_value(d),
             bindings::begin_value(e), bindings::begin_value(u),
             bindings::stride_major(u), bindings::begin_value(vt),
             bindings::stride_major(vt), bindings::begin_value(q),
             bindings::begin_value(iq),
             bindings::begin_value(work.select(real_type())),
             bindings::begin_value(work.select(fortran_int_t())) );
 }