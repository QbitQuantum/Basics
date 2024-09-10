 static void invoke( MatrixA& a, VectorD& d, VectorE& e, VectorTAUQ& tauq,
         VectorTAUP& taup, integer_t& info, detail::workspace1<
         WORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::vector_traits<
             VectorD >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::vector_traits<
             VectorE >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::vector_traits<
             VectorTAUQ >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::vector_traits<
             VectorTAUP >::value_type >::value) );
     BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
     BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
     BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
             traits::matrix_num_rows(a)) );
     BOOST_ASSERT( traits::vector_size(d) >=
             std::min(traits::matrix_num_rows(a),
             traits::matrix_num_columns(a)) );
     BOOST_ASSERT( traits::vector_size(tauq) >=
             std::min(traits::matrix_num_rows(a),
             traits::matrix_num_columns(a)) );
     BOOST_ASSERT( traits::vector_size(taup) >=
             std::min(traits::matrix_num_rows(a),
             traits::matrix_num_columns(a)) );
     BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
             min_size_work( traits::matrix_num_rows(a),
             traits::matrix_num_columns(a) ));
     detail::gebrd( traits::matrix_num_rows(a),
             traits::matrix_num_columns(a), traits::matrix_storage(a),
             traits::leading_dimension(a), traits::vector_storage(d),
             traits::vector_storage(e), traits::vector_storage(tauq),
             traits::vector_storage(taup),
             traits::vector_storage(work.select(real_type())),
             traits::vector_size(work.select(real_type())), info );
 }