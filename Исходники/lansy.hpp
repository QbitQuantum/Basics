 static std::ptrdiff_t invoke( const char norm, const MatrixA& a,
         detail::workspace1< WORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     typedef typename result_of::uplo_tag< MatrixA >::type uplo;
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_work( norm, bindings::size_column(a) ));
     BOOST_ASSERT( bindings::size_column(a) >= 0 );
     BOOST_ASSERT( bindings::size_minor(a) == 1 ||
             bindings::stride_minor(a) == 1 );
     BOOST_ASSERT( bindings::stride_major(a) >= std::max<
             std::ptrdiff_t >(bindings::size_column(a),1) );
     return detail::lansy( norm, uplo(), bindings::size_column(a),
             bindings::begin_value(a), bindings::stride_major(a),
             bindings::begin_value(work.select(real_type())) );
 }