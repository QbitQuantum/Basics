int
tst_wcscspn (FILE * fp, int debug_flg)
{
  TST_DECL_VARS (size_t);
  wchar_t *ws1, *ws2;

  TST_DO_TEST (wcscspn)
  {
    TST_HEAD_LOCALE (wcscspn, S_WCSCSPN);
    TST_DO_REC (wcscspn)
    {
      TST_GET_ERRET (wcscspn);
      ws1 = TST_INPUT (wcscspn).ws1;
      ws2 = TST_INPUT (wcscspn).ws2;	/* external value: size WCSSIZE */
      ret = wcscspn (ws1, ws2);

      if (debug_flg)
	{
	  fprintf (stderr, "wcscspn: ret = %d\n", ret);
	}

      TST_IF_RETURN (S_WCSCSPN)
      {
      };
    }
  }

  return err_count;
}