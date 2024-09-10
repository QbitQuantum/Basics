void CTLB::RecordDifference( CLog &LogFile, const CTLB& rTLB)
{
	for (int i = 0, n = sizeof(m_tlb)/sizeof(m_tlb[0]); i < n; i++)
	{
		if (m_tlb[i].EntryDefined != rTLB.m_tlb[i].EntryDefined) 
		{
			LogFile.LogF("TLB[%d] Defined: %s %s\r\n",i,m_tlb[i].EntryDefined ? "Yes" : "No",rTLB.m_tlb[i].EntryDefined ? "Yes" : "No");
			continue;
		}
		if (!m_tlb[i].EntryDefined)
		{
			continue;
		}
		if (m_tlb[i].PageMask.Value != rTLB.m_tlb[i].PageMask.Value)
		{
			LogFile.LogF("TLB[%d] PageMask: %X %X\r\n",i,m_tlb[i].PageMask.Value,rTLB.m_tlb[i].PageMask.Value);
		}
		if (m_tlb[i].EntryHi.Value != rTLB.m_tlb[i].EntryHi.Value)
		{
			LogFile.LogF("TLB[%d] EntryHi: %X %X\r\n",i,m_tlb[i].EntryHi.Value,rTLB.m_tlb[i].EntryHi.Value);
		}
		if (m_tlb[i].EntryLo0.Value != rTLB.m_tlb[i].EntryLo0.Value)
		{
			LogFile.LogF("TLB[%d] EntryLo0: %X %X\r\n",i,m_tlb[i].EntryLo0.Value,rTLB.m_tlb[i].EntryLo0.Value);
		}
		if (m_tlb[i].EntryLo1.Value != rTLB.m_tlb[i].EntryLo1.Value)
		{
			LogFile.LogF("TLB[%d] EntryLo1: %X %X\r\n",i,m_tlb[i].EntryLo1.Value,rTLB.m_tlb[i].EntryLo1.Value);
		}
	}
}