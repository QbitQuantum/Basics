int
main(int argc,
     char **argv)
{
  UConverter *c;
  UErrorCode status = U_ZERO_ERROR;

  udata_setCommonData(NULL, &status);
  printf("setCommonData(NULL) -> %s [should fail]\n",  u_errorName(status));
  if(status != U_ILLEGAL_ARGUMENT_ERROR)
  {
    printf("*** FAIL: should have returned U_ILLEGAL_ARGUMENT_ERROR\n");
    return 1;
  }

  status = U_ZERO_ERROR;
  udata_setCommonData(&U_ICUDATA_ENTRY_POINT, &status);  
  printf("setCommonData(%p) -> %s\n", (void*)&U_ICUDATA_ENTRY_POINT, u_errorName(status));
  if(U_FAILURE(status))
  {
    printf("*** FAIL: should have returned U_ZERO_ERROR\n");
    return 1;
  }

  status = U_ZERO_ERROR;
  c = ucnv_open("iso-8859-3", &status);
  printf("ucnv_open(iso-8859-3)-> %p, err = %s, name=%s\n",
         (void *)c, u_errorName(status), (!c)?"?":ucnv_getName(c,&status)  );
  if(status != U_ZERO_ERROR)
  {
    printf("\n*** FAIL: should have returned U_ZERO_ERROR;\n");
    return 1;
  }
  else
  {
    ucnv_close(c);
  }

  status = U_ZERO_ERROR;
  udata_setCommonData(&U_ICUDATA_ENTRY_POINT, &status);
  printf("setCommonData(%p) -> %s [should pass]\n", (void*) &U_ICUDATA_ENTRY_POINT, u_errorName(status));
  if (U_FAILURE(status) || status == U_USING_DEFAULT_WARNING )
  {
    printf("\n*** FAIL: should pass and not set U_USING_DEFAULT_ERROR\n");
    return 1;
  }

  printf("\n*** PASS PASS PASS, test PASSED!!!!!!!!\n");
  return 0;
}