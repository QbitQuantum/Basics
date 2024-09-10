inline const PointGrid<R,d,q>&
PointGrid<R,d,q>::operator= ( const PointGrid<R,d,q>& pointGrid )
{
    const size_t q_to_d = Pow<q,d>::val;
    memcpy( &points_[0][0], &pointGrid[0][0], q_to_d*sizeof(R) );
    return *this;
}