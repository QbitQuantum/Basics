 inline exception_ptr copy_exception( T&& e ) {
   try { throw e; } catch (...) { return current_exception(); }  
   return exception_ptr();
 }