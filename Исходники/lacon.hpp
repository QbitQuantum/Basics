 static std::ptrdiff_t invoke( const fortran_int_t n, VectorX& x,
         real_type& est, fortran_int_t& kase, detail::workspace2< V,
         ISGN > work ) {
     namespace bindings = ::boost::numeric::bindings;
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorX >::value) );
     BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
             min_size_isgn( n ));
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_v( n ));
     BOOST_ASSERT( n >= 1 );
     return detail::lacon( n,
             bindings::begin_value(work.select(real_type())),
             bindings::begin_value(x),
             bindings::begin_value(work.select(fortran_int_t())), est,
             kase );
 }