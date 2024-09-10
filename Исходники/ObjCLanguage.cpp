size_t
ObjCLanguage::MethodName::GetFullNames (std::vector<ConstString> &names, bool append)
{
    if (!append)
        names.clear();
    if (IsValid(false))
    {
        StreamString strm;
        const bool is_class_method = m_type == eTypeClassMethod;
        const bool is_instance_method = m_type == eTypeInstanceMethod;
        const ConstString &category = GetCategory();
        if (is_class_method || is_instance_method)
        {
            names.push_back (m_full);
            if (category)
            {
                strm.Printf("%c[%s %s]",
                            is_class_method ? '+' : '-',
                            GetClassName().GetCString(),
                            GetSelector().GetCString());
                names.push_back(ConstString(strm.GetString().c_str()));
            }
        }
        else
        {
            const ConstString &class_name = GetClassName();
            const ConstString &selector = GetSelector();
            strm.Printf("+[%s %s]", class_name.GetCString(), selector.GetCString());
            names.push_back(ConstString(strm.GetString().c_str()));
            strm.Clear();
            strm.Printf("-[%s %s]", class_name.GetCString(), selector.GetCString());
            names.push_back(ConstString(strm.GetString().c_str()));
            strm.Clear();
            if (category)
            {
                strm.Printf("+[%s(%s) %s]", class_name.GetCString(), category.GetCString(), selector.GetCString());
                names.push_back(ConstString(strm.GetString().c_str()));
                strm.Clear();
                strm.Printf("-[%s(%s) %s]", class_name.GetCString(), category.GetCString(), selector.GetCString());
                names.push_back(ConstString(strm.GetString().c_str()));
            }
        }
    }
    return names.size();
}