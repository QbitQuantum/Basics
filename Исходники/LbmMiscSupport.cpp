// ////////////////////////////////////////////////////////////////////////////
bool GetLbmConfigFileFromCmdLine(unsigned int &current_index, int argc,
                                 char **argv, std::string &out_datum, bool require_existence)
{
    std::string tmp_datum;

    if (!MLB::Utility::ParseCmdLineArg::ParseCmdLineFollowingSpec(
                MLB::Utility::MakeInlineVector<std::string>
                ("-LBM_CONFIGURATION_FILE")
                ("-LBM_CONFIGURATIONFILE")
                ("-LBMCONFIGURATION_FILE")
                ("-LBMCONFIGURATIONFILE")
                ("-LBM_CONFIG_FILE")
                ("-LBM_CONFIGFILE")
                ("-LBMCONFIG_FILE")
                ("-LBMCONFIGFILE")
                ("-LBM_CFG_FILE")
                ("-LBM_CFGFILE")
                ("-LBMCFG_FILE")
                ("-LBMCFGFILE")
                ("-LBM_CONFIGURATION")
                ("-LBMCONFIGURATION")
                ("-LBM_CONFIG")
                ("-LBMCONFIG")
                ("-LBM_CFG")
                ("-LBMCFG"),
                current_index, argc, argv, tmp_datum))
        return(false);

    MLB::Utility::ParseCmdLineArg::CheckFilePath("LBM configuration file name",
            tmp_datum, "", require_existence);

    out_datum.swap(tmp_datum);

    return(true);
}