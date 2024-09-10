CHtmlPanelUIHandlerBase::~CHtmlPanelUIHandlerBase()
{
  if (m_blockedAcceleratorsTable)
  {
    DestroyAcceleratorTable(m_blockedAcceleratorsTable);
  }
}