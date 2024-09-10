 static std::ptrdiff_t invoke( const char jobu, const char jobv,
         const char jobq, const fortran_int_t k,
         const fortran_int_t l, MatrixA& a, MatrixB& b,
         const real_type tola, const real_type tolb, VectorALPHA& alpha,
         VectorBETA& beta, MatrixU& u, MatrixV& v, MatrixQ& q,
         fortran_int_t& ncycle, detail::workspace1< WORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixB >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixU >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixV >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixQ >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorALPHA >::type >::type,
             typename remove_const< typename bindings::value_type<
             VectorBETA >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< MatrixA >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixB >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< MatrixA >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixU >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< MatrixA >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixV >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< MatrixA >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixQ >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixB >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorALPHA >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorBETA >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixU >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixV >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixQ >::value) );
     BOOST_ASSERT( bindings::size(alpha) >= bindings::size_column(a) );
     BOOST_ASSERT( bindings::size(work.select(value_type())) >=
             min_size_work( bindings::size_column(a) ));
     BOOST_ASSERT( bindings::size_column(a) >= 0 );
     BOOST_ASSERT( bindings::size_minor(a) == 1 ||
             bindings::stride_minor(a) == 1 );
     BOOST_ASSERT( bindings::size_minor(b) == 1 ||
             bindings::stride_minor(b) == 1 );
     BOOST_ASSERT( bindings::size_minor(q) == 1 ||
             bindings::stride_minor(q) == 1 );
     BOOST_ASSERT( bindings::size_minor(u) == 1 ||
             bindings::stride_minor(u) == 1 );
     BOOST_ASSERT( bindings::size_minor(v) == 1 ||
             bindings::stride_minor(v) == 1 );
     BOOST_ASSERT( bindings::size_row(a) >= 0 );
     BOOST_ASSERT( bindings::size_row(b) >= 0 );
     BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
             bindings::size_row(a)) );
     BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
             bindings::size_row(b)) );
     BOOST_ASSERT( jobq == 'Q' || jobq == 'I' || jobq == 'N' );
     BOOST_ASSERT( jobu == 'U' || jobu == 'I' || jobu == 'N' );
     BOOST_ASSERT( jobv == 'V' || jobv == 'I' || jobv == 'N' );
     return detail::tgsja( jobu, jobv, jobq, bindings::size_row(a),
             bindings::size_row(b), bindings::size_column(a), k, l,
             bindings::begin_value(a), bindings::stride_major(a),
             bindings::begin_value(b), bindings::stride_major(b), tola,
             tolb, bindings::begin_value(alpha),
             bindings::begin_value(beta), bindings::begin_value(u),
             bindings::stride_major(u), bindings::begin_value(v),
             bindings::stride_major(v), bindings::begin_value(q),
             bindings::stride_major(q),
             bindings::begin_value(work.select(value_type())), ncycle );
 }