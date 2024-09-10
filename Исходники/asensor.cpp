void ASENSOR::MakeRowVector( matrix &M )
{
    if( M.cols() > 1 )
    {
        M.transpose();
    }
}