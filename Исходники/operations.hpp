    bool operator()(const Matx<_Tp, 2, 2>& a, Matx<_Tp, 2, 2>& b, int) const
    {
        _Tp d = (_Tp)determinant(a);
        if( d == 0 )
=======