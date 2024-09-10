bfd_boolean
generate_build_id (bfd *abfd,
		   const char *style,
		   checksum_fn checksum_contents,
		   unsigned char *id_bits,
		   int size ATTRIBUTE_UNUSED)
{
  if (streq (style, "md5"))
    {
      struct md5_ctx ctx;

      md5_init_ctx (&ctx);
      if (!(*checksum_contents) (abfd, (sum_fn) &md5_process_bytes, &ctx))
	return FALSE;
      md5_finish_ctx (&ctx, id_bits);
    }
  else if (streq (style, "sha1"))
    {
      struct sha1_ctx ctx;

      sha1_init_ctx (&ctx);
      if (!(*checksum_contents) (abfd, (sum_fn) &sha1_process_bytes, &ctx))
	return FALSE;
      sha1_finish_ctx (&ctx, id_bits);
    }
  else if (streq (style, "uuid"))
    {
#ifndef __MINGW32__
      int n;
      int fd = open ("/dev/urandom", O_RDONLY);

      if (fd < 0)
	return FALSE;
      n = read (fd, id_bits, size);
      close (fd);
      if (n < size)
	return FALSE;
#else /* __MINGW32__ */
      typedef RPC_STATUS (RPC_ENTRY * UuidCreateFn) (UUID *);
      UUID          uuid;
      UuidCreateFn  uuid_create = 0;
      HMODULE       rpc_library = LoadLibrary ("rpcrt4.dll");

      if (!rpc_library)
	return FALSE;
      uuid_create = (UuidCreateFn) (void (WINAPI *)(void)) GetProcAddress (rpc_library, "UuidCreate");
      if (!uuid_create)
	{
	  FreeLibrary (rpc_library);
	  return FALSE;
	}

      if (uuid_create (&uuid) != RPC_S_OK)
	{
	  FreeLibrary (rpc_library);
	  return FALSE;
	}
      FreeLibrary (rpc_library);
      memcpy (id_bits, &uuid,
	      (size_t) size < sizeof (UUID) ? (size_t) size : sizeof (UUID));
#endif /* __MINGW32__ */
    }
  else if (strneq (style, "0x", 2))
    {
      /* ID is in string form (hex).  Convert to bits.  */
      const char *id = style + 2;
      size_t n = 0;

      do
	{
	  if (ISXDIGIT (id[0]) && ISXDIGIT (id[1]))
	    {
	      id_bits[n] = read_hex (*id++) << 4;
	      id_bits[n++] |= read_hex (*id++);
	    }
	  else if (*id == '-' || *id == ':')
	    ++id;
	  else
	    abort ();		/* Should have been validated earlier.  */
	}
      while (*id != '\0');
    }
  else
    abort ();			/* Should have been validated earlier.  */

  return TRUE;
}