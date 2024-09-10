/** 
 * @brief Increase found items (dirs and files) count.
 * @param [in] count Amount of items to add.
 */
void CompareStats::IncreaseTotalItems(int count /*= 1*/)
{
	EnterCriticalSection(&m_csProtect);
	m_nTotalItems += count;
	LeaveCriticalSection(&m_csProtect);
}