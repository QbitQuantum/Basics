int ls_iniGetStr(struct ls_Ini* self, char* app, char* key, int outLen, char* outValue)
{
  if (NULL != self && NULL != app && NULL != key && NULL != outValue && outLen > 0)
  {
    if (GetPrivateProfileStringA(app, key, NULL, outValue, outLen, self->file) >= (unsigned long)outLen)
      return LS_Failed;
    return LS_Success;
  }
  return LS_Failed_InvalidParameters;
}