BOOL QstInitialize( void )
{
   // Ascertain path for HECI driver

   if( !LookupDriver() )
      return( FALSE );

   // Obtain mutex to ensure process-safe/thread-safe communications

#ifdef USE_GLOBAL_MUTEX
   hMutex = CreateMutex( NULL, FALSE, __TEXT("Global\\QSTCommandMutex") );
#else
   hMutex = CreateMutex( NULL, FALSE, NULL );
#endif

   if( !hMutex )
      return( FALSE );

#ifdef USE_GLOBAL_MUTEX

   // If creator of global Mutex, enable access by others

   if( GetLastError() != ERROR_ALREADY_EXISTS )
   {
      SECURITY_DESCRIPTOR sd;

      InitializeSecurityDescriptor( &sd, SECURITY_DESCRIPTOR_REVISION );
      SetSecurityDescriptorDacl( &sd, TRUE, NULL, FALSE );
      SetKernelObjectSecurity( hMutex, DACL_SECURITY_INFORMATION, &sd );
   }

#endif

   // Indicate we require driver attachment

   bAttached = FALSE;
   return( TRUE );
}