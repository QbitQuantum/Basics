 Bigint operator - ( Bigint b ) {
     if( sign != b.sign ) return (*this) + b.inverseSign();
     if( (*this) < b ) return (b - (*this)).inverseSign();
     Bigint c;
     for( int i = 0, borrow = 0; i < (int)a.size(); i++ ) {
         borrow = a[i] - borrow - (i < b.size() ? b.a[i] : 48);
         c.a += borrow >= 0 ? borrow + 48 : borrow + 58;
         borrow = borrow >= 0 ? 0 : 1;
     }
     return c.normalize(sign);
 }