caddr_t
mts_get_rmcookie ()
{
  if (!local_rm)
    {
      return 0;
    }

  DOUBLE_LOCK (rmcookie, alloc_ret);

  try
  {
    auto_interface < ITransactionImportWhereabouts > import_abouts;
    HRESULT hr = DtcGetTransactionManager (0,
	0,
	__uuidof (ITransactionImportWhereabouts),
	0,
	0,
	0,
	(void **) &import_abouts.get ());
    MTS_THROW_ASSERT (hr, "Get ITransactionImportWhereabouts");

    hr = import_abouts->GetWhereaboutsSize (&local_rm->rmcookie_len);
    MTS_THROW_ASSERT (hr, "GetTransactionImportWhereaboutsLen");

    DWORD used;
    auto_dkptr < BYTE >
	whereabouts_aptr ((BYTE *) dk_alloc (sizeof (BYTE) *
	    local_rm->rmcookie_len));
    hr = import_abouts->GetWhereabouts (local_rm->rmcookie_len,
	whereabouts_aptr.get (), &used);

    local_rm->rmcookie = whereabouts_aptr.release ();
  }
  catch (const mts_error & err)
  {
    RELEASE_OBJECT (local_rm);
    err.dump ();
    return 0;
  }
  RELEASE_OBJECT (local_rm);

alloc_ret:
  caddr_t cookie = (caddr_t) dk_alloc_box (local_rm->rmcookie_len, DV_BIN);
  memcpy (cookie, local_rm->rmcookie, local_rm->rmcookie_len);

  return cookie;
};