void CMultiverseModel::OnUserSignedIn (const CString &sUsername)

//	OnUserSignedIn
//
//	The given user has signed in. The given username is the human-readable
//	username (not the username key).

	{
	CSmartLock Lock(m_cs);

	ASSERT(!sUsername.IsBlank());

	if (!strEquals(sUsername, m_sUsername) || !m_fUserSignedIn)
		{
		m_sUsername = sUsername;

		//	Clear out the collection so that we are forced to reload it.

		DeleteCollection();

		//	We're signed in

		m_fUserSignedIn = true;
		}
	}