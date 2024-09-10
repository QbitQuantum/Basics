/**
  <summary>
  Create a new traversal object
  <summary>
  <returns>A pointer to the new object</returns>
  <remarks>
  The traversal object is not initialized until
  jsw_rbtfirst or jsw_rbtlast are called.
  The pointer must be released with jsw_rbtdelete
  </remarks>
*/
jsw_rbtrav_t *jsw_rbtnew ( void )
{
  return (jsw_rbtrav_t*)malloc ( sizeof ( jsw_rbtrav_t ) );
}