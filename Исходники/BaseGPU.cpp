///////////////////////////////////////////////////////////////////////////////
//Copy Constructor
///////////////////////////////////////////////////////////////////////////////
BaseGPU::BaseGPU(const BaseGPU& baseGPU)
{
	this->m_bIsDefFanValid = baseGPU.GetIsDefFanValid();
	this->m_bIsFanValid = baseGPU.GetIsFanValid();
	this->m_bIsManaged = baseGPU.GetIsManaged();
	this->m_nAdapterIndex = baseGPU.GetAdapterIndex();
	this->m_nBusNumber = baseGPU.GetBusNumber();
	this->m_nLastEngine = baseGPU.GetLastEngine();
	this->m_nLastTemp = baseGPU.GetLastTemp();
	this->m_nGPUID = baseGPU.GetGPUID();
	this->m_szAdapterName = baseGPU.GetAdapterName();
	this->m_pGPUSettings = baseGPU.GetGPUSetting();
	this->m_pTwin = baseGPU.GetTwin();
}