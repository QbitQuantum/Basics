SymTableNodePtr ABLModule::findFunction(PSTR functionName, bool searchLibraries)
{
    SymTableNodePtr symbol = searchSymTableForFunction(functionName, ModuleRegistry[handle].moduleIdPtr->defn.info.routine.localSymTable);
    if(!symbol && searchLibraries)
    {
        for(size_t i = 0; i < ModuleRegistry[handle].numLibrariesUsed; i++)
        {
            char temp[1024];
            memset(temp, 0, 1024);
            strncpy(temp, functionName, (strlen(functionName) > 1020) ? 1020 : strlen(functionName));
            symbol = searchSymTable(_strlwr(temp), ModuleRegistry[ModuleRegistry[handle].librariesUsed[i]->handle].moduleIdPtr->defn.info.routine.localSymTable);
            if(symbol)
                break;
        }
    }
    return(symbol);
}