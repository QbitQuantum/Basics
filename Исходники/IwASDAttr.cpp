//--------------------------------------------------------------------------------
wxString CIwASDFileDataAttr::Group::MakeAbsolute(const wxString& fileName)
{
    wxString name2;
    if (fileName.length()>=2 && fileName[0]=='.' && (fileName[1]=='\\' || fileName[1]=='/'))
        name2=m_Parent->m_File->m_Paths[0]->m_Parent->c_str();
    else if (m_Parent->m_File->m_Paths[0]->GetRoot()!=NULL)
        name2=m_Parent->m_File->m_Paths[0]->GetRoot()->c_str();

    if (name2.EndsWith(L"\\") || name2.EndsWith(L"/"))
        name2.RemoveLast();

    if (fileName.length()>=2 && fileName[0]=='.' && (fileName[1]=='\\' || fileName[1]=='/'))
        name2+=fileName.Mid(1);
    else
    {
        if (fileName[0]!='\\' && fileName[1]!='/')
            name2+=L"/";

        name2+=fileName;
    }

    return name2;
}