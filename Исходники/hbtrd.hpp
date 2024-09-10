 static void invoke( char const vect, integer_t const n,
         integer_t const kd, MatrixAB& ab, VectorD& d, VectorE& e,
         MatrixQ& q, integer_t& info, detail::workspace1< WORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
             VectorD >::value_type, typename traits::vector_traits<
             VectorE >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixAB >::value_type, typename traits::matrix_traits<
             MatrixQ >::value_type >::value) );
     BOOST_ASSERT( vect == 'N' || vect == 'V' || vect == 'U' );
     BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
             traits::matrix_uplo_tag(a) == 'L' );
     BOOST_ASSERT( n >= 0 );
     BOOST_ASSERT( kd >= 0 );
     BOOST_ASSERT( traits::leading_dimension(ab) >= kd+1 );
     BOOST_ASSERT( traits::vector_size(d) >= n );
     BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
             min_size_work( n ));
     detail::hbtrd( vect, traits::matrix_uplo_tag(a), n, kd,
             traits::matrix_storage(ab), traits::leading_dimension(ab),
             traits::vector_storage(d), traits::vector_storage(e),
             traits::matrix_storage(q), traits::leading_dimension(q),
             traits::vector_storage(work.select(value_type())), info );
 }