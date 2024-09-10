lldb::ValueObjectSP
lldb_private::formatters::LibcxxStdListSyntheticFrontEnd::GetChildAtIndex (size_t idx)
{
    if (idx >= CalculateNumChildren())
        return lldb::ValueObjectSP();
    
    if (!m_head || !m_tail || m_node_address == 0)
        return lldb::ValueObjectSP();
    
    auto cached = m_children.find(idx);
    if (cached != m_children.end())
        return cached->second;
    
    if (m_loop_detected <= idx)
        if (HasLoop(idx))
            return lldb::ValueObjectSP();
        
    ListIterator current(m_head);
    ValueObjectSP current_sp(current.advance(idx));
    if (!current_sp)
        return lldb::ValueObjectSP();
    current_sp = current_sp->GetChildMemberWithName(ConstString("__value_"), true);
    if (!current_sp)
        return lldb::ValueObjectSP();
    // we need to copy current_sp into a new object otherwise we will end up with all items named __value_
    DataExtractor data;
    Error error;
    current_sp->GetData(data, error);
    if (error.Fail())
        return lldb::ValueObjectSP();
    
    StreamString name;
    name.Printf("[%" PRIu64 "]", (uint64_t)idx);
    return (m_children[idx] = ValueObject::CreateValueObjectFromData(name.GetData(), data, m_backend.GetExecutionContextRef(), m_element_type));
}