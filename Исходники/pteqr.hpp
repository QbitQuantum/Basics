 static std::ptrdiff_t invoke( const char compz, VectorD& d, VectorE& e,
         MatrixZ& z, detail::workspace1< WORK > work ) {
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
     BOOST_ASSERT( bindings::size(d) >= bindings::size(d) );
     BOOST_ASSERT( bindings::size(d) >= 0 );
     BOOST_ASSERT( bindings::size(e) >= bindings::size(d)-1 );
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_work( bindings::size(d) ));
     BOOST_ASSERT( bindings::size_minor(z) == 1 ||
             bindings::stride_minor(z) == 1 );
     BOOST_ASSERT( compz == 'N' || compz == 'V' || compz == 'I' );
     return detail::pteqr( compz, bindings::size(d),
             bindings::begin_value(d), bindings::begin_value(e),
             bindings::begin_value(z), bindings::stride_major(z),
             bindings::begin_value(work.select(real_type())) );
 }