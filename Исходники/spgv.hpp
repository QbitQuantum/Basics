 static void invoke( integer_t const itype, char const jobz,
                     integer_t const n, MatrixAP& ap, MatrixBP& bp, VectorW& w,
                     MatrixZ& z, integer_t& info, detail::workspace1< WORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                           MatrixAP >::value_type, typename traits::matrix_traits<
                           MatrixBP >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                           MatrixAP >::value_type, typename traits::vector_traits<
                           VectorW >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                           MatrixAP >::value_type, typename traits::matrix_traits<
                           MatrixZ >::value_type >::value) );
     BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
     BOOST_ASSERT( traits::matrix_uplo_tag(ap) == 'U' ||
                   traits::matrix_uplo_tag(ap) == 'L' );
     BOOST_ASSERT( n >= 0 );
     BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                   min_size_work( n ));
     detail::spgv( itype, jobz, traits::matrix_uplo_tag(ap), n,
                   traits::matrix_storage(ap), traits::matrix_storage(bp),
                   traits::vector_storage(w), traits::matrix_storage(z),
                   traits::leading_dimension(z),
                   traits::vector_storage(work.select(real_type())), info );
 }