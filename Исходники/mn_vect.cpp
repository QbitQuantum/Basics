int VECT::Insert(int pos, void* buf, int ile)
{
if( !buf ) return 0;
if ( pos*size > nbytes || ile < 0L ) return 0;

if( !ptr && !size ) return 0;

if( ile == 0L ) return 1;
// if empty
if( ptr == 0 && size != 0 && pos == 0L )
  {
   if( !Alloc( ile, size ) ) return 0;
   memcpy( ptr, buf, ile*size );
   return 1;
  }

unsigned int oldnbytes = nbytes;
if( !ReAlloc( Nelem() + ile ) ) return 0;

if( pos*size < oldnbytes ) memmove( ((char*)ptr) + (pos+ile)*size, ((char*)ptr) + pos*size, oldnbytes-pos*size );
memcpy( ((char*)ptr) + pos*size, buf, ile*size );

return 1;
}