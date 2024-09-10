static bool
create_symlink (const char * dst_path, const char * src_path, bool dst_is_dir)
{
#ifndef _WIN32

  (void) dst_is_dir;

  return symlink (src_path, dst_path) != -1;

#else

  wchar_t * wide_src_path;
  wchar_t * wide_dst_path;
  bool ret = false;

  wide_src_path = tr_win32_utf8_to_native (src_path, -1);
  wide_dst_path = tr_win32_utf8_to_native (dst_path, -1);

  ret = CreateSymbolicLinkW (wide_dst_path, wide_src_path,
                             dst_is_dir ? SYMBOLIC_LINK_FLAG_DIRECTORY : 0);

  tr_free (wide_dst_path);
  tr_free (wide_src_path);

  return ret;

#endif
}