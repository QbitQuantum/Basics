 /* "slow" portion of 'grow()'  */
 void grow_reallocate() {
     int a = 64;
     while( a < l )
         a = a * 2;
     data = (char *) al.Realloc(data, a);
     assert(data);
     if ( data == NULL )
     size = a;
 }