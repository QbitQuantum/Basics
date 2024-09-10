void CAdvancedSettings::ParseSettingsFile(const CStdString &file)
{
  TiXmlDocument advancedXML;
  if (!CFile::Exists(file))
  {
    CLog::Log(LOGNOTICE, "No settings file to load (%s)", file.c_str());
    return;
  }

  if (!advancedXML.LoadFile(file))
  {
    CLog::Log(LOGERROR, "Error loading %s, Line %d\n%s", file.c_str(), advancedXML.ErrorRow(), advancedXML.ErrorDesc());
    return;
  }

  TiXmlElement *pRootElement = advancedXML.RootElement();
  if (!pRootElement || strcmpi(pRootElement->Value(),"advancedsettings") != 0)
  {
    CLog::Log(LOGERROR, "Error loading %s, no <advancedsettings> node", file.c_str());
    return;
  }

  // succeeded - tell the user it worked
  CLog::Log(LOGNOTICE, "Loaded settings file from %s", file.c_str());

  // Dump contents of AS.xml to debug log
  TiXmlPrinter printer;
  printer.SetLineBreak("\n");
  printer.SetIndent("  ");
  advancedXML.Accept(&printer);
  CLog::Log(LOGNOTICE, "Contents of %s are...\n%s", file.c_str(), printer.CStr());

  TiXmlElement *pElement = pRootElement->FirstChildElement("audio");
  if (pElement)
  {
    XMLUtils::GetFloat(pElement, "ac3downmixgain", m_ac3Gain, -96.0f, 96.0f);
    XMLUtils::GetInt(pElement, "headroom", m_audioHeadRoom, 0, 12);
    XMLUtils::GetString(pElement, "defaultplayer", m_audioDefaultPlayer);
    // 101 on purpose - can be used to never automark as watched
    XMLUtils::GetFloat(pElement, "playcountminimumpercent", m_audioPlayCountMinimumPercent, 0.0f, 101.0f);

    XMLUtils::GetBoolean(pElement, "usetimeseeking", m_musicUseTimeSeeking);
    XMLUtils::GetInt(pElement, "timeseekforward", m_musicTimeSeekForward, 0, 6000);
    XMLUtils::GetInt(pElement, "timeseekbackward", m_musicTimeSeekBackward, -6000, 0);
    XMLUtils::GetInt(pElement, "timeseekforwardbig", m_musicTimeSeekForwardBig, 0, 6000);
    XMLUtils::GetInt(pElement, "timeseekbackwardbig", m_musicTimeSeekBackwardBig, -6000, 0);

    XMLUtils::GetInt(pElement, "percentseekforward", m_musicPercentSeekForward, 0, 100);
    XMLUtils::GetInt(pElement, "percentseekbackward", m_musicPercentSeekBackward, -100, 0);
    XMLUtils::GetInt(pElement, "percentseekforwardbig", m_musicPercentSeekForwardBig, 0, 100);
    XMLUtils::GetInt(pElement, "percentseekbackwardbig", m_musicPercentSeekBackwardBig, -100, 0);

    XMLUtils::GetInt(pElement, "resample", m_musicResample, 0, 192000);

    TiXmlElement* pAudioExcludes = pElement->FirstChildElement("excludefromlisting");
    if (pAudioExcludes)
      GetCustomRegexps(pAudioExcludes, m_audioExcludeFromListingRegExps);

    pAudioExcludes = pElement->FirstChildElement("excludefromscan");
    if (pAudioExcludes)
      GetCustomRegexps(pAudioExcludes, m_audioExcludeFromScanRegExps);

    XMLUtils::GetString(pElement, "audiohost", m_audioHost);
    XMLUtils::GetBoolean(pElement, "applydrc", m_audioApplyDrc);
    XMLUtils::GetBoolean(pElement, "dvdplayerignoredtsinwav", m_dvdplayerIgnoreDTSinWAV);

    XMLUtils::GetFloat(pElement, "limiterhold", m_limiterHold, 0.0f, 100.0f);
    XMLUtils::GetFloat(pElement, "limiterrelease", m_limiterRelease, 0.001f, 100.0f);
  }

  pElement = pRootElement->FirstChildElement("karaoke");
  if (pElement)
  {
    XMLUtils::GetFloat(pElement, "syncdelaycdg", m_karaokeSyncDelayCDG, -3.0f, 3.0f); // keep the old name for comp
    XMLUtils::GetFloat(pElement, "syncdelaylrc", m_karaokeSyncDelayLRC, -3.0f, 3.0f);
    XMLUtils::GetBoolean(pElement, "alwaysreplacegenre", m_karaokeChangeGenreForKaraokeSongs );
    XMLUtils::GetBoolean(pElement, "storedelay", m_karaokeKeepDelay );
    XMLUtils::GetInt(pElement, "autoassignstartfrom", m_karaokeStartIndex, 1, 2000000000);
    XMLUtils::GetBoolean(pElement, "nocdgbackground", m_karaokeAlwaysEmptyOnCdgs );
    XMLUtils::GetBoolean(pElement, "lookupsongbackground", m_karaokeUseSongSpecificBackground );

    TiXmlElement* pKaraokeBackground = pElement->FirstChildElement("defaultbackground");
    if (pKaraokeBackground)
    {
      const char* attr = pKaraokeBackground->Attribute("type");
      if ( attr )
        m_karaokeDefaultBackgroundType = attr;

      attr = pKaraokeBackground->Attribute("path");
      if ( attr )
        m_karaokeDefaultBackgroundFilePath = attr;
    }
  }

  pElement = pRootElement->FirstChildElement("video");
  if (pElement)
  {
    XMLUtils::GetFloat(pElement, "subsdelayrange", m_videoSubsDelayRange, 10, 600);
    XMLUtils::GetFloat(pElement, "audiodelayrange", m_videoAudioDelayRange, 10, 600);
    XMLUtils::GetInt(pElement, "blackbarcolour", m_videoBlackBarColour, 0, 255);
    XMLUtils::GetString(pElement, "defaultplayer", m_videoDefaultPlayer);
    XMLUtils::GetString(pElement, "defaultdvdplayer", m_videoDefaultDVDPlayer);
    XMLUtils::GetBoolean(pElement, "fullscreenonmoviestart", m_fullScreenOnMovieStart);
    // 101 on purpose - can be used to never automark as watched
    XMLUtils::GetFloat(pElement, "playcountminimumpercent", m_videoPlayCountMinimumPercent, 0.0f, 101.0f);
    XMLUtils::GetInt(pElement, "ignoresecondsatstart", m_videoIgnoreSecondsAtStart, 0, 900);
    XMLUtils::GetFloat(pElement, "ignorepercentatend", m_videoIgnorePercentAtEnd, 0, 100.0f);

    XMLUtils::GetInt(pElement, "smallstepbackseconds", m_videoSmallStepBackSeconds, 1, INT_MAX);
    XMLUtils::GetInt(pElement, "smallstepbacktries", m_videoSmallStepBackTries, 1, 10);
    XMLUtils::GetInt(pElement, "smallstepbackdelay", m_videoSmallStepBackDelay, 100, 5000); //MS

    XMLUtils::GetBoolean(pElement, "usetimeseeking", m_videoUseTimeSeeking);
    XMLUtils::GetInt(pElement, "timeseekforward", m_videoTimeSeekForward, 0, 6000);
    XMLUtils::GetInt(pElement, "timeseekbackward", m_videoTimeSeekBackward, -6000, 0);
    XMLUtils::GetInt(pElement, "timeseekforwardbig", m_videoTimeSeekForwardBig, 0, 6000);
    XMLUtils::GetInt(pElement, "timeseekbackwardbig", m_videoTimeSeekBackwardBig, -6000, 0);

    XMLUtils::GetInt(pElement, "percentseekforward", m_videoPercentSeekForward, 0, 100);
    XMLUtils::GetInt(pElement, "percentseekbackward", m_videoPercentSeekBackward, -100, 0);
    XMLUtils::GetInt(pElement, "percentseekforwardbig", m_videoPercentSeekForwardBig, 0, 100);
    XMLUtils::GetInt(pElement, "percentseekbackwardbig", m_videoPercentSeekBackwardBig, -100, 0);

    TiXmlElement* pVideoExcludes = pElement->FirstChildElement("excludefromlisting");
    if (pVideoExcludes)
      GetCustomRegexps(pVideoExcludes, m_videoExcludeFromListingRegExps);

    pVideoExcludes = pElement->FirstChildElement("excludefromscan");
    if (pVideoExcludes)
      GetCustomRegexps(pVideoExcludes, m_moviesExcludeFromScanRegExps);

    pVideoExcludes = pElement->FirstChildElement("excludetvshowsfromscan");
    if (pVideoExcludes)
      GetCustomRegexps(pVideoExcludes, m_tvshowExcludeFromScanRegExps);

    pVideoExcludes = pElement->FirstChildElement("cleanstrings");
    if (pVideoExcludes)
      GetCustomRegexps(pVideoExcludes, m_videoCleanStringRegExps);

    XMLUtils::GetString(pElement,"cleandatetime", m_videoCleanDateTimeRegExp);
    XMLUtils::GetString(pElement,"ppffmpegdeinterlacing",m_videoPPFFmpegDeint);
    XMLUtils::GetString(pElement,"ppffmpegpostprocessing",m_videoPPFFmpegPostProc);
    XMLUtils::GetBoolean(pElement,"vdpauscaling",m_videoVDPAUScaling);
    XMLUtils::GetFloat(pElement, "nonlinearstretchratio", m_videoNonLinStretchRatio, 0.01f, 1.0f);
    XMLUtils::GetBoolean(pElement,"enablehighqualityhwscalers", m_videoEnableHighQualityHwScalers);
    XMLUtils::GetFloat(pElement,"autoscalemaxfps",m_videoAutoScaleMaxFps, 0.0f, 1000.0f);
    XMLUtils::GetBoolean(pElement,"allowmpeg4vdpau",m_videoAllowMpeg4VDPAU);
    XMLUtils::GetBoolean(pElement,"allowmpeg4vaapi",m_videoAllowMpeg4VAAPI);    
    XMLUtils::GetBoolean(pElement, "disablebackgrounddeinterlace", m_videoDisableBackgroundDeinterlace);
    XMLUtils::GetInt(pElement, "useocclusionquery", m_videoCaptureUseOcclusionQuery, -1, 1);

    TiXmlElement* pAdjustRefreshrate = pElement->FirstChildElement("adjustrefreshrate");
    if (pAdjustRefreshrate)
    {
      TiXmlElement* pRefreshOverride = pAdjustRefreshrate->FirstChildElement("override");
      while (pRefreshOverride)
      {
        RefreshOverride override = {0};

        float fps;
        if (XMLUtils::GetFloat(pRefreshOverride, "fps", fps))
        {
          override.fpsmin = fps - 0.01f;
          override.fpsmax = fps + 0.01f;
        }

        float fpsmin, fpsmax;
        if (XMLUtils::GetFloat(pRefreshOverride, "fpsmin", fpsmin) &&
            XMLUtils::GetFloat(pRefreshOverride, "fpsmax", fpsmax))
        {
          override.fpsmin = fpsmin;
          override.fpsmax = fpsmax;
        }

        float refresh;
        if (XMLUtils::GetFloat(pRefreshOverride, "refresh", refresh))
        {
          override.refreshmin = refresh - 0.01f;
          override.refreshmax = refresh + 0.01f;