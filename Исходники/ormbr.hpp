 static void invoke( char const vect, char const side, char const trans,
         integer_t const k, MatrixA& a, VectorTAU& tau, MatrixC& c,
         integer_t& info, detail::workspace1< WORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::vector_traits<
             VectorTAU >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::matrix_traits<
             MatrixC >::value_type >::value) );
     BOOST_ASSERT( vect == 'Q' || vect == 'P' );
     BOOST_ASSERT( side == 'L' || side == 'R' );
     BOOST_ASSERT( trans == 'N' || trans == 'T' );
     BOOST_ASSERT( traits::matrix_num_rows(c) >= 0 );
     BOOST_ASSERT( traits::matrix_num_columns(c) >= 0 );
     BOOST_ASSERT( k >= 0 );
     BOOST_ASSERT( traits::vector_size(tau) >= std::min(?NQ,k) );
     BOOST_ASSERT( traits::leading_dimension(c) >= std::max(1,
             traits::matrix_num_rows(c)) );
     BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
             min_size_work( side, traits::matrix_num_rows(c),
             traits::matrix_num_columns(c) ));
     detail::ormbr( vect, side, trans, traits::matrix_num_rows(c),
             traits::matrix_num_columns(c), k, traits::matrix_storage(a),
             traits::leading_dimension(a), traits::vector_storage(tau),
             traits::matrix_storage(c), traits::leading_dimension(c),
             traits::vector_storage(work.select(real_type())),
             traits::vector_size(work.select(real_type())), info );
 }