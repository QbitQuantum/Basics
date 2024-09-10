static int
testDirectory (unsigned int i)
{
  struct GNUNET_FS_DirectoryBuilder *db;
  char *data;
  size_t dlen;
  struct GNUNET_FS_Uri **uris;
  struct GNUNET_CONTAINER_MetaData **mds;
  struct GNUNET_CONTAINER_MetaData *meta;
  struct PCLS cls;
  char *emsg;
  int p;
  int q;
  char uri[512];
  char txt[128];
  int ret = 0;
  struct GNUNET_TIME_Absolute start;
  const char *s;

  cls.max = i;
  uris = GNUNET_malloc (sizeof (struct GNUNET_FS_Uri *) * i);
  mds = GNUNET_malloc (sizeof (struct GNUNET_CONTAINER_MetaData *) * i);
  meta = GNUNET_CONTAINER_meta_data_create ();
  GNUNET_CONTAINER_meta_data_insert (meta, "<test>", EXTRACTOR_METATYPE_TITLE,
                                     EXTRACTOR_METAFORMAT_UTF8, "text/plain",
                                     "A title", strlen ("A title") + 1);
  GNUNET_CONTAINER_meta_data_insert (meta, "<test>",
                                     EXTRACTOR_METATYPE_AUTHOR_NAME,
                                     EXTRACTOR_METAFORMAT_UTF8, "text/plain",
                                     "An author", strlen ("An author") + 1);
  for (p = 0; p < i; p++)
  {
    mds[p] = GNUNET_CONTAINER_meta_data_create ();
    for (q = 0; q <= p; q++)
    {
      GNUNET_snprintf (txt, sizeof (txt), "%u -- %u\n", p, q);
      GNUNET_CONTAINER_meta_data_insert (mds[p], "<test>",
#if HAVE_EXTRACTOR_H && HAVE_LIBEXTRACTOR
                                         q % EXTRACTOR_metatype_get_max (),
#else
                                         q % 128,
#endif
                                         EXTRACTOR_METAFORMAT_UTF8,
                                         "text/plain", txt, strlen (txt) + 1);
    }
    GNUNET_snprintf (uri, sizeof (uri),
                     "gnunet://fs/chk/C282GG70GKK41O4551011DO413KFBVTVMQG1OG30I0K4045N0G41HAPB82G680A02JRVVFO8URVRU2F159011DO41000000022RG820.RNVVVVOOLCLK065B5D04HTNVNSIB2AI022RG8200HSLK1CO1000ATQ98824DMA2032LIMG50CG0K057NVUVG200000H000004400000.%u",
                     p);
    emsg = NULL;
    uris[p] = GNUNET_FS_uri_parse (uri, &emsg);
    if (uris[p] == NULL)
    {
      GNUNET_CONTAINER_meta_data_destroy (mds[p]);
      while (--p > 0)
      {
        GNUNET_CONTAINER_meta_data_destroy (mds[p]);
        GNUNET_FS_uri_destroy (uris[p]);
      }
      GNUNET_free (mds);
      GNUNET_free (uris);
      GNUNET_free (emsg);
      GNUNET_CONTAINER_meta_data_destroy (meta);
      ABORT ();                 /* error in testcase */
    }
    GNUNET_assert (emsg == NULL);
  }
  start = GNUNET_TIME_absolute_get ();
  db = GNUNET_FS_directory_builder_create (meta);
  for (p = 0; p < i; p++)
    GNUNET_FS_directory_builder_add (db, uris[p], mds[p], NULL);
  GNUNET_FS_directory_builder_finish (db, &dlen, (void **) &data);
  s = GNUNET_STRINGS_relative_time_to_string (GNUNET_TIME_absolute_get_duration
                                              (start),
					      GNUNET_YES);
  FPRINTF (stdout,
           "Creating directory with %u entires and total size %llu took %s\n",
           i, (unsigned long long) dlen, s);
  if (i < 100)
  {
    cls.pos = 0;
    cls.uri = uris;
    cls.md = mds;
    GNUNET_FS_directory_list_contents (dlen, data, 0, &processor, &cls);
    GNUNET_assert (cls.pos == i);
  }
  GNUNET_free (data);
  GNUNET_CONTAINER_meta_data_destroy (meta);
  for (p = 0; p < i; p++)
  {
    GNUNET_CONTAINER_meta_data_destroy (mds[p]);
    GNUNET_FS_uri_destroy (uris[p]);
  }
  GNUNET_free (uris);
  GNUNET_free (mds);
  return ret;
}