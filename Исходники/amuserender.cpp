int main(int argc, const boo::SystemChar** argv)
#endif
{
  logvisor::RegisterConsoleLogger();

  std::vector<boo::SystemString> m_args;
  m_args.reserve(argc);
  double rate = NativeSampleRate;
  int chCount = 2;
  double volume = 1.0;
  for (int i = 1; i < argc; ++i) {
#if _WIN32
    if (!wcsncmp(argv[i], L"-r", 2)) {
      if (argv[i][2])
        rate = wcstod(&argv[i][2], nullptr);
      else if (argc > (i + 1)) {
        rate = wcstod(argv[i + 1], nullptr);
        ++i;
      }
    } else if (!wcsncmp(argv[i], L"-c", 2)) {
      if (argv[i][2])
        chCount = wcstoul(&argv[i][2], nullptr, 0);
      else if (argc > (i + 1)) {
        chCount = wcstoul(argv[i + 1], nullptr, 0);
        ++i;
      }
    } else if (!wcsncmp(argv[i], L"-v", 2)) {
      if (argv[i][2])
        volume = wcstod(&argv[i][2], nullptr);
      else if (argc > (i + 1)) {
        volume = wcstod(argv[i + 1], nullptr);
        ++i;
      }
    } else
      m_args.push_back(argv[i]);
#else
    if (!strncmp(argv[i], "-r", 2)) {
      if (argv[i][2])
        rate = strtod(&argv[i][2], nullptr);
      else if (argc > (i + 1)) {
        rate = strtod(argv[i + 1], nullptr);
        ++i;
      }
    } else if (!strncmp(argv[i], "-c", 2)) {
      if (argv[i][2])
        chCount = strtoul(&argv[i][2], nullptr, 0);
      else if (argc > (i + 1)) {
        chCount = strtoul(argv[i + 1], nullptr, 0);
        ++i;
      }
    } else if (!strncmp(argv[i], "-v", 2)) {
      if (argv[i][2])
        volume = strtod(&argv[i][2], nullptr);
      else if (argc > (i + 1)) {
        volume = strtod(argv[i + 1], nullptr);
        ++i;
      }
    } else
      m_args.push_back(argv[i]);
#endif
  }

  /* Load data */
  if (m_args.size() < 1) {
    Log.report(logvisor::Error,
               "Usage: amuserender <group-file> [<songs-file>] [-r <sample-rate>] [-c <channel-count>] [-v <volume "
               "0.0-1.0>]");
    return 1;
  }

  amuse::ContainerRegistry::Type cType = amuse::ContainerRegistry::DetectContainerType(m_args[0].c_str());
  if (cType == amuse::ContainerRegistry::Type::Invalid) {
    Log.report(logvisor::Error, "invalid/no data at path argument");
    return 1;
  }
  Log.report(logvisor::Info, _SYS_STR("Found '%s' Audio Group data"), amuse::ContainerRegistry::TypeToName(cType));

  std::vector<std::pair<amuse::SystemString, amuse::IntrusiveAudioGroupData>> data =
      amuse::ContainerRegistry::LoadContainer(m_args[0].c_str());
  if (data.empty()) {
    Log.report(logvisor::Error, "invalid/no data at path argument");
    return 1;
  }

  int m_groupId = -1;
  int m_setupId = -1;
  const amuse::SystemString* m_groupName = nullptr;
  const amuse::SystemString* m_songName = nullptr;
  amuse::ContainerRegistry::SongData* m_arrData = nullptr;
  bool m_sfxGroup = false;

  std::list<amuse::AudioGroupProject> m_projs;
  std::map<int, std::pair<std::pair<amuse::SystemString, amuse::IntrusiveAudioGroupData>*,
                          amuse::ObjToken<amuse::SongGroupIndex>>>
      allSongGroups;
  std::map<int, std::pair<std::pair<amuse::SystemString, amuse::IntrusiveAudioGroupData>*,
                          amuse::ObjToken<amuse::SFXGroupIndex>>>
      allSFXGroups;
  size_t totalGroups = 0;

  for (auto& grp : data) {
    /* Load project to assemble group list */
    m_projs.push_back(amuse::AudioGroupProject::CreateAudioGroupProject(grp.second));
    amuse::AudioGroupProject& proj = m_projs.back();
    totalGroups += proj.sfxGroups().size() + proj.songGroups().size();

    for (auto it = proj.songGroups().begin(); it != proj.songGroups().end(); ++it)
      allSongGroups[it->first] = std::make_pair(&grp, it->second);

    for (auto it = proj.sfxGroups().begin(); it != proj.sfxGroups().end(); ++it)
      allSFXGroups[it->first] = std::make_pair(&grp, it->second);
  }

  /* Attempt loading song */
  std::vector<std::pair<amuse::SystemString, amuse::ContainerRegistry::SongData>> songs;
  if (m_args.size() > 1)
    songs = amuse::ContainerRegistry::LoadSongs(m_args[1].c_str());
  else
    songs = amuse::ContainerRegistry::LoadSongs(m_args[0].c_str());

  if (songs.size()) {
    bool play = true;
    if (m_args.size() <= 1) {
      bool prompt = true;
      while (true) {
        if (prompt) {
          printf("Render Song? (Y/N): ");
          prompt = false;
        }
        char userSel;
        if (scanf("%c", &userSel) <= 0 || userSel == '\n')
          continue;
        userSel = tolower(userSel);
        if (userSel == 'n')
          play = false;
        else if (userSel != 'y') {
          prompt = true;
          continue;
        }
        break;
      }
    }

    if (play) {
      /* Get song selection from user */
      if (songs.size() > 1) {
        /* Ask user to specify which song */
        printf("Multiple Songs discovered:\n");
        int idx = 0;
        for (const auto& pair : songs) {
          const amuse::ContainerRegistry::SongData& sngData = pair.second;
          int16_t grpId = sngData.m_groupId;
          int16_t setupId = sngData.m_setupId;
          if (sngData.m_groupId == -1 && sngData.m_setupId != -1) {
            for (const auto& pair : allSongGroups) {
              for (const auto& setup : pair.second.second->m_midiSetups) {
                if (setup.first == sngData.m_setupId) {
                  grpId = pair.first;
                  break;
                }
              }
              if (grpId != -1)
                break;
            }
          }
          amuse::Printf(_SYS_STR("    %d %s (Group %d, Setup %d)\n"), idx++, pair.first.c_str(), grpId, setupId);
        }

        int userSel = 0;
        printf("Enter Song Number: ");
        if (scanf("%d", &userSel) <= 0) {
          Log.report(logvisor::Error, "unable to parse prompt");
          return 1;
        }

        if (userSel < songs.size()) {
          m_arrData = &songs[userSel].second;
          m_groupId = m_arrData->m_groupId;
          m_setupId = m_arrData->m_setupId;
          m_songName = &songs[userSel].first;
        } else {
          Log.report(logvisor::Error, "unable to find Song %d", userSel);
          return 1;
        }
      } else if (songs.size() == 1) {
        m_arrData = &songs[0].second;
        m_groupId = m_arrData->m_groupId;
        m_setupId = m_arrData->m_setupId;
        m_songName = &songs[0].first;
      }
    }
  }

  /* Get group selection via setup search */
  if (m_groupId == -1 && m_setupId != -1) {
    for (const auto& pair : allSongGroups) {
      for (const auto& setup : pair.second.second->m_midiSetups) {
        if (setup.first == m_setupId) {
          m_groupId = pair.first;
          m_groupName = &pair.second.first->first;
          break;
        }
      }
      if (m_groupId != -1)
        break;
    }
  }

  /* Get group selection via user */
  if (m_groupId != -1) {
    auto songSearch = allSongGroups.find(m_groupId);
    auto sfxSearch = allSFXGroups.find(m_groupId);
    if (songSearch != allSongGroups.end()) {
      m_sfxGroup = false;
      m_groupName = &songSearch->second.first->first;
    } else if (sfxSearch != allSFXGroups.end()) {
      m_sfxGroup = true;
      m_groupName = &sfxSearch->second.first->first;
    } else {
      Log.report(logvisor::Error, "unable to find Group %d", m_groupId);
      return 1;
    }
  } else if (totalGroups > 1) {
    /* Ask user to specify which group in project */
    printf("Multiple Audio Groups discovered:\n");
    for (const auto& pair : allSFXGroups) {
      amuse::Printf(_SYS_STR("    %d %s (SFXGroup)  %" PRISize " sfx-entries\n"), pair.first,
                    pair.second.first->first.c_str(), pair.second.second->m_sfxEntries.size());
    }
    for (const auto& pair : allSongGroups) {
      amuse::Printf(_SYS_STR("    %d %s (SongGroup)  %" PRISize " normal-pages, %" PRISize " drum-pages, %" PRISize
                             " MIDI-setups\n"),
                    pair.first, pair.second.first->first.c_str(), pair.second.second->m_normPages.size(),
                    pair.second.second->m_drumPages.size(), pair.second.second->m_midiSetups.size());
    }

    int userSel = 0;
    printf("Enter Group Number: ");
    if (scanf("%d", &userSel) <= 0) {
      Log.report(logvisor::Error, "unable to parse prompt");
      return 1;
    }

    auto songSearch = allSongGroups.find(userSel);
    auto sfxSearch = allSFXGroups.find(userSel);
    if (songSearch != allSongGroups.end()) {
      m_groupId = userSel;
      m_groupName = &songSearch->second.first->first;
      m_sfxGroup = false;
    } else if (sfxSearch != allSFXGroups.end()) {
      m_groupId = userSel;
      m_groupName = &sfxSearch->second.first->first;
      m_sfxGroup = true;
    } else {
      Log.report(logvisor::Error, "unable to find Group %d", userSel);
      return 1;
    }
  } else if (totalGroups == 1) {
    /* Load one and only group */
    if (allSongGroups.size()) {
      const auto& pair = *allSongGroups.cbegin();
      m_groupId = pair.first;
      m_groupName = &pair.second.first->first;
      m_sfxGroup = false;
    } else {
      const auto& pair = *allSFXGroups.cbegin();
      m_groupId = pair.first;
      m_groupName = &pair.second.first->first;
      m_sfxGroup = true;
    }
  } else {
    Log.report(logvisor::Error, "empty project");
    return 1;
  }

  /* Make final group selection */
  amuse::IntrusiveAudioGroupData* selData = nullptr;
  amuse::ObjToken<amuse::SongGroupIndex> songIndex;
  amuse::ObjToken<amuse::SFXGroupIndex> sfxIndex;
  auto songSearch = allSongGroups.find(m_groupId);
  if (songSearch != allSongGroups.end()) {
    selData = &songSearch->second.first->second;
    songIndex = songSearch->second.second;
    std::set<int> sortSetups;
    for (auto& pair : songIndex->m_midiSetups)
      sortSetups.insert(pair.first);
    if (m_setupId == -1) {
      /* Ask user to specify which group in project */
      printf("Multiple MIDI Setups:\n");
      for (int setup : sortSetups)
        printf("    %d\n", setup);
      int userSel = 0;
      printf("Enter Setup Number: ");
      if (scanf("%d", &userSel) <= 0) {
        Log.report(logvisor::Error, "unable to parse prompt");
        return 1;
      }
      m_setupId = userSel;
    }
    if (sortSetups.find(m_setupId) == sortSetups.cend()) {
      Log.report(logvisor::Error, "unable to find setup %d", m_setupId);
      return 1;
    }
  } else {
    auto sfxSearch = allSFXGroups.find(m_groupId);
    if (sfxSearch != allSFXGroups.end()) {
      selData = &sfxSearch->second.first->second;
      sfxIndex = sfxSearch->second.second;
    }
  }

  if (!selData) {
    Log.report(logvisor::Error, "unable to select audio group data");
    return 1;
  }

  if (m_sfxGroup) {
    Log.report(logvisor::Error, "amuserender is currently only able to render SongGroups");
    return 1;
  }

  /* WAV out path */
  amuse::SystemChar pathOut[1024];
  SNPrintf(pathOut, 1024, _SYS_STR("%s-%s.wav"), m_groupName->c_str(), m_songName->c_str());
  Log.report(logvisor::Info, _SYS_STR("Writing to %s"), pathOut);

  /* Build voice engine */
  std::unique_ptr<boo::IAudioVoiceEngine> voxEngine = boo::NewWAVAudioVoiceEngine(pathOut, rate, chCount);
  amuse::BooBackendVoiceAllocator booBackend(*voxEngine);
  amuse::Engine engine(booBackend, amuse::AmplitudeMode::PerSample);
  engine.setVolume(float(amuse::clamp(0.0, volume, 1.0)));

  /* Load group into engine */
  const amuse::AudioGroup* group = engine.addAudioGroup(*selData);
  if (!group) {
    Log.report(logvisor::Error, "unable to add audio group");
    return 1;
  }

  /* Enter playback loop */
  amuse::ObjToken<amuse::Sequencer> seq = engine.seqPlay(m_groupId, m_setupId, m_arrData->m_data.get(), false);
  size_t wroteFrames = 0;
  signal(SIGINT, SIGINTHandler);
  do {
    voxEngine->pumpAndMixVoices();
    wroteFrames += voxEngine->get5MsFrames();
    printf("\rFrame %" PRISize, wroteFrames);
    fflush(stdout);
  } while (!g_BreakLoop && (seq->state() == amuse::SequencerState::Playing || seq->getVoiceCount() != 0));

  printf("\n");
  return 0;
}