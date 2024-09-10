AudioPlugin::AudioPlugin(NPP inst) : SubPlugin(inst) {

    const char path[] = "/sdcard/sample.raw";

    // open a file stream
    FILE* f = fopen(path, "r");
    gLogI.log(inst, kDebug_ANPLogType, "--- path %s FILE %p", path, f);

    // setup our private audio struct's default values
    m_soundPlay = new SoundPlay;
    m_soundPlay->instance = inst;
    m_soundPlay->progress = 0;
    m_soundPlay->fileSize = 0;
    m_soundPlay->file = f;
    m_soundPlay->track = NULL;

    // create the audio track
    if (f) {
        m_soundPlay->track = gSoundI.newTrack(44100, kPCM16Bit_ANPSampleFormat, 2, audioCallback, m_soundPlay);
        if (!m_soundPlay->track) {
            fclose(f);
            m_soundPlay->file = NULL;
        }
    }

    // get the audio file's size
    int fileDescriptor = open(path, O_RDONLY);
    struct stat fileStatus;

    if(fileDescriptor <= 0) {
        gLogI.log(inst, kError_ANPLogType, "fopen error");
    }
    else if (fstat(fileDescriptor, &fileStatus) != 0) {
        gLogI.log(inst, kDebug_ANPLogType, "File Size: %d", fileStatus.st_size);
        m_soundPlay->fileSize = fileStatus.st_size;
    } else {
        gLogI.log(inst, kError_ANPLogType, "fstat error");
    }

    // configure the UI elements
    m_activeTouch = false;

    memset(&m_trackRect, 0, sizeof(m_trackRect));
    memset(&m_playRect,  0, sizeof(m_playRect));
    memset(&m_pauseRect, 0, sizeof(m_pauseRect));
    memset(&m_stopRect,  0, sizeof(m_stopRect));

    m_paintTrack = gPaintI.newPaint();
    gPaintI.setFlags(m_paintTrack, gPaintI.getFlags(m_paintTrack) | kAntiAlias_ANPPaintFlag);
    gPaintI.setColor(m_paintTrack, 0xFFC0C0C0);

    m_paintRect = gPaintI.newPaint();
    gPaintI.setFlags(m_paintRect, gPaintI.getFlags(m_paintRect) | kAntiAlias_ANPPaintFlag);
    gPaintI.setColor(m_paintRect, 0xFFA8A8A8);

    m_paintText = gPaintI.newPaint();
    gPaintI.setFlags(m_paintText, gPaintI.getFlags(m_paintText) | kAntiAlias_ANPPaintFlag);
    gPaintI.setColor(m_paintText, 0xFF2F4F4F);
    gPaintI.setTextSize(m_paintText, 18);

    m_paintTrackProgress = gPaintI.newPaint();
    gPaintI.setFlags(m_paintTrackProgress, gPaintI.getFlags(m_paintTrackProgress) | kAntiAlias_ANPPaintFlag);
    gPaintI.setColor(m_paintTrackProgress, 0xFF545454);

    m_paintActiveRect = gPaintI.newPaint();
    gPaintI.setFlags(m_paintActiveRect, gPaintI.getFlags(m_paintActiveRect) | kAntiAlias_ANPPaintFlag);
    gPaintI.setColor(m_paintActiveRect, 0xFF545454);

    ANPTypeface* tf = gTypefaceI.createFromName("serif", kItalic_ANPTypefaceStyle);
    gPaintI.setTypeface(m_paintText, tf);
    gTypefaceI.unref(tf);

    //register for touch events
    ANPEventFlags flags = kTouch_ANPEventFlag;
    NPError err = browser->setvalue(inst, kAcceptEvents_ANPSetValue, &flags);
    if (err != NPERR_NO_ERROR) {
        gLogI.log(inst, kError_ANPLogType, "Error selecting input events.");
    }
}