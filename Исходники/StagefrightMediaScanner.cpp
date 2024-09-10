MediaScanResult StagefrightMediaScanner::processFileInternal(
        const char *path, const char *mimeType,
        MediaScannerClient &client) {
    const char *extension = strrchr(path, '.');

    if (!extension) {
        return MEDIA_SCAN_RESULT_SKIPPED;
    }

    if (!FileHasAcceptableExtension(extension)) {
        return MEDIA_SCAN_RESULT_SKIPPED;
    }

#ifndef ANDROID_DEFAULT_CODE
#ifdef MTK_DRM_APP
    // add dcf meta data for dcf file
    // check extension first
    LOGV("processFileInternal() : the extension: %s", extension);
    bool isOMADrmDcf = false;
    if (0 == strcasecmp(extension, ".dcf")) {
        String8 tmp(path);
        DrmManagerClient* drmManagerClient = new DrmManagerClient();
        DrmMetadata* dcfMetadata = drmManagerClient->getMetadata(&tmp);

        if (dcfMetadata == NULL) {
            LOGW("scan: OMA DRM v1: failed to get drm metadata, not scanned into db.");
            delete drmManagerClient;
            client.setMimeType("bad mime type");
            return MEDIA_SCAN_RESULT_SKIPPED;
        }

        struct Map {
            const char* from;
            int to;
        };
        static const Map kMap[] = {
            {DrmMetaKey::META_KEY_IS_DRM,
                METADATA_KEY_IS_DRM}, // "is_drm"
            {DrmMetaKey::META_KEY_CONTENT_URI, 
                METADATA_KEY_DRM_CONTENT_URI},
            {DrmMetaKey::META_KEY_OFFSET,
                METADATA_KEY_DRM_OFFSET},
            {DrmMetaKey::META_KEY_DATALEN,
                METADATA_KEY_DRM_DATALEN},
            {DrmMetaKey::META_KEY_RIGHTS_ISSUER,
                METADATA_KEY_DRM_RIGHTS_ISSUER},
            {DrmMetaKey::META_KEY_CONTENT_NAME,
                METADATA_KEY_DRM_CONTENT_NAME},
            {DrmMetaKey::META_KEY_CONTENT_DESCRIPTION,
                METADATA_KEY_DRM_CONTENT_DES},
            {DrmMetaKey::META_KEY_CONTENT_VENDOR,
                METADATA_KEY_DRM_CONTENT_VENDOR},
            {DrmMetaKey::META_KEY_ICON_URI,
                METADATA_KEY_DRM_ICON_URI} ,
            {DrmMetaKey::META_KEY_METHOD,
                METADATA_KEY_DRM_METHOD},
            {DrmMetaKey::META_KEY_MIME,
                METADATA_KEY_DRM_MIME}
        };
        static const size_t kNumMapEntries = sizeof(kMap) / sizeof(kMap[0]);

        int action = Action::PLAY;
        String8 type;
        for (size_t i = 0; i < kNumMapEntries; ++i) {
            String8 value = dcfMetadata->get(String8(kMap[i].from));
            if (value.length() != 0)
            {
                if (kMap[i].to == METADATA_KEY_DRM_MIME) {
                    value = DrmMtkUtil::toCommonMime(value.string());
                    // not audio/video/image -> not scan into db
                    type.setTo(value.string(), 6);
                    if (0 != strcasecmp(type.string(), "audio/")
                        && 0 != strcasecmp(type.string(), "video/")
                        && 0 != strcasecmp(type.string(), "image/")) {
                        LOGW("scan: OMA DRM v1: invalid drm media file mime type[%s], not added into db.",
                                value.string());
                        delete dcfMetadata;
                        delete drmManagerClient;
                        client.setMimeType("bad mime type");
                        return MEDIA_SCAN_RESULT_SKIPPED;
                    }

                    client.setMimeType(value.string());
                    LOGD("scan: OMA DRM v1: drm original mime type[%s].",
                            value.string());

                    // determine the Action it shall used.
                    if ((0 == strcasecmp(type.string(), "audio/"))
                        || (0 == strcasecmp(type.string(), "video/"))) {
                        action = Action::PLAY;
                    } else if ((0 == strcasecmp(type.string(), "image/"))) {
                        action = Action::DISPLAY;
                    }
                }

                if (kMap[i].to == METADATA_KEY_IS_DRM) {
                    isOMADrmDcf = (value == String8("1"));
                }

                client.addStringTag(kMap[i].from, value.string());
                LOGD("scan: OMA DRM v1: client.addString tag[%s] value[%s].",
                        kMap[i].from, value.string());
            }
        }

        // if there's no valid rights for this file currently, just return OK
        // to make sure it can be scanned into db.
        if (isOMADrmDcf
            && RightsStatus::RIGHTS_VALID != drmManagerClient->checkRightsStatus(tmp, action)) {
            LOGD("scan: OMA DRM v1: current no valid rights, return OK so that it can be added into db.");
            delete dcfMetadata;
            delete drmManagerClient;
            return MEDIA_SCAN_RESULT_OK;
        }

        // when there's valid rights, should contine to add extra metadata
        LOGD("scan: OMA DRM v1: current valid rights, continue to add extra info.");
        delete dcfMetadata; dcfMetadata = NULL;
        delete drmManagerClient; drmManagerClient = NULL;

        // if picture then we need not to scan with extractors.
        if (isOMADrmDcf && 0 == strcasecmp(type.string(), "image/")) {
            LOGD("scan: OMA DRM v1: for DRM image we do not sniff with extractors.");
            return MEDIA_SCAN_RESULT_OK;
        }
    }
#endif
#endif

    if (!strcasecmp(extension, ".mid")
            || !strcasecmp(extension, ".smf")
            || !strcasecmp(extension, ".imy")
            || !strcasecmp(extension, ".midi")
            || !strcasecmp(extension, ".xmf")
            || !strcasecmp(extension, ".rtttl")
            || !strcasecmp(extension, ".rtx")
            || !strcasecmp(extension, ".ota")
            || !strcasecmp(extension, ".mxmf")) {
        return HandleMIDI(path, &client);
    }

    sp<MediaMetadataRetriever> mRetriever(new MediaMetadataRetriever);

    status_t status = mRetriever->setDataSource(path);
    if (status) {
#ifndef ANDROID_DEFAULT_CODE
         //if this still need on ICS
        // set mime type to "bad mime type" for unsupported format, otherwise the file will be included in Gallery/Music
        LOGE("processFile '%s' - not supported", path);
        client.setMimeType("bad mime type");
        return MEDIA_SCAN_RESULT_SKIPPED;
#else
        return MEDIA_SCAN_RESULT_ERROR;
#endif
    }

    const char *value;
    if ((value = mRetriever->extractMetadata(
                    METADATA_KEY_MIMETYPE)) != NULL) {
        status = client.setMimeType(value);
        if (status) {
            return MEDIA_SCAN_RESULT_ERROR;
        }
    }

    struct KeyMap {
        const char *tag;
        int key;
    };
    static const KeyMap kKeyMap[] = {
        { "tracknumber", METADATA_KEY_CD_TRACK_NUMBER },
        { "discnumber", METADATA_KEY_DISC_NUMBER },
        { "album", METADATA_KEY_ALBUM },
        { "artist", METADATA_KEY_ARTIST },
        { "albumartist", METADATA_KEY_ALBUMARTIST },
        { "composer", METADATA_KEY_COMPOSER },
        { "genre", METADATA_KEY_GENRE },
        { "title", METADATA_KEY_TITLE },
        { "year", METADATA_KEY_YEAR },
        { "duration", METADATA_KEY_DURATION },
        { "writer", METADATA_KEY_WRITER },
        { "compilation", METADATA_KEY_COMPILATION },
        { "isdrm", METADATA_KEY_IS_DRM }, // "isdrm"
#ifdef MTK_S3D_SUPPORT
        {"stereotype",METADATA_KEY_STEREO_3D}, //stereo 3d info
#endif
    };
    static const size_t kNumEntries = sizeof(kKeyMap) / sizeof(kKeyMap[0]);

    for (size_t i = 0; i < kNumEntries; ++i) {
        const char *value;
        if ((value = mRetriever->extractMetadata(kKeyMap[i].key)) != NULL) {
#ifndef ANDROID_DEFAULT_CODE
#ifdef MTK_DRM_APP
            if (kKeyMap[i].key == METADATA_KEY_IS_DRM) {
                if (isOMADrmDcf) {
                    LOGD("set METADATA_KEY_IS_DRM to 1 for OMA DRM v1.");
                    value = "1";
                }
            }
#endif
#endif
            status = client.addStringTag(kKeyMap[i].tag, value);
            LOGD("processFileInternal() : client.addString tag[%s] value[%s]",
                        kKeyMap[i].tag, value);
            if (status != OK) {
                return MEDIA_SCAN_RESULT_ERROR;
            }
#ifndef ANDROID_DEFAULT_CODE
            if (kKeyMap[i].key == METADATA_KEY_DURATION) {
                if (!strcasecmp(extension, ".mp3")
                        || !strcasecmp(extension, ".aac")
                        || !strcasecmp(extension, ".amr")
                        || !strcasecmp(extension, ".awb")) {
                    client.addStringTag("isAccurateDuration", "0");
                } else if (!strcasecmp(extension, ".wav")
                        || !strcasecmp(extension, ".ogg")
                        || !strcasecmp(extension, ".oga")) {
                    client.addStringTag("isAccurateDuration", "1");
                }
            }
#endif // ANDROID_DEFAULT_CODE
        }
    }
#ifndef ANDROID_DEFAULT_CODE
	LOGD("processFileInternal '%s' - return OK", path);
#endif
    return MEDIA_SCAN_RESULT_OK;
}