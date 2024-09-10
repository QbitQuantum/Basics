	/// Dtor.
   virtual ~fptrostream ()
   {
#ifdef _MSC_VER
	   _pclose(fptr_);
#else
	   pclose(fptr_);
#endif
   }