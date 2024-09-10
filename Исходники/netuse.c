static PyObject *
netuse_user_info(PyObject *self, PyObject *args)
{
  DWORD dwLevel = 1;
  LPWKSTA_USER_INFO_1 pBuf = NULL;
  NET_API_STATUS nStatus;
  //
  // Call the NetWkstaUserGetInfo function;
  //  specify level 1.
  //
  nStatus = NetWkstaUserGetInfo(NULL,
                                dwLevel,
                                (LPBYTE *)&pBuf);
  //
  // If the call succeeds, print the information
  //  about the logged-on user.
  //
  if (nStatus == NERR_Success) {
    if (pBuf != NULL) {
      size_t size = MAX_USERBUFFER_SIZE;
      size_t len;
      logonuser = userinfo;
      len = wchar2mchar(pBuf->wkui1_username, logonuser, size);
      if (len == -1) {
        PyErr_SetString(PyExc_RuntimeError, "Unicode conversion error");
        return NULL;
      }
      size -= len;
      logondomain = logonuser + len;
      len = wchar2mchar(pBuf->wkui1_logon_domain, logondomain, size);
      if (len == -1) {
        PyErr_SetString(PyExc_RuntimeError, "Unicode conversion error");
        return NULL;
      }
      size -= len;
      logonserver = logondomain + len;
      len = wchar2mchar(pBuf->wkui1_logon_server, logonserver, size);
      if (len == -1) {
        PyErr_SetString(PyExc_RuntimeError, "Unicode conversion error");
        return NULL;
      }
    }
  }
  // Otherwise, print the system error.
  //
  else {
    PyErr_Format(PyExc_RuntimeError,
                 "A system error has occurred: %ld",
                 nStatus
                 );
    return NULL;
  }
  //
  // Free the allocated memory.
  //
  if (pBuf != NULL) {
    NetApiBufferFree(pBuf);
    return Py_BuildValue("sss", logonserver, logondomain, logonuser);
  }

  PyErr_SetString(PyExc_RuntimeError, "No logon user information");
  return NULL;
}