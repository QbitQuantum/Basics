 void SSEVector3::SetElem( Numerics::uint8 idx, float value )
 {
   __m128 val = _mm_set1_ps( value );
   switch( idx )
   {
   case 0:
     vec = _mm_insert_ps( vec, val, 0x00 );
     break;
   case 1:
     vec = _mm_insert_ps( vec, val, 0x10 );
     break;
   case 2:
     vec = _mm_insert_ps( vec, val, 0x20 );
     break;
   }
 }