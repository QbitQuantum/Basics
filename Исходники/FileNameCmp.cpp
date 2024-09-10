CmpResult NativeNameCmp(StrLen a,StrLen b)
 {
  if( a.len<b.len )
    {
     ulen off=a.match(b.ptr);

     if( off<a.len ) return NativeCmp(a[off],b[off]);

     return CmpLess;
    }
  else
    {
     ulen off=b.match(a.ptr);

     if( off<b.len ) return NativeCmp(a[off],b[off]);

     return (a.len==b.len)?CmpEqual:CmpGreater;
    }
 }