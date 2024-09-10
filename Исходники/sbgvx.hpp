 static void invoke( char const jobz, char const range, integer_t const n,
         integer_t const ka, integer_t const kb, MatrixAB& ab,
         MatrixBB& bb, MatrixQ& q, real_type const vl, real_type const vu,
         integer_t const il, integer_t const iu, real_type const abstol,
         integer_t& m, VectorW& w, MatrixZ& z, VectorIFAIL& ifail,
         integer_t& info, detail::workspace2< WORK, IWORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixAB >::value_type, typename traits::matrix_traits<
             MatrixBB >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixAB >::value_type, typename traits::matrix_traits<
             MatrixQ >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixAB >::value_type, typename traits::vector_traits<
             VectorW >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixAB >::value_type, typename traits::matrix_traits<
             MatrixZ >::value_type >::value) );
     BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
     BOOST_ASSERT( range == 'A' || range == 'V' || range == 'I' );
     BOOST_ASSERT( traits::matrix_uplo_tag(ab) == 'U' ||
             traits::matrix_uplo_tag(ab) == 'L' );
     BOOST_ASSERT( n >= 0 );
     BOOST_ASSERT( ka >= 0 );
     BOOST_ASSERT( kb >= 0 );
     BOOST_ASSERT( traits::leading_dimension(ab) >= ka+1 );
     BOOST_ASSERT( traits::leading_dimension(bb) >= kb+1 );
     BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
             min_size_work( n ));
     BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
             min_size_iwork( n ));
     detail::sbgvx( jobz, range, traits::matrix_uplo_tag(ab), n, ka, kb,
             traits::matrix_storage(ab), traits::leading_dimension(ab),
             traits::matrix_storage(bb), traits::leading_dimension(bb),
             traits::matrix_storage(q), traits::leading_dimension(q), vl,
             vu, il, iu, abstol, m, traits::vector_storage(w),
             traits::matrix_storage(z), traits::leading_dimension(z),
             traits::vector_storage(work.select(real_type())),
             traits::vector_storage(work.select(integer_t())),
             traits::vector_storage(ifail), info );
 }