static int init(sh_video_t *sh)
{
    int err;
    char fname[MAX_PATH + 1] = "";
    memset(&dsn, 0, sizeof(dsn));
#ifdef WIN32_LOADER
    dsn.ldt_fs = Setup_LDT_Keeper();
#endif
    dsn.hLib = LoadLibraryA("dshownative.dll");

    if (!dsn.hLib)
    {
        mp_msg(MSGT_DECVIDEO, MSGL_ERR, "[dshownative] Cannot find dshownative.dll: %ld\n", GetLastError());
        return 0;
    }

    dsn.DSOpenVideoCodec = (funcDSOpenVideoCodec) GetProcAddress(dsn.hLib, "DSOpenVideoCodec");
    dsn.DSCloseVideoCodec = (funcDSCloseVideoCodec) GetProcAddress(dsn.hLib, "DSCloseVideoCodec");
    dsn.DSVideoDecode = (funcDSVideoDecode) GetProcAddress(dsn.hLib, "DSVideoDecode");
    dsn.DSVideoResync = (funcDSVideoResync) GetProcAddress(dsn.hLib, "DSVideoResync");
    dsn.DSStrError = (funcDSStrError) GetProcAddress(dsn.hLib, "DSStrError");
    dsn.DSGetApiVersion = (funcDSGetApiVersion) GetProcAddress(dsn.hLib, "DSGetApiVersion");

    if (!(dsn.DSOpenVideoCodec && dsn.DSCloseVideoCodec && dsn.DSVideoDecode && dsn.DSVideoResync && dsn.DSStrError && dsn.DSGetApiVersion))
    {
        mp_msg(MSGT_DECVIDEO, MSGL_ERR, "[dshownative] dshownative dll symbol mismatch\n");
        return 0;
    }
    if (dsn.DSGetApiVersion() != DSN_API_VERSION)
    {
        mp_msg(MSGT_DECVIDEO, MSGL_ERR, "[dshownative] Incompatible API version\n");
        return 0;
    }

    if (sh->ds->demuxer->filename)
        GetFullPathNameA(sh->ds->demuxer->filename, MAX_PATH, fname, NULL);

    if (!(dsn.codec = dsn.DSOpenVideoCodec(sh->codec->dll, sh->codec->guid, sh->bih,
                                           sh->codec->outfmt[sh->outfmtidx], sh->fps, fname, is_mpegts_format, &err)))
    {
        mp_msg(MSGT_DECVIDEO, MSGL_ERR, "[dshownative] Codec init failed: %s\n", dsn.DSStrError(err));
        return 0;
    }

    if (!mpcodecs_config_vo(sh, sh->disp_w, sh->disp_h, IMGFMT_YUY2))
    {
        mp_msg(MSGT_DECVIDEO, MSGL_ERR, "[dshownative] mpcodecs_config_vo() failed\n");
        return 0;
    }

	special_codec = 1;
    mp_msg(MSGT_DECVIDEO, MSGL_V, "INFO: [dshownative] video codec init OK.\n");
    return 1;
}