gpointer
g_realloc (gpointer mem,
	   gsize    n_bytes)
{
  if (G_UNLIKELY (!g_mem_initialized))
    g_mem_init_nomessage();
  if (G_LIKELY (n_bytes))
    {
      mem = glib_mem_vtable.realloc (mem, n_bytes);
      if (mem)
	return mem;

      g_error ("%s: failed to allocate %"G_GSIZE_FORMAT" bytes",
               G_STRLOC, n_bytes);
    }

  if (mem)
    glib_mem_vtable.free (mem);

  return NULL;
}