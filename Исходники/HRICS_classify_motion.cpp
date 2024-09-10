 Eigen::MatrixXd ClassifyMotion::convert_to_matrix( const std::vector< std::vector< std::string > >& matrix )
{
    Eigen::MatrixXd result;

    if(matrix.empty())
        return result;

    if(matrix[0].empty())
        return result;

    result.setZero( matrix.size(), matrix[0].size() );

    for( int i=0; i<int(matrix.size()); i++ )
    {
        for( int j=0; j<int(matrix[i].size()); j++ )
        {
            std::istringstream convert( matrix[i][j] );
            convert >> result(i,j);
        }
    }

    return result;
}