 inline T norm(const ConstVectorBase<T, BaseClass>& v) 
 {
    T mag=T(0);
    if(v.size()==0) return mag;
    mag = ABS(v(0));
    for(size_t i=1; i<v.size(); i++) {
       if(mag > ABS(v(i)))
          mag *= SQRT(T(1)+(v(i)/mag)*(v(i)/mag));
       else if(ABS(v(i)) > mag)
          mag = ABS(v(i))*SQRT(T(1)+(mag/v(i))*(mag/v(i)));
       else
          mag *= SQRT(T(2));
    }
    return mag;
 } 