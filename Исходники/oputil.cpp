static bool findMac(const IP_ADAPTER_INFO *adapterInfo, quint32 ipv4Host, QByteArray& mac)
{
	Q_UNUSED(adapterInfo)

	DWORD ip = qToBigEndian(ipv4Host);

	ULONG bufferLen = sizeof(MIB_IPNETROW) * 1000;
	std::vector<BYTE> buffer(bufferLen);
	MIB_IPNETTABLE *ipTable = reinterpret_cast<MIB_IPNETTABLE*>(&buffer[0]);
	if (NO_ERROR != GetIpNetTable(ipTable, &bufferLen, FALSE)) {
		return false;
	}

	for (DWORD i = 0; i < ipTable->dwNumEntries; i++) {
		const MIB_IPNETROW& row = ipTable->table[i];
		if (row.dwAddr == ip && row.dwPhysAddrLen == 6) {
			mac = QByteArray(reinterpret_cast<const char*>(&row.bPhysAddr[0]), 6);
			return true;
		}
	}

	return false;
}