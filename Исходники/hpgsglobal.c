/*! This function has to be called atfer the last usage of hpgs.
    It cleans up internally allocated resources.
*/
void hpgs_cleanup()
{
  hpgs_font_cleanup();

  hpgs_cleanup_plugin_devices();

  if (hpgs_reader_prefix)
    {
      free(hpgs_reader_prefix);
      hpgs_reader_prefix = 0;
    }
#ifdef WIN32
  TlsFree(tls_handle);
  HeapDestroy(hHeap);
  hHeap=0;
  tls_handle=-1;
#else
  hpgs_clear_error();
  pthread_key_delete (key);
#endif
}