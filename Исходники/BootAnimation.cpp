bool BootAnimation::movie()
{

    char bootenabled[PROPERTY_VALUE_MAX];
    char bootsound[PROPERTY_VALUE_MAX];
    char bootvolume[PROPERTY_VALUE_MAX];
    property_get("persist.sys.boot_enabled", bootenabled, "1");
    property_get("persist.sys.boot_sound", bootsound, "1");
    property_get("persist.sys.boot_volume", bootvolume, "0.2");

    bool bootEnabled = atoi(bootenabled) != 0;
    bool enableSound = atoi(bootsound) != 0;
    float bootVolume = strtof(bootvolume, NULL);

    if(!bootEnabled) {
        return false;
    }

    if(enableSound){
      sp<MediaPlayer> mediaplay = new MediaPlayer();
      mediaplay->setDataSource ("/system/media/audio.mp3", NULL);
      mediaplay->setVolume (bootVolume, bootVolume);
      mediaplay->prepare();
      mediaplay->start();
    }

    ZipFileRO& zip(mZip);

    size_t numEntries = zip.getNumEntries();
    ZipEntryRO desc = zip.findEntryByName("desc.txt");
    FileMap* descMap = zip.createEntryFileMap(desc);
    ALOGE_IF(!descMap, "descMap is null");
    if (!descMap) {
        return false;
    }

    String8 desString((char const*)descMap->getDataPtr(),
            descMap->getDataLength());
    char const* s = desString.string();

    Animation animation;

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    // Parse the description file
    for (;;) {
        const char* endl = strstr(s, "\n");
        if (!endl) break;
        String8 line(s, endl - s);
        const char* l = line.string();
        int fps, width, height, count, pause, red, green, blue;
        char path[256];
        char pathType;
        if (sscanf(l, "%d %d %d %d %d %d", &width, &height, &fps, &red, &green, &blue) == 6) {
            //ALOGD("> w=%d, h=%d, fps=%d, rgb=(%d, %d, %d)", width, height, fps, red, green, blue);
            animation.width = width;
            animation.height = height;
            animation.fps = fps;
            r = (float) red / 255.0f;
            g = (float) green / 255.0f;
            b = (float) blue / 255.0f;
        }
        else if (sscanf(l, "%d %d %d", &width, &height, &fps) == 3) {
            //LOGD("> w=%d, h=%d, fps=%d", width, height, fps);
            animation.width = width;
            animation.height = height;
            animation.fps = fps;
        }
        else if (sscanf(l, " %c %d %d %s", &pathType, &count, &pause, path) == 4) {
            //LOGD("> type=%c, count=%d, pause=%d, path=%s", pathType, count, pause, path);
            Animation::Part part;
            part.playUntilComplete = pathType == 'c';
            part.count = count;
            part.pause = pause;
            part.path = path;
            animation.parts.add(part);
        }

        s = ++endl;
    }

    // read all the data structures
    const size_t pcount = animation.parts.size();
    for (size_t i=0 ; i<numEntries ; i++) {
        char name[256];
        ZipEntryRO entry = zip.findEntryByIndex(i);
        if (zip.getEntryFileName(entry, name, 256) == 0) {
            const String8 entryName(name);
            const String8 path(entryName.getPathDir());
            const String8 leaf(entryName.getPathLeaf());
            if (leaf.size() > 0) {
                for (size_t j=0 ; j<pcount ; j++) {
                    if (path == animation.parts[j].path) {
                        int method;
                        // supports only stored png files
                        if (zip.getEntryInfo(entry, &method, 0, 0, 0, 0, 0)) {
                            if (method == ZipFileRO::kCompressStored) {
                                FileMap* map = zip.createEntryFileMap(entry);
                                if (map) {
                                    Animation::Frame frame;
                                    frame.name = leaf;
                                    frame.map = map;
                                    Animation::Part& part(animation.parts.editItemAt(j));
                                    part.frames.add(frame);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

#ifndef CONTINUOUS_SPLASH
    // clear screen
    glShadeModel(GL_FLAT);
    glDisable(GL_DITHER);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_BLEND);
    glClearColor(r,g,b,1);
    glClear(GL_COLOR_BUFFER_BIT);

    eglSwapBuffers(mDisplay, mSurface);
#endif

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_TEXTURE_2D);
    glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const int xc = (mWidth - animation.width) / 2;
    const int yc = ((mHeight - animation.height) / 2);
    nsecs_t lastFrame = systemTime();
    nsecs_t frameDuration = s2ns(1) / animation.fps;

    Region clearReg(Rect(mWidth, mHeight));
    clearReg.subtractSelf(Rect(xc, yc, xc+animation.width, yc+animation.height));

    for (int i=0 ; i<pcount ; i++) {
        const Animation::Part& part(animation.parts[i]);
        const size_t fcount = part.frames.size();

        // can be 1, 0, or not set
        #ifdef NO_TEXTURE_CACHE
        const int noTextureCache = NO_TEXTURE_CACHE;
        #else
        const int noTextureCache = ((animation.width * animation.height * fcount) >
                                 48 * 1024 * 1024) ? 1 : 0;
        #endif

        glBindTexture(GL_TEXTURE_2D, 0);

        for (int r=0 ; !part.count || r<part.count ; r++) {
            // Exit any non playuntil complete parts immediately
            if(exitPending() && !part.playUntilComplete)
                break;

            for (int j=0 ; j<fcount && (!exitPending() || part.playUntilComplete) ; j++) {
                const Animation::Frame& frame(part.frames[j]);
                nsecs_t lastFrame = systemTime();

                if (r > 0 && !noTextureCache) {
                    glBindTexture(GL_TEXTURE_2D, frame.tid);
                } else {
                    if (part.count != 1) {
                        glGenTextures(1, &frame.tid);
                        glBindTexture(GL_TEXTURE_2D, frame.tid);
                        glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                        glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    }
                    initTexture(
                            frame.map->getDataPtr(),
                            frame.map->getDataLength());
                }

                if (!clearReg.isEmpty()) {
                    Region::const_iterator head(clearReg.begin());
                    Region::const_iterator tail(clearReg.end());
                    glEnable(GL_SCISSOR_TEST);
                    while (head != tail) {
                        const Rect& r(*head++);
                        glScissor(r.left, mHeight - r.bottom,
                                r.width(), r.height());
                        glClear(GL_COLOR_BUFFER_BIT);
                    }
                    glDisable(GL_SCISSOR_TEST);
                }
                glDrawTexiOES(xc, yc, 0, animation.width, animation.height);
                eglSwapBuffers(mDisplay, mSurface);

                nsecs_t now = systemTime();
                nsecs_t delay = frameDuration - (now - lastFrame);
                //ALOGD("%lld, %lld", ns2ms(now - lastFrame), ns2ms(delay));
                lastFrame = now;

                if (delay > 0) {
                    struct timespec spec;
                    spec.tv_sec  = (now + delay) / 1000000000;
                    spec.tv_nsec = (now + delay) % 1000000000;
                    int err;
                    do {
                        err = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &spec, NULL);
                    } while (err<0 && errno == EINTR);
                }

                checkExit();

                if (noTextureCache)
                    glDeleteTextures(1, &frame.tid);
            }

            usleep(part.pause * ns2us(frameDuration));

            // For infinite parts, we've now played them at least once, so perhaps exit
            if(exitPending() && !part.count)
                break;
        }

        // free the textures for this part
        if (part.count != 1 && !noTextureCache) {
            for (size_t j=0 ; j<fcount ; j++) {
                const Animation::Frame& frame(part.frames[j]);
                glDeleteTextures(1, &frame.tid);
            }
        }
    }

    return false;
}