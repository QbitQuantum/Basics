void MHSyncItemInfo::addExportedServices(const char* serviceName, time_t exportDate)
{
    if (serviceName) {
        StringBuffer exportDateStr;
        
        exportDateStr.sprintf("%ld", exportDate);
        
        exportedServices.put(serviceName, exportDateStr.c_str());
    }
}