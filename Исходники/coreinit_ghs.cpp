void ghsCleanupExceptions()
{
   if (p__cpp_exception_cleanup_ptr->getAddress()) {
      auto thread = getCurrentThread();

      if (thread->_ghs__eh_globals.getAddress()) {
         (*p__cpp_exception_cleanup_ptr)(&thread->_ghs__eh_globals);
         thread->_ghs__eh_globals = nullptr;
      }
   }
}