RbHelpParser::HelpEntryType RbHelpParser::testHelpEntry(const std::string &fn)
{
    // first we need to load the file
    std::ifstream readStream;
    RbFileManager fm = RbFileManager(fn);
    fm.openFile( readStream );
    
    // try to load the xml file
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(fn.c_str(), pugi::parse_default);
    if (result.status != pugi::status_ok)
    {
        std::cerr << "Problem while parsing file " << fn << std::endl;
        throw RbException( result.description() );
    }
    
    pugi::xpath_node_set nodeSet = doc.select_nodes("//function-help-entry");
    if ( nodeSet.size() > 0 )
    {
        return FUNCTION;
    }
    
    nodeSet = doc.select_nodes("//type-help-entry");
    if ( nodeSet.size() > 0 )
    {
        return TYPE;
    }
    
    nodeSet = doc.select_nodes("//distribution-help-entry");
    if ( nodeSet.size() > 0 )
    {
        return DISTRIBUTION;
    }
    
    nodeSet = doc.select_nodes("//move-help-entry");
    if ( nodeSet.size() > 0 )
    {
        return MOVE;
    }
    
    nodeSet = doc.select_nodes("//monitor-help-entry");
    if ( nodeSet.size() > 0 )
    {
        return MONITOR;
    }
    
    
    throw RbException("Unknown help entry type in file '" + fn + "'.");

}