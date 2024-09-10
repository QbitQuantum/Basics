/* Strips "\\\\?\\" extended prefix or
 * "\\??\\" NT Object Manager prefix from
 * @str in-place, using memmove.
 * @str_size must point to the size of @str
 * in gunichar2s, including NUL-terminator
 * (if @str is NUL-terminated; it doesn't have to be).
 * On return @str_size will correctly reflect changes
 * in @str size (if any).
 * Returns TRUE if @str was modified.
 */
static gboolean
_g_win32_strip_extended_ntobjm_prefix (gunichar2 *str,
                                       gsize     *str_size)
{
  const wchar_t *extended_prefix = L"\\\\?\\";
  const gsize    extended_prefix_len = wcslen (extended_prefix);
  const gsize    extended_prefix_len_bytes = sizeof (gunichar2) * extended_prefix_len;
  const gsize    extended_prefix_with_drive_len_bytes = sizeof (gunichar2) * (extended_prefix_len + 2);
  const wchar_t *ntobjm_prefix = L"\\??\\";
  const gsize    ntobjm_prefix_len = wcslen (ntobjm_prefix);
  const gsize    ntobjm_prefix_len_bytes = sizeof (gunichar2) * ntobjm_prefix_len;
  const gsize    ntobjm_prefix_with_drive_len_bytes = sizeof (gunichar2) * (ntobjm_prefix_len + 2);
  gboolean do_move = FALSE;
  gsize move_shift = 0;

  if ((*str_size) * sizeof (gunichar2) > extended_prefix_with_drive_len_bytes &&
      memcmp (str,
              extended_prefix,
              extended_prefix_len_bytes) == 0 &&
      iswascii (str[extended_prefix_len]) &&
      iswalpha (str[extended_prefix_len]) &&
      str[extended_prefix_len + 1] == L':')
   {
     do_move = TRUE;
     move_shift = extended_prefix_len;
   }
  else if ((*str_size) * sizeof (gunichar2) > ntobjm_prefix_with_drive_len_bytes &&
           memcmp (str,
                   ntobjm_prefix,
                   ntobjm_prefix_len_bytes) == 0 &&
           iswascii (str[ntobjm_prefix_len]) &&
           iswalpha (str[ntobjm_prefix_len]) &&
           str[ntobjm_prefix_len + 1] == L':')
    {
      do_move = TRUE;
      move_shift = ntobjm_prefix_len;
    }

  if (do_move)
    {
      *str_size -= move_shift;
      memmove (str,
               str + move_shift,
               (*str_size) * sizeof (gunichar2));
    }

  return do_move;
}