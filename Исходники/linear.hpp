Matrix inverse( Matrix const & matrix )
{
    assert( matrix.rows() == matrix.cols() );

    auto [ p, lu ] = decompose( matrix, Strategy::LUP );

    std::vector< Matrix > xSolutions;
    xSolutions.reserve( lu.rows() );

    for ( std::size_t i{ 0 }; i < lu.rows(); ++i )
    {
        Matrix m{ lu.rows(), 1 };
        m( i, 0 ) = 1;
        m = p * m;
        supstitution::forward( lu, m );
        supstitution::backward( lu, m );
        xSolutions.emplace_back( m );
    }

    for ( std::size_t i{ 0 }; i < lu.rows(); ++i )
    {
        for ( std::size_t j{ 0 }; j < lu.cols(); ++j )
        {
            lu( i, j ) = xSolutions[ j ]( i, 0 );
        }
    }

    Matrix identity{ Matrix::Identity( lu.rows() ) };
    if ( lu.hasNan() || lu.hasInf() )
    {
        LOG_ERROR( "Matirx does not have inverse." );
    }

    return lu;
}