bool
lldb_private::formatters::VectorTypeSummaryProvider (ValueObject& valobj,
                                                     Stream& s,
                                                     const TypeSummaryOptions&)
{
    auto synthetic_children = VectorTypeSyntheticFrontEndCreator(nullptr, valobj.GetSP());
    if (!synthetic_children)
        return false;
    
    synthetic_children->Update();
    
    s.PutChar('(');
    bool first = true;
    
    size_t idx = 0, len = synthetic_children->CalculateNumChildren();
    
    for (;
         idx < len;
         idx++)
    {
        auto child_sp = synthetic_children->GetChildAtIndex(idx);
        if (!child_sp)
            continue;
        child_sp = child_sp->GetQualifiedRepresentationIfAvailable(lldb::eDynamicDontRunTarget, true);
        
        const char* child_value = child_sp->GetValueAsCString();
        if (child_value && *child_value)
        {
            if (first)
            {
                s.Printf("%s", child_value);
                first = false;
            }
            else
            {
                s.Printf(", %s", child_value);
            }
        }
    }
    
    s.PutChar(')');
    
    return true;
}