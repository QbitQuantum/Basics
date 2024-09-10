 static std::ptrdiff_t invoke( const char fact, MatrixAB& ab,
         MatrixAFB& afb, char& equed, VectorS& s, MatrixB& b, MatrixX& x,
         real_type& rcond, VectorFERR& ferr, VectorBERR& berr,
         detail::workspace2< WORK, RWORK > work ) {
     namespace bindings = ::boost::numeric::bindings;
     typedef typename result_of::uplo_tag< MatrixAB >::type uplo;
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixAB >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixAFB >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixB >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixX >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorS >::type >::type,
             typename remove_const< typename bindings::value_type<
             VectorFERR >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< VectorS >::type >::type,
             typename remove_const< typename bindings::value_type<
             VectorBERR >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< MatrixAB >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixAFB >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< MatrixAB >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixB >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
             typename bindings::value_type< MatrixAB >::type >::type,
             typename remove_const< typename bindings::value_type<
             MatrixX >::type >::type >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixAB >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixAFB >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorS >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixB >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixX >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorFERR >::value) );
     BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorBERR >::value) );
     BOOST_ASSERT( bindings::bandwidth(ab, uplo()) >= 0 );
     BOOST_ASSERT( bindings::size(berr) >= bindings::size_column(b) );
     BOOST_ASSERT( bindings::size(work.select(real_type())) >=
             min_size_rwork( bindings::size_column(ab) ));
     BOOST_ASSERT( bindings::size(work.select(value_type())) >=
             min_size_work( bindings::size_column(ab) ));
     BOOST_ASSERT( bindings::size_column(ab) >= 0 );
     BOOST_ASSERT( bindings::size_column(b) >= 0 );
     BOOST_ASSERT( bindings::size_minor(ab) == 1 ||
             bindings::stride_minor(ab) == 1 );
     BOOST_ASSERT( bindings::size_minor(afb) == 1 ||
             bindings::stride_minor(afb) == 1 );
     BOOST_ASSERT( bindings::size_minor(b) == 1 ||
             bindings::stride_minor(b) == 1 );
     BOOST_ASSERT( bindings::size_minor(x) == 1 ||
             bindings::stride_minor(x) == 1 );
     BOOST_ASSERT( bindings::stride_major(ab) >= bindings::bandwidth(ab,
             uplo())+1 );
     BOOST_ASSERT( bindings::stride_major(afb) >= bindings::bandwidth(ab,
             uplo())+1 );
     BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
             bindings::size_column(ab)) );
     BOOST_ASSERT( bindings::stride_major(x) >= std::max< std::ptrdiff_t >(1,
             bindings::size_column(ab)) );
     BOOST_ASSERT( equed == 'N' || equed == 'Y' );
     BOOST_ASSERT( fact == 'F' || fact == 'Y' || fact == 'N' ||
             fact == 'E' );
     return detail::pbsvx( fact, uplo(), bindings::size_column(ab),
             bindings::bandwidth(ab, uplo()), bindings::size_column(b),
             bindings::begin_value(ab), bindings::stride_major(ab),
             bindings::begin_value(afb), bindings::stride_major(afb),
             equed, bindings::begin_value(s), bindings::begin_value(b),
             bindings::stride_major(b), bindings::begin_value(x),
             bindings::stride_major(x), rcond, bindings::begin_value(ferr),
             bindings::begin_value(berr),
             bindings::begin_value(work.select(value_type())),
             bindings::begin_value(work.select(real_type())) );
 }