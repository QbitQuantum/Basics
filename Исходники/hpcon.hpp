 static std::ptrdiff_t invoke( const MatrixAP& ap, const VectorIPIV& ipiv,
         const real_type anorm, real_type& rcond, detail::workspace2< WORK,
         IWORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     typedef typename result_of::uplo_tag< MatrixAP >::type uplo;
     BOOST_ASSERT( bindings::size(ipiv) >= bindings::size_column(ap) );
     BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
             min_size_iwork( bindings::size_column(ap) ));
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_work( bindings::size_column(ap) ));
     BOOST_ASSERT( bindings::size_column(ap) >= 0 );
     return detail::hpcon( uplo(), bindings::size_column(ap),
             bindings::begin_value(ap), bindings::begin_value(ipiv), anorm,
             rcond, bindings::begin_value(work.select(real_type())),
             bindings::begin_value(work.select(fortran_int_t())) );
 }