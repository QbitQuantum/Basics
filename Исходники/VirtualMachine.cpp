	Module* VirtualMachine::LoadModule(const ModuleName &name, bool noreflection, bool debug, Module *hint)
	{
        // Check for an already loaded module.
        // TODO: Add security.
        LoadedModulesByName::iterator it = loadedModulesByName.find(name.name);
        if(it != loadedModulesByName.end())
            return it->second;

        // Use the filename if present
        if(!name.filename.empty())
    		return LoadModule(name.filename, debug);

        // Try to load the module.
        std::string baseName = name.name + ".cbm";
        std::string fileName;
        if(FindModule(baseName, &fileName, hint))
            return LoadModule(fileName, noreflection, debug);

        // Try to load embedded module.
        // ELF module.
        baseName = "lib" + name.name + ".so";
        if(FindModule(baseName, &fileName, hint))
            return LoadModule(fileName, noreflection, debug);

        // PE module.
        baseName = name.name + ".dll";
        if(FindModule(baseName, &fileName, hint))
            return LoadModule(fileName, noreflection, debug);

        return NULL;
	}