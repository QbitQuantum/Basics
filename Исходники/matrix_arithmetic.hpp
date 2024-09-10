inline typename result_of::adjugate_at_index<Row,Column,Matrix>::type adjugate_at_index( const Matrix& m )
{
    matrix_minor<Matrix, Column, Row> mm( m );
    return power_c<-1,Row+Column>::value * determinant( mm );
}