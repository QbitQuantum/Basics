 static std::ptrdiff_t invoke( const char jobz, const char range,
         MatrixAP& ap, const real_type vl, const real_type vu,
         const fortran_int_t il, const fortran_int_t iu,
         const real_type abstol, fortran_int_t& m, VectorW& w,
         MatrixZ& z, VectorIFAIL& ifail, detail::workspace2< WORK,
         IWORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     typedef typename result_of::uplo_tag< MatrixAP >::type uplo;
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixZ >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< MatrixAP >::type >::type,
             typename remove_const< typename bindings::value_type<
             VectorW >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< MatrixAP >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixZ >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixAP >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorW >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixZ >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorIFAIL >::value) );
     BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
             min_size_iwork( bindings::size_column(ap) ));
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_work( bindings::size_column(ap) ));
     BOOST_ASSERT( bindings::size_column(ap) >= 0 );
     BOOST_ASSERT( bindings::size_minor(z) == 1 ||
             bindings::stride_minor(z) == 1 );
     BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
     BOOST_ASSERT( range == 'A' || range == 'V' || range == 'I' );
     return detail::spevx( jobz, range, uplo(), bindings::size_column(ap),
             bindings::begin_value(ap), vl, vu, il, iu, abstol, m,
             bindings::begin_value(w), bindings::begin_value(z),
             bindings::stride_major(z),
             bindings::begin_value(work.select(real_type())),
             bindings::begin_value(work.select(fortran_int_t())),
             bindings::begin_value(ifail) );
 }