 static void invoke( MatrixA& a, VectorIPIV& ipiv, integer_t& info,
         detail::workspace1< WORK > work ) {
     BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
             traits::matrix_uplo_tag(a) == 'L' );
     BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
     BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
             traits::matrix_num_columns(a)) );
     BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
             min_size_work( $CALL_MIN_SIZE ));
     detail::sytrf( traits::matrix_uplo_tag(a),
             traits::matrix_num_columns(a), traits::matrix_storage(a),
             traits::leading_dimension(a), traits::vector_storage(ipiv),
             traits::vector_storage(work.select(real_type())),
             traits::vector_size(work.select(real_type())), info );
 }