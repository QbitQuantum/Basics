OCIOColorSpace::OCIOColorSpace(Node *n) : DD::Image::PixelIop(n)
{
    m_hasColorSpaces = false;

    m_inputColorSpaceIndex = 0;
    m_outputColorSpaceIndex = 0;

    m_layersToProcess = DD::Image::Mask_RGB;

    
    // Query the colorspace names from the current config
    // TODO (when to) re-grab the list of available colorspaces? How to save/load?
    
    try
    {
        OCIO::ConstConfigRcPtr config = OCIO::GetCurrentConfig();
        std::string defaultColorSpaceName = config->getColorSpace(OCIO::ROLE_SCENE_LINEAR)->getName();
        
        for(int i = 0; i < config->getNumColorSpaces(); i++)
        {
            std::string csname = config->getColorSpaceNameByIndex(i);
            m_colorSpaceNames.push_back(csname);
            
            if(csname == defaultColorSpaceName)
            {
                m_inputColorSpaceIndex = i;
                m_outputColorSpaceIndex = i;
            }
        }
    }
    catch (OCIO::Exception& e)
    {
        std::cerr << "OCIOColorSpace: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "OCIOColorSpace: Unknown exception during OCIO setup." << std::endl;
    }
    
    // Then, create a cstr array for passing to Nuke
    // This must be done in a second pass, lest the original m_colorSpaceNames
    // std::string be reallocated in the interim
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
        std::cerr << "OCIOColorSpace: No ColorSpaces available for input and/or output." << std::endl;
    }
}