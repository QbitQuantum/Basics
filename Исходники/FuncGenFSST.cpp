void Cos::CalcOneStep(){
    _pos += _inc;
    if(_pos >= _N){
        _pos -= _N;
    }
    
    int i = Floor(_pos);
    double frac = _pos-i;
    
    int ii = i+1;
    if(ii>= _N){
        ii=0;
    }
    
    val = table[i]+((table[ii]-table[i])*frac);
}