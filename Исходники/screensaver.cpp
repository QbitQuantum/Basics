void CScreensaver::GetDefaultDisplayPeriods(struct ss_periods &periods)
{
    char*           default_data_dir_path = NULL;
    char            buf[1024];
    FILE*           f;
    MIOFILE         mf;

    periods.GFXDefaultPeriod = GFX_DEFAULT_PERIOD;
    periods.GFXSciencePeriod = GFX_SCIENCE_PERIOD;
    periods.GFXChangePeriod = GFX_CHANGE_PERIOD;
    periods.Show_default_ss_first = false;

#ifdef __APPLE__
    default_data_dir_path = "/Library/Application Support/BOINC Data";
#else
    default_data_dir_path = (char*)m_strBOINCDataDirectory.c_str();
#endif

    strlcpy(buf, default_data_dir_path, sizeof(buf));
    strlcat(buf, PATH_SEPARATOR, sizeof(buf));
    strlcat(buf, THE_SS_CONFIG_FILE, sizeof(buf));

    f = boinc_fopen(buf, "r");
    if (!f) return;
    
    mf.init_file(f);
    XML_PARSER xp(&mf);

    while (mf.fgets(buf, sizeof(buf))) {
        if (parse_bool(buf, "default_ss_first", periods.Show_default_ss_first)) continue;
        if (parse_double(buf, "<default_gfx_duration>", periods.GFXDefaultPeriod)) continue;
        if (parse_double(buf, "<science_gfx_duration>", periods.GFXSciencePeriod)) continue;
        if (parse_double(buf, "<science_gfx_change_interval>", periods.GFXChangePeriod)) continue;
        
    }
    fclose(f);
    
    BOINCTRACE(_T("CScreensaver::GetDefaultDisplayPeriods: m_bShow_default_ss_first=%d, m_fGFXDefaultPeriod=%f, m_fGFXSciencePeriod=%f, m_fGFXChangePeriod=%f\n"),
                    (int)periods.Show_default_ss_first, periods.GFXDefaultPeriod, periods.GFXSciencePeriod, periods.GFXChangePeriod);
}