 static void invoke( MatrixA& a, VectorD& d, VectorE& e, VectorTAU& tau,
         integer_t& info, detail::workspace1< WORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
             VectorD >::value_type, typename traits::vector_traits<
             VectorE >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::vector_traits<
             VectorTAU >::value_type >::value) );
     BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
             traits::matrix_uplo_tag(a) == 'L' );
     BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
     BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
             traits::matrix_num_columns(a)) );
     BOOST_ASSERT( traits::vector_size(d) >=
             traits::matrix_num_columns(a) );
     BOOST_ASSERT( traits::vector_size(tau) >=
             traits::matrix_num_columns(a)-1 );
     BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
             min_size_work(  ));
     detail::hetrd( traits::matrix_uplo_tag(a),
             traits::matrix_num_columns(a), traits::matrix_storage(a),
             traits::leading_dimension(a), traits::vector_storage(d),
             traits::vector_storage(e), traits::vector_storage(tau),
             traits::vector_storage(work.select(value_type())),
             traits::vector_size(work.select(value_type())), info );
 }