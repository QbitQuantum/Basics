 static std::ptrdiff_t invoke( const Side side, const char uplo,
         const VectorAP& ap, const VectorTAU& tau, MatrixC& c,
         detail::workspace1< WORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     typedef tag::column_major order;
     typedef typename result_of::trans_tag< VectorAP, order >::type trans;
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixC >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorAP >::type >::type,
             typename remove_const< typename bindings::value_type<
             VectorTAU >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorAP >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixC >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixC >::value) );
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_work( side, bindings::size_row(c),
             bindings::size_column(c) ));
     BOOST_ASSERT( bindings::size_column(c) >= 0 );
     BOOST_ASSERT( bindings::size_minor(c) == 1 ||
             bindings::stride_minor(c) == 1 );
     BOOST_ASSERT( bindings::size_row(c) >= 0 );
     BOOST_ASSERT( bindings::stride_major(c) >= std::max< std::ptrdiff_t >(1,
             bindings::size_row(c)) );
     return detail::opmtr( side, uplo, trans(), bindings::size_row(c),
             bindings::size_column(c), bindings::begin_value(ap),
             bindings::begin_value(tau), bindings::begin_value(c),
             bindings::stride_major(c),
             bindings::begin_value(work.select(real_type())) );
 }