void kuhl_m_kerberos_ccache_skip_buffer(PBYTE *data)
{
	*data += sizeof(DWORD) + _byteswap_ulong(*(PDWORD) *data);
}