BOOL
TSetupDlg::IsPageValid (void)
{
  switch (m_iCurPage)
    {
    case 0:
      /* DSN not blank */
      if (!m_bFileDSN)
	{
	  if (m_DSN.TextLength() == 0)
	    return FALSE;

	  /* DSN valid, except for file dsns */
	  if (!SQLValidDSN (m_DSN.Text ()))
	    return FALSE;
	}

      /* Server not blank */
      if (IsDlgComboEmpty (m_SERVER))
	return FALSE;
      break;

    case 1:
      /* If using login to connect to db for settings, then not blank */
      if (m_USEUID.Checked () && m_UID.TextLength() == 0)
	return FALSE;

      /* If using server certificate, then not blank */
      if (m_USESERVERCERT.Checked () && m_SERVERCERT.TextLength() == 0)
	return FALSE;

      break;

    case 2:
      /* If not using default database, then not blank */
      if (m_USEDEFAULTDB.Checked () && IsDlgComboEmpty (m_DEFAULTDB))
	return FALSE;

      /* If not using default charset, then not blank */
      if (m_USEDEFAULTCS.Checked () && IsDlgComboEmpty (m_DEFAULTCS))
	return FALSE;

      /* If not using default isolation level, then not blank */
      if (m_USEDEFAULTIL.Checked () && IsDlgComboEmpty (m_DEFAULTIL))
	return FALSE;
      break;

    default:
      break;
    }

  return TRUE;
}