void tweakbukconv::Init(std::string configfile)
{
    reader = new ConfigReader();
    groups = new Groups();
    users = new Users();
    if (reader->ReadFile(configfile))
    {
        std::cout << "W00p config is gelezen \\o/" << std::endl;
    }
    else
    {
        std::cout << "Kon niet lezen :/" << std::endl;
    }

    std::string loadmodsstr;
    loadmodsstr = reader->GetString("loadmods");
    moduledir = reader->GetString("moduledir");
    hostname_str = reader->GetString("hostname");
    databasename_str = reader->GetString("databasename");
    username_str = reader->GetString("username");
    pass_str = reader->GetString("password");
	GetGroupsDB();
    std::vector< std::string > loadmods;
    boost::split( loadmods, loadmodsstr, boost::is_any_of(" "), boost::token_compress_on );
    for (unsigned int i = 0; i < loadmods.size(); i++)
    {
        LoadModule(loadmods[i]);
    }
    tweakloop = true;
    assert(!tweak_thread);
    tweak_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&tweakbukconv::tweakrun, this)));
}