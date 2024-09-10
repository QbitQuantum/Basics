/**
 * g_win32_check_windows_version:
 * @major: major version of Windows
 * @minor: minor version of Windows
 * @spver: Windows Service Pack Level, 0 if none
 * @os_type: Type of Windows OS
 *
 * Returns whether the version of the Windows operating system the
 * code is running on is at least the specified major, minor and
 * service pack versions.  See MSDN documentation for the Operating
 * System Version.  Software that needs even more detailed version and
 * feature information should use the Win32 API VerifyVersionInfo()
 * directly.
 *
 * Successive calls of this function can be used for enabling or
 * disabling features at run-time for a range of Windows versions,
 * as per the VerifyVersionInfo() API documentation.
 *
 * Returns: %TRUE if the Windows Version is the same or greater than
 *          the specified major, minor and service pack versions, and
 *          whether the running Windows is a workstation or server edition
 *          of Windows, if specifically specified.
 *
 * Since: 2.44
 **/
gboolean
g_win32_check_windows_version (const gint major,
                               const gint minor,
                               const gint spver,
                               const GWin32OSType os_type)
{
  OSVERSIONINFOEXW osverinfo;
  gboolean test_os_type;
  const DWORDLONG conds = gwin32condmask (gwin32condmask (gwin32condmask (0, VER_MAJORVERSION), VER_MINORVERSION), VER_SERVICEPACKMAJOR);

  memset (&osverinfo, 0, sizeof (OSVERSIONINFOEXW));
  osverinfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFOEXW);
  osverinfo.dwPlatformId = VER_PLATFORM_WIN32_NT;
  osverinfo.dwMajorVersion = major;
  osverinfo.dwMinorVersion = minor;
  osverinfo.wServicePackMajor = spver;

  switch (os_type)
    {
      case G_WIN32_OS_WORKSTATION:
        osverinfo.wProductType = VER_NT_WORKSTATION;
        test_os_type = TRUE;
        break;
      case G_WIN32_OS_SERVER:
        osverinfo.wProductType = VER_NT_SERVER;
        test_os_type = TRUE;
        break;
      default:
        test_os_type = FALSE;
        break;
    }

  if (test_os_type)
    return VerifyVersionInfoW (&osverinfo,
                               VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR | VER_PRODUCT_TYPE,
                               gwin32condmask (conds, VER_PRODUCT_TYPE));
  else
    return VerifyVersionInfoW (&osverinfo,
                               VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR,
                               conds);
}