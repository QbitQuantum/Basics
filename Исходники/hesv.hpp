 static std::ptrdiff_t invoke( MatrixA& a, VectorIPIV& ipiv, MatrixB& b,
         detail::workspace1< WORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     typedef typename result_of::uplo_tag< MatrixA >::type uplo;
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixB >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< MatrixA >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixB >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorIPIV >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixB >::value) );
     BOOST_ASSERT( bindings::size(work.select(value_type())) >=
             min_size_work());
     BOOST_ASSERT( bindings::size_column(a) >= 0 );
     BOOST_ASSERT( bindings::size_column(b) >= 0 );
     BOOST_ASSERT( bindings::size_minor(a) == 1 ||
             bindings::stride_minor(a) == 1 );
     BOOST_ASSERT( bindings::size_minor(b) == 1 ||
             bindings::stride_minor(b) == 1 );
     BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
             bindings::size_column(a)) );
     BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
             bindings::size_column(a)) );
     return detail::hesv( uplo(), bindings::size_column(a),
             bindings::size_column(b), bindings::begin_value(a),
             bindings::stride_major(a), bindings::begin_value(ipiv),
             bindings::begin_value(b), bindings::stride_major(b),
             bindings::begin_value(work.select(value_type())),
             bindings::size(work.select(value_type())) );
 }