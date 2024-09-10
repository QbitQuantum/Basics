void ComTestStoreService::CheckForReportFaultsAndDelays(ComPointer<IFabricStatefulServicePartition> partition, ApiFaultHelper::ComponentName compName, std::wstring operationName)
{
    if (testStoreService_.ShouldFailOn(compName, operationName, ApiFaultHelper::ReportFaultPermanent))          
    {
        if (partition.GetRawPointer() != nullptr) 
        {
            partition->ReportFault(FABRIC_FAULT_TYPE::FABRIC_FAULT_TYPE_PERMANENT);
        } 
    };                                                                                          
    if (testStoreService_.ShouldFailOn(compName, operationName, ApiFaultHelper::ReportFaultTransient))          
    {     
        if (partition.GetRawPointer() != nullptr) 
        {
            partition->ReportFault(FABRIC_FAULT_TYPE::FABRIC_FAULT_TYPE_TRANSIENT);
        }
    };                                                                                          
    if (testStoreService_.ShouldFailOn(compName, operationName, ApiFaultHelper::Delay))               
    {         
        ::Sleep(static_cast<DWORD>(ApiFaultHelper::Get().GetApiDelayInterval().TotalMilliseconds()));
    }
}