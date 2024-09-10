 static void invoke( char const jobz, integer_t const n,
         integer_t const kd, MatrixAB& ab, VectorW& w, MatrixZ& z,
         integer_t& info, detail::workspace1< WORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixAB >::value_type, typename traits::vector_traits<
             VectorW >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixAB >::value_type, typename traits::matrix_traits<
             MatrixZ >::value_type >::value) );
     BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
     BOOST_ASSERT( traits::matrix_uplo_tag(ab) == 'U' ||
             traits::matrix_uplo_tag(ab) == 'L' );
     BOOST_ASSERT( n >= 0 );
     BOOST_ASSERT( kd >= 0 );
     BOOST_ASSERT( traits::leading_dimension(ab) >= kd );
     BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
             min_size_work( n ));
     detail::sbev( jobz, traits::matrix_uplo_tag(ab), n, kd,
             traits::matrix_storage(ab), traits::leading_dimension(ab),
             traits::vector_storage(w), traits::matrix_storage(z),
             traits::leading_dimension(z),
             traits::vector_storage(work.select(real_type())), info );
 }