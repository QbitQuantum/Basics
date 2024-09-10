 static std::ptrdiff_t invoke( const VectorD& d, const VectorE& e,
         const real_type anorm, real_type& rcond, detail::workspace1<
         WORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorD >::type >::type,
             typename remove_const< typename bindings::value_type<
             VectorE >::type >::type >::value) );
     BOOST_ASSERT( bindings::size(d) >= bindings::size(d) );
     BOOST_ASSERT( bindings::size(d) >= 0 );
     BOOST_ASSERT( bindings::size(e) >= bindings::size(d)-1 );
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_work( bindings::size(d) ));
     return detail::ptcon( bindings::size(d), bindings::begin_value(d),
             bindings::begin_value(e), anorm, rcond,
             bindings::begin_value(work.select(real_type())) );
 }