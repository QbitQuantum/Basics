std::string
SyntheticFilter::GetDescription()
{
    StreamString sstr;
    sstr.Printf("%s%s%s {\n",
                m_cascades ? "" : " (not cascading)",
                m_skip_pointers ? " (skip pointers)" : "",
                m_skip_references ? " (skip references)" : "");
    
    for (int i = 0; i < GetCount(); i++)
    {
        sstr.Printf("    %s\n",
                    GetExpressionPathAtIndex(i).c_str());
    }
                    
    sstr.Printf("}");
    return sstr.GetString();
}