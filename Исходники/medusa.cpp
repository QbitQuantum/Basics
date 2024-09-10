Cell* Medusa::GetCell(Address const& rAddr)
{
  boost::lock_guard<MutexType> Lock(m_Mutex);
  Cell* pCell = m_Database.RetrieveCell(rAddr);
  if (pCell == nullptr) return nullptr;

  auto spArch = GetArchitecture(pCell->GetArchitectureTag());
  if (!spArch) return nullptr;

  spArch->FormatCell(m_Database, m_FileBinStrm, rAddr, *pCell);
  return pCell;
}