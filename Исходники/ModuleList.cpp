void
ModuleList::LogUUIDAndPaths (LogSP &log_sp, const char *prefix_cstr)
{
    if (log_sp)
    {   
        Mutex::Locker locker(m_modules_mutex);
        char uuid_cstr[256];
        collection::const_iterator pos, begin = m_modules.begin(), end = m_modules.end();
        for (pos = begin; pos != end; ++pos)
        {
            Module *module = pos->get();
            module->GetUUID().GetAsCString (uuid_cstr, sizeof(uuid_cstr));
            const FileSpec &module_file_spec = module->GetFileSpec();
            log_sp->Printf ("%s[%u] %s (%s) \"%s/%s\"", 
                            prefix_cstr ? prefix_cstr : "",
                            (uint32_t)std::distance (begin, pos),
                            uuid_cstr,
                            module->GetArchitecture().GetArchitectureName(),
                            module_file_spec.GetDirectory().GetCString(),
                            module_file_spec.GetFilename().GetCString());
        }
    }
}