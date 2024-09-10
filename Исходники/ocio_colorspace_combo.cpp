void ocio_colorspace_combo_t::set_default()
{
    OCIO::ConstConfigRcPtr config = app().ocio_manager().config();
    std::string default_cs_name = config->getColorSpace( OCIO::ROLE_SCENE_LINEAR)->getName();

    int index = 0;
    int num_color_spaces = config->getNumColorSpaces();

    for(int i = 0; i < num_color_spaces; i++)
    {
        if( config->getColorSpaceNameByIndex( i) == default_cs_name)
            index = i;
    }

    setCurrentIndex( index);
    current_colorspace_ = default_cs_name;
}