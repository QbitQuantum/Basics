void content_playlist_qsort(content_playlist_t *playlist, content_playlist_sort_fun_t *fn)
{
   qsort(playlist->entries, playlist->size, sizeof(content_playlist_entry_t),
         (int (*)(const void *, const void *))fn);
}