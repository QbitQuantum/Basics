 static void invoke( char const fact, MatrixA& a, MatrixAF& af,
         char& equed, VectorS& s, MatrixB& b, MatrixX& x, real_type& rcond,
         VectorFERR& ferr, VectorBERR& berr, integer_t& info,
         detail::workspace2< WORK, IWORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::matrix_traits<
             MatrixAF >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::vector_traits<
             VectorS >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::matrix_traits<
             MatrixB >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::matrix_traits<
             MatrixX >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::vector_traits<
             VectorFERR >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::vector_traits<
             VectorBERR >::value_type >::value) );
     BOOST_ASSERT( fact == 'F' || fact == 'Y' || fact == 'N' ||
             fact == 'E' );
     BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
             traits::matrix_uplo_tag(a) == 'L' );
     BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
     BOOST_ASSERT( traits::matrix_num_columns(x) >= 0 );
     BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
             traits::matrix_num_columns(a)) );
     BOOST_ASSERT( traits::leading_dimension(af) >= std::max(1,
             traits::matrix_num_columns(a)) );
     BOOST_ASSERT( equed == 'N' || equed == 'Y' );
     BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,
             traits::matrix_num_columns(a)) );
     BOOST_ASSERT( traits::leading_dimension(x) >= std::max(1,
             traits::matrix_num_columns(a)) );
     BOOST_ASSERT( traits::vector_size(berr) >=
             traits::matrix_num_columns(x) );
     BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
             min_size_work( traits::matrix_num_columns(a) ));
     BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
             min_size_iwork( traits::matrix_num_columns(a) ));
     detail::posvx( fact, traits::matrix_uplo_tag(a),
             traits::matrix_num_columns(a), traits::matrix_num_columns(x),
             traits::matrix_storage(a), traits::leading_dimension(a),
             traits::matrix_storage(af), traits::leading_dimension(af),
             equed, traits::vector_storage(s), traits::matrix_storage(b),
             traits::leading_dimension(b), traits::matrix_storage(x),
             traits::leading_dimension(x), rcond,
             traits::vector_storage(ferr), traits::vector_storage(berr),
             traits::vector_storage(work.select(real_type())),
             traits::vector_storage(work.select(integer_t())), info );
 }