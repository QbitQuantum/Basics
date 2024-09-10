long Cx_StringTable::RegisterFile(const std::wstring& filename)
{
    Cx_Interface<Ix_ConfigXml> pIFFile(x3::CLSID_ConfigXmlFile);
    if (pIFFile.IsNull())
    {
        return 0;
    }

    pIFFile->SetFileName(filename.c_str());
    X3LOG_DEBUG2(L"@StringTable:IDS_LOAD_STRFILE", PathFindFileNameW(filename.c_str()));

    long count = 0;
    for (int i = 0; i < 99; i++)
    {
        Cx_ConfigSection sec (pIFFile->GetData()->GetSectionByIndex(NULL, L"module", i));
        ITEM item;

        item.file = pIFFile->GetData();
        item.group = sec;
        item.module = sec->GetString(L"name");
        ASSERT(item.group && item.file);

        if (item.module.empty())
            break;

        if (Find(item.module) == m_groups.end())
        {
            m_groups.push_back(item);
            count++;
        }
        else
        {
            X3LOG_WARNING2(L"@StringTable:IDS_IGNORE_STRGROUP", item.module);
        }
    }

    return count;
}