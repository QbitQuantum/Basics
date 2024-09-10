bool
DWARFMappedHash::MemoryTable::ReadHashData (uint32_t hash_data_offset, HashData &hash_data) const
{
    lldb::offset_t offset = hash_data_offset;
    offset += 4; // Skip string table offset that contains offset of hash name in .debug_str
    const uint32_t count = m_data.GetU32 (&offset);
    if (count > 0)
    {
        hash_data.resize(count);
        for (uint32_t i=0; i<count; ++i)
        {
            if (!m_header.Read(m_data, &offset, hash_data[i]))
                return false;
        }
    }
    else
        hash_data.clear();
    return true;
}