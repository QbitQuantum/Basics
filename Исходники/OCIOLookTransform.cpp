OCIOLookTransform::OCIOLookTransform(Node *n) : DD::Image::PixelIop(n)
{
    m_hasColorSpaces = false;

    m_inputColorSpaceIndex = 0;
    m_outputColorSpaceIndex = 0;
    m_lookIndex = 0;
    m_dirIndex = 0;
    m_ignoreErrors = false;
    
    // Query the colorspace names from the current config
    // TODO (when to) re-grab the list of available colorspaces? How to save/load?
    
    OCIO::ConstConfigRcPtr config;
    std::string linear;
    
    try
    {
        config = OCIO::GetCurrentConfig();
        
        OCIO::ConstColorSpaceRcPtr linearcs = config->getColorSpace(OCIO::ROLE_SCENE_LINEAR);
        if(!linearcs) throw std::runtime_error("ROLE_SCENE_LINEAR not defined.");
        linear = linearcs->getName();
    }
    catch (const OCIO::Exception& e)
    {
        std::cerr << "OCIOLookTransform: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "OCIOLookTransform: Unknown exception during OCIO setup." << std::endl;
    }
    
    if(!config)
    {
        m_hasColorSpaces = false;
        return;
    }
    
    // Step 1: Make the std::vectors
    for(int i=0; i<config->getNumLooks(); ++i)
    {
        m_lookNames.push_back(config->getLookNameByIndex(i));
    }
    
    for(int i = 0; i < config->getNumColorSpaces(); i++)
    {
        std::string csname = config->getColorSpaceNameByIndex(i);
        
#ifdef OCIO_CASCADE
            std::string family = config->getColorSpace(csname.c_str())->getFamily();
            if(family.empty())
                m_colorSpaceNames.push_back(csname.c_str());
            else
                m_colorSpaceNames.push_back(family + "/" + csname);
#else
            m_colorSpaceNames.push_back(csname);
#endif
        if(csname == linear)
        {
            m_inputColorSpaceIndex = i;
            m_outputColorSpaceIndex = i;
        }
    }
    
    
    // Step 2: Create a cstr array for passing to Nuke
    // (This must be done in a second pass, lest the original strings be reallocated)
    
    for(unsigned int i=0; i<m_lookNames.size(); ++i)
    {
        m_lookCstrNames.push_back(m_lookNames[i].c_str());
    }
    m_lookCstrNames.push_back(NULL);
    
    for(unsigned int i=0; i<m_colorSpaceNames.size(); ++i)
    {
        m_inputColorSpaceCstrNames.push_back(m_colorSpaceNames[i].c_str());
        m_outputColorSpaceCstrNames.push_back(m_colorSpaceNames[i].c_str());
    }
    
    m_inputColorSpaceCstrNames.push_back(NULL);
    m_outputColorSpaceCstrNames.push_back(NULL);
    
    
    
    
    
    m_hasColorSpaces = (!m_colorSpaceNames.empty());
    
    if(!m_hasColorSpaces)
    {
        std::cerr << "OCIOLookTransform: No ColorSpaces available for input and/or output." << std::endl;
    }
}