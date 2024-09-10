int setup_stream_test(int argc, const char* argv[])
{
    int rv = 0;

    if (checkHelp(argc, argv)) {
        std::cout << "SetupStreamTest [-c collectionid] [-D testfilesfolder] [-d dumpfile [-M dumpCountMax]] [-f filterCategory 0|1|2|3]" << std::endl;
        std::cout << "  collectionid    = Collection ID. Default is \"streamtestcollection\"" << std::endl;
        std::cout << "  testfilesfolder = Folder containing test files. Ignored on client." << std::endl;
        std::cout << "  dumpfile        = Dump URLs to this file." << std::endl;
        std::cout << "  dumpCountMax    = Dump at most this many files." << std::endl;
        std::cout << "  filterCategory  = 0 - All(Disabled) | 1 - Music | 2 - Photo | 3 - Music&Photo(Disabled) | 4 - Video | 5 - Music&Video(Disabled) | 6 - Photo&Video(Disabled). Default is 1 - dump music." << std::endl;
        return 0;
    }

    std::string collectionid;
    std::string testfilesfolder;
    std::string dumpfile;
    int dumpCountMax = -1;  // meaning no limit
    bool downloadMusic = true;
    bool downloadPhoto = false;
    bool downloadVideo = false;
    media_metadata::CatalogType_t catType = media_metadata::MM_CATALOG_MUSIC;
    collectionid.assign("streamtestcollection");  // default collection ID

    setDebugLevel(LOG_LEVEL_INFO);

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
            case 'c':
                if (i + 1 < argc) {
                    collectionid.assign(argv[++i]);
                }
                break;
            case 'D':
                if (i + 1 < argc) {
                    testfilesfolder.assign(argv[++i]);
                }
                break;
            case 'd':
                if (i + 1 < argc) {
                    dumpfile.assign(argv[++i]);
                }
                break;
            case 'M':
                if (i + 1 < argc) {
                    dumpCountMax = atoi(argv[++i]);
                }
                break;
            case 'f':
                if(i + 1 < argc) {
                    if(atoi(argv[i+1]) == 0) {
                        downloadMusic = true;
                        downloadPhoto = true;
                        downloadVideo = true;
                        LOG_ERROR("Not supported");
                        return -1;
                    }
                    else if(atoi(argv[i+1]) == 1) {
                        downloadMusic = true;
                        downloadPhoto = false;
                        downloadVideo = false;
                        catType = media_metadata::MM_CATALOG_MUSIC;
                    }
                    else if(atoi(argv[i+1]) == 2) {
                        downloadMusic = false;
                        downloadPhoto = true;
                        downloadVideo = false;
                        catType = media_metadata::MM_CATALOG_PHOTO;
                    }
                    else if(atoi(argv[i+1]) == 3) {
                        downloadMusic = true;
                        downloadPhoto = true;
                        downloadVideo = false;
                        LOG_ERROR("Not supported");
                        return -1;
                    }
                    else if(atoi(argv[i+1]) == 4) {
                        downloadMusic = false;
                        downloadPhoto = false;
                        downloadVideo = true;
                        catType = media_metadata::MM_CATALOG_VIDEO;
                    }
                    else if(atoi(argv[i+1]) == 5) {
                        downloadMusic = true;
                        downloadPhoto = false;
                        downloadVideo = true;
                        LOG_ERROR("Not supported");
                        return -1;
                    }
                    else {
                        downloadMusic = false;
                        downloadPhoto = true;
                        downloadVideo = true;
                        LOG_ERROR("Not supported");
                        return -1;
                    }
                }
                break;
            default:
                LOG_ERROR("Unknown option %s", argv[i]);
                return -2;
            }
        }
    }

    u64 userId = 0;
    rv = getUserIdBasic(&userId);
    if (rv != 0) {
        LOG_ERROR("Failed to get user ID: %d", rv);
        return rv;
    }

    u64 deviceId = 0;
    rv = getDeviceId(&deviceId);
    if (rv != 0) {
        LOG_ERROR("Failed to get device ID: %d", rv);
        return rv;
    }

    if (!testfilesfolder.empty()) {
        if (isCloudpc(userId, deviceId)) {
            rv = setup_stream_test_create_metadata(userId,
                                                   deviceId,
                                                   catType,
                                                   collectionid,
                                                   testfilesfolder);
        }
        else {
            LOG_WARN("-D ignored on client PC");
        }
    }

    if (!dumpfile.empty()) {
        rv = setup_stream_test_write_dumpfile(userId,
                                              deviceId,
                                              collectionid,
                                              dumpfile,
                                              downloadMusic,
                                              downloadPhoto,
                                              downloadVideo,
                                              dumpCountMax);
    }

    resetDebugLevel();

    return rv;
}