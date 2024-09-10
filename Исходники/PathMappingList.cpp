bool
PathMappingList::FindFile (const FileSpec &orig_spec, FileSpec &new_spec) const
{
    if (!m_pairs.empty())
    {
        char orig_path[PATH_MAX];
        char new_path[PATH_MAX];
        const size_t orig_path_len = orig_spec.GetPath (orig_path, sizeof(orig_path));
        if (orig_path_len > 0)
        {
            const_iterator pos, end = m_pairs.end();
            for (pos = m_pairs.begin(); pos != end; ++pos)
            {
                const size_t prefix_len = pos->first.GetLength();
                
                if (orig_path_len >= prefix_len)
                {
                    if (::strncmp (pos->first.GetCString(), orig_path, prefix_len) == 0)
                    {
                        const size_t new_path_len = snprintf(new_path, sizeof(new_path), "%s/%s", pos->second.GetCString(), orig_path + prefix_len);
                        if (new_path_len < sizeof(new_path))
                        {
                            new_spec.SetFile (new_path, true);
                            if (new_spec.Exists())
                                return true;
                        }
                    }
                }
            }
        }
    }
    new_spec.Clear();
    return false;
}