 static void invoke( MatrixA& a, VectorTAU& tau, integer_t& info,
         detail::workspace1< WORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::vector_traits<
             VectorTAU >::value_type >::value) );
     BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
     BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
     BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
             traits::matrix_num_rows(a)) );
     BOOST_ASSERT( traits::vector_size(tau) >=
             std::min(traits::matrix_num_rows(a),
             traits::matrix_num_columns(a)) );
     BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
             min_size_work( $CALL_MIN_SIZE ));
     detail::geqrf( traits::matrix_num_rows(a),
             traits::matrix_num_columns(a), traits::matrix_storage(a),
             traits::leading_dimension(a), traits::vector_storage(tau),
             traits::vector_storage(work.select(real_type())),
             traits::vector_size(work.select(real_type())), info );
 }