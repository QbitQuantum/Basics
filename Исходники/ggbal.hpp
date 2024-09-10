 static void invoke( char const job, integer_t const n, MatrixA& a,
         MatrixB& b, integer_t& ilo, integer_t& ihi, VectorLSCALE& lscale,
         VectorRSCALE& rscale, integer_t& info, detail::workspace1<
         WORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::matrix_traits<
             MatrixB >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::vector_traits<
             VectorLSCALE >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
             MatrixA >::value_type, typename traits::vector_traits<
             VectorRSCALE >::value_type >::value) );
     BOOST_ASSERT( job == 'N' || job == 'P' || job == 'S' || job == 'B' );
     BOOST_ASSERT( n >= 0 );
     BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,n) );
     BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,n) );
     BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
             min_size_work( $CALL_MIN_SIZE ));
     detail::ggbal( job, n, traits::matrix_storage(a),
             traits::leading_dimension(a), traits::matrix_storage(b),
             traits::leading_dimension(b), ilo, ihi,
             traits::vector_storage(lscale),
             traits::vector_storage(rscale),
             traits::vector_storage(work.select(real_type())), info );
 }