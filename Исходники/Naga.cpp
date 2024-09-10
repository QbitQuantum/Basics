// ----------------------------------------------------------------------- //
// ROUTINE		: Naga::MC_Extra
// DESCRIPTION	: Create or remove (and fire) the spike
// RETURN TYPE	: void 
// ----------------------------------------------------------------------- //
void Naga::MC_Extra(const char *lpszParam)
{
	if (m_bAnimating && lpszParam) 
	{
		DDWORD dwFlags;

		if (_mbsicmp((const unsigned char*)lpszParam,(const unsigned char*)"take_spike") == 0)
		{
			// Make the spike visible
			dwFlags = m_pServerDE->GetObjectFlags(m_hSpike);
			dwFlags |= FLAG_VISIBLE;
			m_pServerDE->SetObjectFlags(m_hSpike, dwFlags);
		}

		if (_mbsicmp((const unsigned char*)lpszParam,(const unsigned char*)"fire_spike") == 0)
		{
			// Hide the hand-spike...
			dwFlags = m_pServerDE->GetObjectFlags(m_hSpike);
			dwFlags &= ~FLAG_VISIBLE;
			m_pServerDE->SetObjectFlags(m_hSpike, dwFlags);

			// ...and fire the spike weapon.
			Fire();
		}
	}
}