Real MR::T(size_t i, sub_nb A) {
    sub_nb _nbi_min_A(G.nb(i).size());
    _nbi_min_A.set();
    _nbi_min_A &= ~A;

    Real res = theta[i];
    for( size_t _j = 0; _j < _nbi_min_A.size(); _j++ )
        if( _nbi_min_A.test(_j) )
            res += atanh(tJ[i][_j] * M[i][_j]);
    return tanh(res);
}