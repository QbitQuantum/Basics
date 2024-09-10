bool
lldb_private::formatters::NSDateSummaryProvider (ValueObject& valobj, Stream& stream, const TypeSummaryOptions& options)
{
    ProcessSP process_sp = valobj.GetProcessSP();
    if (!process_sp)
        return false;
    
    ObjCLanguageRuntime* runtime = (ObjCLanguageRuntime*)process_sp->GetLanguageRuntime(lldb::eLanguageTypeObjC);
    
    if (!runtime)
        return false;
    
    ObjCLanguageRuntime::ClassDescriptorSP descriptor(runtime->GetClassDescriptor(valobj));
    
    if (!descriptor || !descriptor->IsValid())
        return false;
    
    uint32_t ptr_size = process_sp->GetAddressByteSize();
    
    lldb::addr_t valobj_addr = valobj.GetValueAsUnsigned(0);
    
    if (!valobj_addr)
        return false;
    
    uint64_t date_value_bits = 0;
    double date_value = 0.0;
    
    ConstString class_name = descriptor->GetClassName();
    
    static const ConstString g_NSDate("NSDate");
    static const ConstString g___NSDate("__NSDate");
    static const ConstString g___NSTaggedDate("__NSTaggedDate");
    static const ConstString g_NSCalendarDate("NSCalendarDate");

    if (class_name.IsEmpty())
        return false;
    
    if ((class_name == g_NSDate) ||
        (class_name == g___NSDate) ||
        (class_name == g___NSTaggedDate))
    {
        uint64_t info_bits=0,value_bits = 0;
        if (descriptor->GetTaggedPointerInfo(&info_bits,&value_bits))
        {
            date_value_bits = ((value_bits << 8) | (info_bits << 4));
            memcpy(&date_value, &date_value_bits, sizeof(date_value_bits));
        }
        else
        {
            llvm::Triple triple(process_sp->GetTarget().GetArchitecture().GetTriple());
            uint32_t delta = (triple.isWatchOS() && triple.isWatchABI()) ? 8 : ptr_size;
            Error error;
            date_value_bits = process_sp->ReadUnsignedIntegerFromMemory(valobj_addr+delta, 8, 0, error);
            memcpy(&date_value, &date_value_bits, sizeof(date_value_bits));
            if (error.Fail())
                return false;
        }
    }
    else if (class_name == g_NSCalendarDate)
    {
        Error error;
        date_value_bits = process_sp->ReadUnsignedIntegerFromMemory(valobj_addr+2*ptr_size, 8, 0, error);
        memcpy(&date_value, &date_value_bits, sizeof(date_value_bits));
        if (error.Fail())
            return false;
    }
    else
        return false;

    if (date_value == -63114076800)
    {
        stream.Printf("0001-12-30 00:00:00 +0000");
        return true;
    }
    // this snippet of code assumes that time_t == seconds since Jan-1-1970
    // this is generally true and POSIXly happy, but might break if a library
    // vendor decides to get creative
    time_t epoch = GetOSXEpoch();
    epoch = epoch + (time_t)date_value;
    tm *tm_date = gmtime(&epoch);
    if (!tm_date)
        return false;
    std::string buffer(1024,0);
    if (strftime (&buffer[0], 1023, "%Z", tm_date) == 0)
        return false;
    stream.Printf("%04d-%02d-%02d %02d:%02d:%02d %s", tm_date->tm_year+1900, tm_date->tm_mon+1, tm_date->tm_mday, tm_date->tm_hour, tm_date->tm_min, tm_date->tm_sec, buffer.c_str());
    return true;
}