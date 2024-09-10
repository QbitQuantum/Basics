 static void invoke( char const compz, integer_t const n, VectorD& d,
         VectorE& e, MatrixZ& z, integer_t& info, detail::workspace2< WORK,
         IWORK > work ) {
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
             VectorD >::value_type, typename traits::vector_traits<
             VectorE >::value_type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
             VectorD >::value_type, typename traits::matrix_traits<
             MatrixZ >::value_type >::value) );
     BOOST_ASSERT( compz == 'N' || compz == 'I' || compz == 'V' );
     BOOST_ASSERT( n >= 0 );
     BOOST_ASSERT( traits::vector_size(e) >= n-1 );
     BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
             min_size_work( $CALL_MIN_SIZE ));
     BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
             min_size_iwork( compz, n ));
     detail::stedc( compz, n, traits::vector_storage(d),
             traits::vector_storage(e), traits::matrix_storage(z),
             traits::leading_dimension(z),
             traits::vector_storage(work.select(real_type())),
             traits::vector_size(work.select(real_type())),
             traits::vector_storage(work.select(integer_t())),
             traits::vector_size(work.select(integer_t())), info );
 }