bool
lldb_private::formatters::NSSetSummaryProvider (ValueObject& valobj, Stream& stream, const TypeSummaryOptions& options)
{
    static ConstString g_TypeHint("NSSet");
    
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
    bool is_64bit = (ptr_size == 8);
    
    lldb::addr_t valobj_addr = valobj.GetValueAsUnsigned(0);
    
    if (!valobj_addr)
        return false;
    
    uint64_t value = 0;
    
    ConstString class_name_cs = descriptor->GetClassName();
    const char* class_name = class_name_cs.GetCString();
    
    if (!class_name || !*class_name)
        return false;
    
    if (!strcmp(class_name,"__NSSetI"))
    {
        Error error;
        value = process_sp->ReadUnsignedIntegerFromMemory(valobj_addr + ptr_size, ptr_size, 0, error);
        if (error.Fail())
            return false;
        value &= (is_64bit ? ~0xFC00000000000000UL : ~0xFC000000U);
    }
    else if (!strcmp(class_name,"__NSSetM"))
    {
        Error error;
        value = process_sp->ReadUnsignedIntegerFromMemory(valobj_addr + ptr_size, ptr_size, 0, error);
        if (error.Fail())
            return false;
        value &= (is_64bit ? ~0xFC00000000000000UL : ~0xFC000000U);
    }
    /*else if (!strcmp(class_name,"__NSCFSet"))
     {
     Error error;
     value = process_sp->ReadUnsignedIntegerFromMemory(valobj_addr + (is_64bit ? 20 : 12), 4, 0, error);
     if (error.Fail())
     return false;
     if (is_64bit)
     value &= ~0x1fff000000000000UL;
     }
     else if (!strcmp(class_name,"NSCountedSet"))
     {
     Error error;
     value = process_sp->ReadUnsignedIntegerFromMemory(valobj_addr + ptr_size, ptr_size, 0, error);
     if (error.Fail())
     return false;
     value = process_sp->ReadUnsignedIntegerFromMemory(value + (is_64bit ? 20 : 12), 4, 0, error);
     if (error.Fail())
     return false;
     if (is_64bit)
     value &= ~0x1fff000000000000UL;
     }*/
    else
    {
        auto& map(NSSet_Additionals::GetAdditionalSummaries());
        auto iter = map.find(class_name_cs), end = map.end();
        if (iter != end)
            return iter->second(valobj, stream, options);
        else
            return false;
    }
    
    std::string prefix,suffix;
    if (Language* language = Language::FindPlugin(options.GetLanguage()))
    {
        if (!language->GetFormatterPrefixSuffix(valobj, g_TypeHint, prefix, suffix))
        {
            prefix.clear();
            suffix.clear();
        }
    }
    
    stream.Printf("%s%" PRIu64 " %s%s%s",
                  prefix.c_str(),
                  value,
                  "element",
                  value == 1 ? "" : "s",
                  suffix.c_str());
    return true;
}