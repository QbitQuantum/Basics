 static void invoke( char const vect, integer_t const m, integer_t const n,
         integer_t const k, MatrixA& a, VectorTAU& tau, integer_t& info,
         detail::workspace1< WORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::vector_traits<
             VectorTAU >::value_type >::value) );
     BOOST_ASSERT( vect == 'Q' || vect == 'P' );
     BOOST_ASSERT( m >= 0 );
     BOOST_ASSERT( k >= 0 );
     BOOST_ASSERT( traits::leading_dimension(a) >= m );
     BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
             min_size_work( m, n ));
     detail::ungbr( vect, m, n, k, traits::matrix_storage(a),
             traits::leading_dimension(a), traits::vector_storage(tau),
             traits::vector_storage(work.select(value_type())),
             traits::vector_size(work.select(value_type())), info );
 }