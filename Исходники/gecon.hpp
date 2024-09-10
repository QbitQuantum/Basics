 static std::ptrdiff_t invoke( const char norm, const MatrixA& a,
         const real_type anorm, real_type& rcond, detail::workspace2< WORK,
         RWORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_rwork( bindings::size_column(a) ));
     BOOST_ASSERT( bindings::size(work.select(value_type())) >=
             min_size_work( bindings::size_column(a) ));
     BOOST_ASSERT( bindings::size_column(a) >= 0 );
     BOOST_ASSERT( bindings::size_minor(a) == 1 ||
             bindings::stride_minor(a) == 1 );
     BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
             bindings::size_column(a)) );
     BOOST_ASSERT( norm == '1' || norm == 'O' || norm == 'I' );
     return detail::gecon( norm, bindings::size_column(a),
             bindings::begin_value(a), bindings::stride_major(a), anorm,
             rcond, bindings::begin_value(work.select(value_type())),
             bindings::begin_value(work.select(real_type())) );
 }