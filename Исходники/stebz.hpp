 static std::ptrdiff_t invoke( const char range, const char order,
         const fortran_int_t n, const real_type vl, const real_type vu,
         const fortran_int_t il, const fortran_int_t iu,
         const real_type abstol, const VectorD& d, const VectorE& e,
         fortran_int_t& m, fortran_int_t& nsplit, VectorW& w,
         VectorIBLOCK& iblock, VectorISPLIT& isplit, detail::workspace2<
         WORK, IWORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorD >::type >::type,
             typename remove_const< typename bindings::value_type<
             VectorE >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorD >::type >::type,
             typename remove_const< typename bindings::value_type<
             VectorW >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorIBLOCK >::type >::type,
             typename remove_const< typename bindings::value_type<
             VectorISPLIT >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorW >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorIBLOCK >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorISPLIT >::value) );
     BOOST_ASSERT( bindings::size(d) >= n );
     BOOST_ASSERT( bindings::size(e) >= n-1 );
     BOOST_ASSERT( bindings::size(isplit) >= n );
     BOOST_ASSERT( bindings::size(w) >= n );
     BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
             min_size_iwork( n ));
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_work( n ));
     BOOST_ASSERT( n >= 0 );
     BOOST_ASSERT( order == 'B' || order == 'E' );
     BOOST_ASSERT( range == 'A' || range == 'V' || range == 'I' );
     return detail::stebz( range, order, n, vl, vu, il, iu, abstol,
             bindings::begin_value(d), bindings::begin_value(e), m, nsplit,
             bindings::begin_value(w), bindings::begin_value(iblock),
             bindings::begin_value(isplit),
             bindings::begin_value(work.select(real_type())),
             bindings::begin_value(work.select(fortran_int_t())) );
 }