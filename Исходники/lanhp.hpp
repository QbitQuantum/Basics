 static std::ptrdiff_t invoke( const char norm, const MatrixAP& ap,
         detail::workspace1< WORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     typedef typename result_of::uplo_tag< MatrixAP >::type uplo;
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_work( norm, bindings::size_column(ap) ));
     BOOST_ASSERT( bindings::size_column(ap) >= 0 );
     return detail::lanhp( norm, uplo(), bindings::size_column(ap),
             bindings::begin_value(ap),
             bindings::begin_value(work.select(real_type())) );
 }