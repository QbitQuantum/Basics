static void
nr_type_w32_init (void)
{
    LOGFONT logfont;
    GSList *l;
    int pos;

    g_print ("Loading W32 type directory...\n");

    hdc = CreateDC ("DISPLAY", NULL, NULL, NULL);

    familydict = g_hash_table_new (g_str_hash, g_str_equal);
    namedict = g_hash_table_new (g_str_hash, g_str_equal);

    /* read system font directory */
    memset (&logfont, 0, sizeof (LOGFONT));
    logfont.lfCharSet = DEFAULT_CHARSET;
    EnumFontFamiliesExA (hdc, &logfont, (FONTENUMPROC) nr_type_w32_typefaces_enum_proc, 0, 0);

    /* Fill in lists */
    NRW32Families.length = g_slist_length (familylist);
    NRW32Families.names = g_new (unsigned char *, NRW32Families.length);
    pos = 0;
    for (l = familylist; l != NULL; l = l->next) {
        NRW32Families.names[pos] = (unsigned char *) l->data;
        pos += 1;
    }
    NRW32Typefaces.length = g_slist_length (namelist);
    NRW32Typefaces.names = g_new (unsigned char *, NRW32Typefaces.length);
    pos = 0;
    for (l = namelist; l != NULL; l = l->next) {
        NRW32Typefaces.names[pos] = (unsigned char *) l->data;
        pos += 1;
    }

    w32i = TRUE;
}