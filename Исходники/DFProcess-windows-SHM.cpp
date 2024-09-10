bool SHMProcess::Private::validate(vector <VersionInfo *> & known_versions)
{
    // try to identify the DF version
    IMAGE_NT_HEADERS32 pe_header;
    IMAGE_SECTION_HEADER sections[16];
    HMODULE hmod = NULL;
    DWORD junk;
    HANDLE hProcess;
    bool found = false;
    identified = false;
    // open process, we only need the process open
    hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, process_ID );
    if (NULL == hProcess)
        return false;

    // try getting the first module of the process
    if(EnumProcessModules(hProcess, &hmod, 1 * sizeof(HMODULE), &junk) == 0)
    {
        CloseHandle(hProcess);
        // cout << "EnumProcessModules fail'd" << endl;
        return false;
    }
    // got base ;)
    uint32_t base = (uint32_t)hmod;

    // read from this process
    uint32_t pe_offset = self->readDWord(base+0x3C);
    self->read(base + pe_offset                   , sizeof(pe_header), (uint8_t *)&pe_header);
    self->read(base + pe_offset+ sizeof(pe_header), sizeof(sections) , (uint8_t *)&sections );

    // iterate over the list of memory locations
    vector<VersionInfo *>::iterator it;
    for ( it=known_versions.begin() ; it < known_versions.end(); it++ )
    {
        uint32_t pe_timestamp;
        try
        {
            pe_timestamp = (*it)->getPE();
        }
        catch(Error::MissingMemoryDefinition&)
        {
            continue;
        }
        if (pe_timestamp == pe_header.FileHeader.TimeDateStamp)
        {
            VersionInfo *m = new VersionInfo(**it);
            m->RebaseAll(base);
            memdescriptor = m;
            m->setParentProcess(self);
            identified = true;
            cerr << "identified " << m->getVersion() << endl;
            CloseHandle(hProcess);
            return true;
        }
    }
    return false;
}