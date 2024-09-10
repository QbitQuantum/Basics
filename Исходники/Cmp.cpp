bool StrLess(StrLen a,StrLen b)
 {
  if( a.len<b.len )
    {
     ulen off=a.match(b.ptr);
     
     if( off<a.len ) return a[off]<b[off];
     
     return true;
    }
  else
    {
     ulen off=b.match(a.ptr);
     
     if( off<b.len ) return a[off]<b[off];
     
     return false;
    }
 }