/* Implementation of _pymfclib_winhttp */

static PyObject *__pyx_f_17_pymfclib_winhttp_getIEProxyConfigForCurrentUser(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyObject *__pyx_f_17_pymfclib_winhttp_getIEProxyConfigForCurrentUser(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  WINHTTP_CURRENT_USER_IE_PROXY_CONFIG __pyx_v_ieconfig;
  struct __pyx_obj_17_pymfclib_winhttp_CurrentUserIEProxyConfig *__pyx_v_ret;
  PyObject *__pyx_r;
  BOOL __pyx_1;
  PyObject *__pyx_2 = 0;
  int __pyx_3;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  __pyx_v_ret = ((struct __pyx_obj_17_pymfclib_winhttp_CurrentUserIEProxyConfig *)Py_None); Py_INCREF(Py_None);

  /* "c:\src\ip\pymfc\pymfclib\_pymfclib_winhttp.pyx":62 */
  memset((&__pyx_v_ieconfig),0,(sizeof(__pyx_v_ieconfig)));

  /* "c:\src\ip\pymfc\pymfclib\_pymfclib_winhttp.pyx":63 */
  __pyx_1 = WinHttpGetIEProxyConfigForCurrentUser((&__pyx_v_ieconfig));
  if (__pyx_1) {

    /* "c:\src\ip\pymfc\pymfclib\_pymfclib_winhttp.pyx":64 */
    __pyx_2 = PyObject_CallObject(((PyObject *)__pyx_ptype_17_pymfclib_winhttp_CurrentUserIEProxyConfig), 0); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; goto __pyx_L1;}
    Py_DECREF(((PyObject *)__pyx_v_ret));
    __pyx_v_ret = ((struct __pyx_obj_17_pymfclib_winhttp_CurrentUserIEProxyConfig *)__pyx_2);
    __pyx_2 = 0;

    /* "c:\src\ip\pymfc\pymfclib\_pymfclib_winhttp.pyx":65 */
    __pyx_2 = PyInt_FromLong(__pyx_v_ieconfig.fAutoDetect); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 65; goto __pyx_L1;}
    Py_DECREF(__pyx_v_ret->autodetect);
    __pyx_v_ret->autodetect = __pyx_2;
    __pyx_2 = 0;

    /* "c:\src\ip\pymfc\pymfclib\_pymfclib_winhttp.pyx":66 */
    /*try:*/ {

      /* "c:\src\ip\pymfc\pymfclib\_pymfclib_winhttp.pyx":67 */
      __pyx_3 = (__pyx_v_ieconfig.lpszAutoConfigUrl != 0);
      if (__pyx_3) {
        __pyx_2 = _fromWideChar(__pyx_v_ieconfig.lpszAutoConfigUrl); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; goto __pyx_L4;}
        Py_DECREF(__pyx_v_ret->autoconfigurl);
        __pyx_v_ret->autoconfigurl = __pyx_2;
        __pyx_2 = 0;
        goto __pyx_L6;
      }
      __pyx_L6:;

      /* "c:\src\ip\pymfc\pymfclib\_pymfclib_winhttp.pyx":69 */
      __pyx_3 = (__pyx_v_ieconfig.lpszProxy != 0);
      if (__pyx_3) {
        __pyx_2 = _fromWideChar(__pyx_v_ieconfig.lpszProxy); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 70; goto __pyx_L4;}
        Py_DECREF(__pyx_v_ret->proxy);
        __pyx_v_ret->proxy = __pyx_2;
        __pyx_2 = 0;
        goto __pyx_L7;
      }
      __pyx_L7:;

      /* "c:\src\ip\pymfc\pymfclib\_pymfclib_winhttp.pyx":71 */
      __pyx_3 = (__pyx_v_ieconfig.lpszProxyBypass != 0);
      if (__pyx_3) {
        __pyx_2 = _fromWideChar(__pyx_v_ieconfig.lpszProxyBypass); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 72; goto __pyx_L4;}
        Py_DECREF(__pyx_v_ret->proxybypass);
        __pyx_v_ret->proxybypass = __pyx_2;
        __pyx_2 = 0;
        goto __pyx_L8;
      }
      __pyx_L8:;
    }
    /*finally:*/ {
      int __pyx_why;
      PyObject *__pyx_exc_type, *__pyx_exc_value, *__pyx_exc_tb;
      int __pyx_exc_lineno;
      __pyx_why = 0; goto __pyx_L5;
      __pyx_L4: {
        __pyx_why = 4;
        Py_XDECREF(__pyx_2); __pyx_2 = 0;
        PyErr_Fetch(&__pyx_exc_type, &__pyx_exc_value, &__pyx_exc_tb);
        __pyx_exc_lineno = __pyx_lineno;
        goto __pyx_L5;
      }
      __pyx_L5:;

      /* "c:\src\ip\pymfc\pymfclib\_pymfclib_winhttp.pyx":74 */
      __pyx_3 = (__pyx_v_ieconfig.lpszAutoConfigUrl != 0);
      if (__pyx_3) {
        GlobalFree(__pyx_v_ieconfig.lpszAutoConfigUrl);
        goto __pyx_L10;
      }
      __pyx_L10:;

      /* "c:\src\ip\pymfc\pymfclib\_pymfclib_winhttp.pyx":76 */
      __pyx_3 = (__pyx_v_ieconfig.lpszProxy != 0);
      if (__pyx_3) {
        GlobalFree(__pyx_v_ieconfig.lpszProxy);
        goto __pyx_L11;
      }
      __pyx_L11:;

      /* "c:\src\ip\pymfc\pymfclib\_pymfclib_winhttp.pyx":78 */
      __pyx_3 = (__pyx_v_ieconfig.lpszProxyBypass != 0);
      if (__pyx_3) {
        GlobalFree(__pyx_v_ieconfig.lpszProxyBypass);
        goto __pyx_L12;
      }
      __pyx_L12:;
      switch (__pyx_why) {
        case 4: {
          PyErr_Restore(__pyx_exc_type, __pyx_exc_value, __pyx_exc_tb);
          __pyx_lineno = __pyx_exc_lineno;
          __pyx_exc_type = 0;
          __pyx_exc_value = 0;
          __pyx_exc_tb = 0;
          goto __pyx_L1;
        }
      }
    }

    /* "c:\src\ip\pymfc\pymfclib\_pymfclib_winhttp.pyx":80 */
    Py_INCREF(((PyObject *)__pyx_v_ret));
    __pyx_r = ((PyObject *)__pyx_v_ret);
    goto __pyx_L0;
    goto __pyx_L2;
  }
  __pyx_L2:;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  __Pyx_AddTraceback("_pymfclib_winhttp.getIEProxyConfigForCurrentUser");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_ret);
  return __pyx_r;
}