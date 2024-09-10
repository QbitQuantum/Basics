 static void invoke( char const jobz, MatrixA& a, VectorW& w,
         integer_t& info, detail::workspace2< WORK, IWORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::vector_traits<
             VectorW >::value_type >::value) );
     BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
     BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
             traits::matrix_uplo_tag(a) == 'L' );
     BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
     BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
             traits::matrix_num_columns(a)) );
     BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
             min_size_work( jobz, traits::matrix_num_columns(a) ));
     BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
             min_size_iwork( jobz, traits::matrix_num_columns(a) ));
     detail::syevd( jobz, traits::matrix_uplo_tag(a),
             traits::matrix_num_columns(a), traits::matrix_storage(a),
             traits::leading_dimension(a), traits::vector_storage(w),
             traits::vector_storage(work.select(real_type())),
             traits::vector_size(work.select(real_type())),
             traits::vector_storage(work.select(integer_t())),
             traits::vector_size(work.select(integer_t())), info );
 }