/*
  This will stop the dynamic library and free it from memory
 */
int close_dynamic_library( void *handle )
{
  return( FreeLibrary( handle ) );
}