CAccelerator::CAccelerator() : 
	m_hAccel(NULL), 
	m_hAdditionalAccel(NULL), 
	m_pEntriesTable(new stAccelEntry[ACCEL_COUNT]), 
	m_pAccelTable(new ACCEL[ACCEL_COUNT])
{
	ATLTRACE2(atlTraceGeneral, 0, "Accelerator: Accelerator table contains %d items\n", ACCEL_COUNT);
}