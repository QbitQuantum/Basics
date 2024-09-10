 static void invoke( integer_t const n, MatrixAP& ap, MatrixAFP& afp,
         VectorIPIV& ipiv, MatrixB& b, MatrixX& x, VectorFERR& ferr,
         VectorBERR& berr, integer_t& info, detail::workspace2< WORK,
         IWORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixAP >::value_type, typename traits::matrix_traits<
             MatrixAFP >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixAP >::value_type, typename traits::matrix_traits<
             MatrixB >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixAP >::value_type, typename traits::matrix_traits<
             MatrixX >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixAP >::value_type, typename traits::vector_traits<
             VectorFERR >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixAP >::value_type, typename traits::vector_traits<
             VectorBERR >::value_type >::value) );
     BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
             traits::matrix_uplo_tag(a) == 'L' );
     BOOST_ASSERT( n >= 0 );
     BOOST_ASSERT( traits::matrix_num_columns(x) >= 0 );
     BOOST_ASSERT( traits::vector_size(afp) >= n*(n+1)/2 );
     BOOST_ASSERT( traits::vector_size(ipiv) >= n );
     BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,n) );
     BOOST_ASSERT( traits::leading_dimension(x) >= std::max(1,n) );
     BOOST_ASSERT( traits::vector_size(berr) >=
             traits::matrix_num_columns(x) );
     BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
             min_size_work( n ));
     BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
             min_size_iwork( n ));
     detail::sprfs( traits::matrix_uplo_tag(a), n,
             traits::matrix_num_columns(x), traits::matrix_storage(ap),
             traits::matrix_storage(afp), traits::vector_storage(ipiv),
             traits::matrix_storage(b), traits::leading_dimension(b),
             traits::matrix_storage(x), traits::leading_dimension(x),
             traits::vector_storage(ferr), traits::vector_storage(berr),
             traits::vector_storage(work.select(real_type())),
             traits::vector_storage(work.select(integer_t())), info );
 }