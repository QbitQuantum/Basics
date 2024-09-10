gboolean
spice_win32_set_low_integrity (void* handle, GError **error)
{
    g_return_val_if_fail (handle != NULL, FALSE);
    g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

    /* see also http://msdn.microsoft.com/en-us/library/bb625960.aspx */
    PSECURITY_DESCRIPTOR psd = NULL;
    PACL psacl = NULL;
    BOOL sacl_present = FALSE;
    BOOL sacl_defaulted = FALSE;
    char *emsg;
    int errsv;
    gboolean success = FALSE;

    if (!ConvertStringSecurityDescriptorToSecurityDescriptor ("S:(ML;;NW;;;LW)",
            SDDL_REVISION_1, &psd, NULL))
        goto failed;

    if (!GetSecurityDescriptorSacl (psd, &sacl_present, &psacl, &sacl_defaulted))
        goto failed;

    if (SetSecurityInfo (handle, SE_KERNEL_OBJECT, LABEL_SECURITY_INFORMATION,
                         NULL, NULL, NULL, psacl) != ERROR_SUCCESS)
        goto failed;

    success = TRUE;
    goto end;

failed:
    errsv = GetLastError ();
    emsg = g_win32_error_message (errsv);
    g_set_error (error, G_IO_ERROR,
                 g_io_error_from_win32_error (errsv),
                 "Error setting integrity: %s",
                 emsg);
    g_free (emsg);

end:
    if (psd != NULL)
        LocalFree (psd);

    return success;
}