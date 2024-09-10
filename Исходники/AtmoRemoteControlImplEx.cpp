STDMETHODIMP CAtmoRemoteControlImplEx::setChannelValues(SAFEARRAY *channel_values)
{
  if(!channel_values) return S_FALSE;
  ATMO_BOOL result = ATMO_FALSE;
  unsigned char *pChannel_Values;

  SafeArrayAccessData(channel_values,(void **)&pChannel_Values);
  int numElements = channel_values->rgsabound[0].cElements;

  this->m_pAtmoDynData->LockCriticalSection();

  CAtmoConnection *connection = this->m_pAtmoDynData->getAtmoConnection();
  if((connection!=NULL) && (connection->isOpen())) {
     result = connection->setChannelValues(numElements, pChannel_Values);
  }

  this->m_pAtmoDynData->UnLockCriticalSection();

  SafeArrayUnaccessData(channel_values);

  if(result == ATMO_TRUE)
     return S_OK;
  else
     return S_FALSE;
}