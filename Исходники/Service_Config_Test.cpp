void
testNonACEThread ()
{
  ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("Beginning non-ACE thread lookup test\n")));

  static const ACE_TCHAR *svc_desc =
#if (ACE_USES_CLASSIC_SVC_CONF == 1)
    ACE_TEXT ("dynamic Test_Object_1_Thr Service_Object * ")
    ACE_TEXT ("  Service_Config_DLL:_make_Service_Config_DLL() \"Test_Object_1_Thr\"")
#else
    ACE_TEXT ("<dynamic id=\"Test_Object_1_Thr\" type=\"Service_Object\">")
    ACE_TEXT ("  <initializer init=\"_make_Service_Config_DLL\" path=\"Service_Config_DLL\" params=\"Test_Object_1_Thr\"/>")
    ACE_TEXT ("</dynamic>")
#endif /* (ACE_USES_CLASSIC_SVC_CONF == 1) */
    ;

  static const ACE_TCHAR *svc_remove =
#if (ACE_USES_CLASSIC_SVC_CONF == 1)
    ACE_TEXT ("remove Test_Object_1_Thr")
#else
    ACE_TEXT ("<remove id=\"Test_Object_1_Thr\"/>")
    ACE_TEXT ("</remove>")
#endif /* (ACE_USES_CLASSIC_SVC_CONF == 1) */
    ;

  if (-1 == ACE_Service_Config::process_directive (svc_desc))
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%p\n"),
                  ACE_TEXT ("Error loading service")));
      ++error;
      return;
    }

  // Allow the spawned thread to contribute to the logging output.
  ACE_OS_Log_Msg_Attributes log_msg_attrs;
  ACE_Log_Msg::init_hook (log_msg_attrs);

  u_int errors_before = error;

#if defined (ACE_HAS_WTHREADS) && !defined (ACE_HAS_WINCE)
  HANDLE thr_h = (HANDLE)_beginthreadex (0,
                                         0,
                                         &nonacethreadentry,
                                         &log_msg_attrs,
                                         0,
                                         0);
  if (thr_h == 0)
    {
      ACE_ERROR ((LM_ERROR, ACE_TEXT ("%p\n"), ACE_TEXT ("_beginthreadex")));
      ++error;
    }
  else
    {
      WaitForSingleObject (thr_h, INFINITE);
      CloseHandle (thr_h);
    }
#elif defined (ACE_HAS_PTHREADS)
  pthread_t thr_id;
  int status = pthread_create (&thr_id, 0, nonacethreadentry, &log_msg_attrs);
  if (status != 0)
    {
      errno = status;
      ACE_ERROR ((LM_ERROR, ACE_TEXT ("%p\n"), ACE_TEXT ("pthread_create")));
      ++error;
    }
  else
    {
      pthread_join (thr_id, 0);
    }
#endif

  if (error != errors_before)  // The test failed; see if we can still see it
    {
      if (0 != ACE_Service_Config::instance()->find (ACE_TEXT ("Test_Object_1_Thr")))
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("Main thr %t cannot find Test_Object_1_Thr\n")));
          ++error;
        }
      else
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("Main thr %t DOES find Test_Object_1_Thr\n")));
    }

  if (-1 == ACE_Service_Config::process_directive (svc_remove))
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%p\n"),
                  ACE_TEXT ("Error removing service")));
      ++error;
    }
  else
    {
      ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("Non-ACE thread lookup test completed\n")));
    }
}