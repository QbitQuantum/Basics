 bool heap_ok( const char *msg )
 {
   bool rc = true;
   int heap_status = _heapchk( );
   if( heap_status != _HEAPOK && heap_status != _HEAPEMPTY ) {
     std::cout << "!!! HEAP CONSISTENCY FAILURE: " << msg << "\n";
     rc = false;
   }
   return( rc );
 }