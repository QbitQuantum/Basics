 static void invoke( char const uplo, VectorAP& ap, VectorTAU& tau,
         MatrixQ& q, integer_t& info, detail::workspace1< WORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
             VectorAP >::value_type, typename traits::vector_traits<
             VectorTAU >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
             VectorAP >::value_type, typename traits::matrix_traits<
             MatrixQ >::value_type >::value) );
     BOOST_ASSERT( uplo == 'U' || uplo == 'L' );
     BOOST_ASSERT( traits::matrix_num_columns(q) >= 0 );
     BOOST_ASSERT( traits::vector_size(ap) >=
             traits::matrix_num_columns(q)*(traits::matrix_num_columns(q)+
             1)/2 );
     BOOST_ASSERT( traits::vector_size(tau) >=
             traits::matrix_num_columns(q)-1 );
     BOOST_ASSERT( traits::leading_dimension(q) >= std::max(1,
             traits::matrix_num_columns(q)) );
     BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
             min_size_work( traits::matrix_num_columns(q) ));
     detail::upgtr( uplo, traits::matrix_num_columns(q),
             traits::vector_storage(ap), traits::vector_storage(tau),
             traits::matrix_storage(q), traits::leading_dimension(q),
             traits::vector_storage(work.select(value_type())), info );
 }