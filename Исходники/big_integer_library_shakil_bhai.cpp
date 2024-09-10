 Bigint operator - ( Bigint b ) { // subtraction operator overloading
     if( sign != b.sign ) return (*this) + b.inverseSign();
     int s = sign; sign = b.sign = 1;
     if( (*this) < b ) return ((b - (*this)).inverseSign()).normalize(-s);
     Bigint c;
     for( int i = 0, borrow = 0; i < a.size(); i++ ) {
         borrow = a[i] - borrow - (i < b.size() ? b.a[i] : 48);
         c.a += borrow >= 0 ? borrow + 48 : borrow + 58;
         borrow = borrow >= 0 ? 0 : 1;
     }
     return c.normalize(s);
 }