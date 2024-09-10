  /* routine that frees graph for struct _LSAPR_SECURITY_DESCRIPTOR */
void _fgs__LSAPR_SECURITY_DESCRIPTOR (LSAPR_SECURITY_DESCRIPTOR  * _source)
  {
  if (_source->Owner !=0)
    {
    MIDL_user_free((void  *)(_source->Owner));
    }
  if (_source->Group !=0)
    {
    MIDL_user_free((void  *)(_source->Group));
    }
  if (_source->Sacl !=0)
    {
    MIDL_user_free((void  *)(_source->Sacl));
    }
  if (_source->Dacl !=0)
    {
    MIDL_user_free((void  *)(_source->Dacl));
    }
  }