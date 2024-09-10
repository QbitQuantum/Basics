/* Copy manual from install dir to Seafile directory */
void
copy_user_manual ()
{
    char *installdir;            /* C:\Program Files\Seafile */
    char *seafdir;              /* C:\Seafile */
    char *src_path;             /* C:\Program Files\Seafile\help.txt */
    char *dst_path;             /* C:\Seafile\help.txt */

    wchar_t *src_path_w, *dst_path_w;

    installdir = g_path_get_dirname (seafile_bin_dir);
    seafdir = g_path_get_dirname (applet->seafile_dir);

    src_path = g_build_filename (installdir, _("Seafile help.txt"), NULL);
    dst_path = g_build_filename (seafdir, _("Seafile help.txt"), NULL);

    src_path_w = wchar_from_utf8 (src_path);
    dst_path_w = wchar_from_utf8 (dst_path);

    BOOL failIfExist = FALSE;
    CopyFileW (src_path_w, dst_path_w, failIfExist);

    g_free (installdir);
    g_free (seafdir);
    g_free (src_path);
    g_free (dst_path);
    g_free (src_path_w);
    g_free (dst_path_w);
}