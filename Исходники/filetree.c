static struct filename_representations
*filename_representations_new(const char *raw, int type)
{
    struct filename_representations *fr;
    char *display_pre;
    char *real_path;
#ifdef G_OS_WIN32
    DWORD buffer_length;
    gunichar2 *raw_utf16, *real_path_utf16;
#endif

    fr = g_malloc(sizeof(struct filename_representations));
    fr->type = type;
    fr->raw = g_strdup(raw);

#ifdef G_OS_WIN32
    raw_utf16 = g_utf8_to_utf16(fr->raw, -1, NULL, NULL, NULL);
    buffer_length = GetFullPathNameW(raw_utf16, 0, NULL, NULL);
    real_path_utf16 = g_malloc(buffer_length * sizeof(gunichar2));
    GetFullPathNameW(raw_utf16, buffer_length, real_path_utf16, NULL);
    real_path = g_utf16_to_utf8(raw_utf16, -1, NULL, NULL, NULL);
    g_free(real_path_utf16);
    g_free(raw_utf16);
#else
    real_path = realpath(fr->raw, NULL);
#endif
    display_pre = g_filename_display_name(real_path);
    fr->collate_key = g_utf8_collate_key_for_filename(display_pre, -1);

    fr->display = g_strescape(display_pre,
                              (const gchar *) strescape_exceptions);
    g_free(display_pre);
    g_free(real_path);
    return fr;
}