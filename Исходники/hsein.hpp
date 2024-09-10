 static std::ptrdiff_t invoke( const Side side, const char eigsrc,
         const char initv, const VectorSELECT& select, const MatrixH& h,
         VectorW& w, MatrixVL& vl, MatrixVR& vr,
         const fortran_int_t mm, fortran_int_t& m,
         VectorIFAILL& ifaill, VectorIFAILR& ifailr, detail::workspace2<
         WORK, RWORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixH >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixVL >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixVR >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorIFAILL >::type >::type,
             typename remove_const< typename bindings::value_type<
             VectorIFAILR >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< MatrixH >::type >::type,
             typename remove_const< typename bindings::value_type<
             VectorW >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< MatrixH >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixVL >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< MatrixH >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixVR >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorW >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVL >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVR >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorIFAILL >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorIFAILR >::value) );
     BOOST_ASSERT( bindings::size(select) >= bindings::size_column(h) );
     BOOST_ASSERT( bindings::size(w) >= bindings::size_column(h) );
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_rwork( bindings::size_column(h) ));
     BOOST_ASSERT( bindings::size(work.select(value_type())) >=
             min_size_work( bindings::size_column(h) ));
     BOOST_ASSERT( bindings::size_column(h) >= 0 );
     BOOST_ASSERT( bindings::size_minor(h) == 1 ||
             bindings::stride_minor(h) == 1 );
     BOOST_ASSERT( bindings::size_minor(vl) == 1 ||
             bindings::stride_minor(vl) == 1 );
     BOOST_ASSERT( bindings::size_minor(vr) == 1 ||
             bindings::stride_minor(vr) == 1 );
     BOOST_ASSERT( bindings::stride_major(h) >= std::max< std::ptrdiff_t >(1,
             bindings::size_column(h)) );
     BOOST_ASSERT( eigsrc == 'Q' || eigsrc == 'N' );
     BOOST_ASSERT( initv == 'N' || initv == 'U' );
     return detail::hsein( side, eigsrc, initv,
             bindings::begin_value(select), bindings::size_column(h),
             bindings::begin_value(h), bindings::stride_major(h),
             bindings::begin_value(w), bindings::begin_value(vl),
             bindings::stride_major(vl), bindings::begin_value(vr),
             bindings::stride_major(vr), mm, m,
             bindings::begin_value(work.select(value_type())),
             bindings::begin_value(work.select(real_type())),
             bindings::begin_value(ifaill), bindings::begin_value(ifailr) );
 }