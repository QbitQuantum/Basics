 static std::ptrdiff_t invoke( const fortran_int_t n,
                               const fortran_int_t ilo, const fortran_int_t ihi,
                               MatrixA& a, const VectorTAU& tau, detail::workspace1<
                               WORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                           typename bindings::value_type< MatrixA >::type >::type,
                           typename remove_const< typename bindings::value_type<
                           VectorTAU >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
     BOOST_ASSERT( bindings::size(tau) >= n-1 );
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                   min_size_work( ihi, ilo ));
     BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                   bindings::stride_minor(a) == 1 );
     BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                   n) );
     BOOST_ASSERT( n >= 0 );
     return detail::orghr( n, ilo, ihi, bindings::begin_value(a),
                           bindings::stride_major(a), bindings::begin_value(tau),
                           bindings::begin_value(work.select(real_type())),
                           bindings::size(work.select(real_type())) );
 }