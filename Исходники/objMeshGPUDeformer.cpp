 void ObjMeshGPUDeformer::heap_check_()
 {
   int heapstatus = _heapchk();
   switch( heapstatus )
   {
     case _HEAPOK:
       printf(" OK - heap is fine\n" );
     break;
     case _HEAPEMPTY:
       printf(" OK - heap is empty\n" );
     break;
     case _HEAPBADBEGIN:
       printf( "ERROR - bad start of heap\n" );
     break;
     case _HEAPBADNODE:
       printf( "ERROR - bad node in heap\n" );
     break;
   }
 }