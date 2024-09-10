 static std::ptrdiff_t invoke( const char norm, const MatrixAB& ab,
         detail::workspace1< WORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixAB >::value) );
     BOOST_ASSERT( bindings::bandwidth_lower(ab) >= 0 );
     BOOST_ASSERT( bindings::bandwidth_upper(ab) >= 0 );
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_work( norm, bindings::size_column(ab) ));
     BOOST_ASSERT( bindings::size_column(ab) >= 0 );
     BOOST_ASSERT( bindings::size_minor(ab) == 1 ||
             bindings::stride_minor(ab) == 1 );
     BOOST_ASSERT( bindings::stride_major(ab) >=
             bindings::bandwidth_lower(ab)+bindings::bandwidth_upper(ab)+
             1 );
     return detail::langb( norm, bindings::size_column(ab),
             bindings::bandwidth_lower(ab), bindings::bandwidth_upper(ab),
             bindings::begin_value(ab), bindings::stride_major(ab),
             bindings::begin_value(work.select(real_type())) );
 }