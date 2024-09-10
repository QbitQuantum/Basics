bool QKindleFb::connect(const QString &displaySpec)
{
    d_ptr->displaySpec = displaySpec;

    const QStringList args = displaySpec.split(QLatin1Char(':'));

    d_ptr->doGraphicsMode = false;

    if (args.contains(QLatin1String("flashing")))
        flashingUpdates = true ;
    else
        flashingUpdates = false ;

    if (args.contains(QLatin1String("debug")))
        debugMode = true ;
    else
        debugMode = false ;


    if (args.contains(QLatin1String("cursor")))
        hasCursor = true ;
    else
        hasCursor = false ;

    fullUpdateEvery = 1;
    const QStringList updateArg = args.filter(QLatin1String("update="));
    if (updateArg.length() == 1) {
        fullUpdateEvery = updateArg.at(0).section(QLatin1Char('='), 1, 1).toInt();
    }

    d_ptr->ttyDevice = EINK_FRAME_BUFFER ;

    QString dev = QLatin1String(EINK_FRAME_BUFFER);
    QString dev_alt = QLatin1String(EINK_FRAME_BUFFER_ALT_NAME);

    d_ptr->fd = open(dev.toLatin1().constData(), O_RDWR);

    /* try alt frame buffer name */
    if (d_ptr->fd == -1)
        d_ptr->fd = open(dev_alt.toLatin1().constData(), O_RDWR);

    if (d_ptr->fd == -1) {
        if (QApplication::type() == QApplication::GuiServer) {
            perror("QKindleFb::connect");
            qCritical("Error opening framebuffer device %s(%s)", qPrintable(dev), qPrintable(dev_alt));
            return false;
        }
    }

    ::fb_fix_screeninfo finfo;
    ::fb_var_screeninfo vinfo;

    //#######################
    memset(&vinfo, 0, sizeof(vinfo));
    memset(&finfo, 0, sizeof(finfo));
    //#######################

    /* Get fixed screen information */
    if (d_ptr->fd != -1 && ioctl(d_ptr->fd, FBIOGET_FSCREENINFO, &finfo)) {
        perror("QKindleFb::connect");
        qWarning("Error reading fixed information");
        return false;
    }

    d_ptr->driverType = strcmp(finfo.id, "eink_fb") ? GenericDriver : KindleEink ;

    /* Get variable screen information */
    if (d_ptr->fd != -1 && ioctl(d_ptr->fd, FBIOGET_VSCREENINFO, &vinfo)) {
        perror("QKindleFb::connect");
        qWarning("Error reading variable information");
        return false;
    }


#ifdef DEBUG_VINFO
    show_info(&finfo, &vinfo) ;
#endif

    grayscale = vinfo.grayscale;
    d = vinfo.bits_per_pixel;
    lstep = finfo.line_length;

    int xoff = vinfo.xoffset;
    int yoff = vinfo.yoffset;
    const char* qwssize;
    if((qwssize=::getenv("QWS_SIZE")) && sscanf(qwssize,"%dx%d",&w,&h)==2) {
        if (d_ptr->fd != -1) {
            if ((uint)w > vinfo.xres) w = vinfo.xres;
            if ((uint)h > vinfo.yres) h = vinfo.yres;
        }
        dw=w;
        dh=h;
        int xxoff, yyoff;
        if (sscanf(qwssize, "%*dx%*d+%d+%d", &xxoff, &yyoff) == 2) {
            if (xxoff < 0 || xxoff + w > (int)vinfo.xres)
                xxoff = vinfo.xres - w;
            if (yyoff < 0 || yyoff + h > (int)vinfo.yres)
                yyoff = vinfo.yres - h;
            xoff += xxoff;
            yoff += yyoff;
        } else {
            xoff += (vinfo.xres - w)/2;
            yoff += (vinfo.yres - h)/2;
        }
    } else {
        dw=w=vinfo.xres;
        dh=h=vinfo.yres;
        if (debugMode)
        {
            qDebug(".. dw=%d, dh=%d, lstep=%d", dw, dh, lstep) ;
        }

    }

    if (w == 0 || h == 0) {
        qWarning("QKindleFb::connect(): Unable to find screen geometry, "
                 "will use detected device values.");
        dw = w = Device::getWidth();
        dh = h = Device::getHeight();
    }

    // Handle display physical size spec.
    if (vinfo.width != 0 && vinfo.height != 0
            && vinfo.width != UINT_MAX && vinfo.height != UINT_MAX) {
        physWidth = vinfo.width;
        physHeight = vinfo.height;
    } else {
        // the controller didn't report screen physical
        // dimensions. Set them manually:
        double dpi = Device::getDpi();
        double mmperinch = 25.4 ;
        physWidth = qRound(dw*mmperinch/dpi) ;
        physHeight = qRound(dh*mmperinch/dpi) ;
    }

    if (debugMode)
        qDebug("physW=%d, physH=%d", physWidth, physHeight) ;

    dataoffset = yoff * lstep + xoff * d / 8;

    /* Figure out the size of the screen in bytes */
    size = h * lstep;

    mapsize = finfo.smem_len;

    data = (unsigned char *)-1;
    if (d_ptr->fd != -1)
        data = (unsigned char *)mmap(0, mapsize, PROT_READ | PROT_WRITE,
                                     MAP_SHARED , d_ptr->fd, 0);

    if ((long)data == -1) {
        if (QApplication::type() == QApplication::GuiServer) {
            perror("QKindleFb::connect");
            qWarning("Error: failed to map framebuffer device to memory.");
            return false;
        }
        data = 0;
    } else {
        data += dataoffset;
    }

    canaccel = false ;

    // Now read in palette
    if((vinfo.bits_per_pixel==8) || (vinfo.bits_per_pixel==4)) {
        screencols= (vinfo.bits_per_pixel==8) ? 256 : 16;

        // force screen colors to be 16 if it is K4
        if (isKindle4 || isKindle5)
        {
            screencols = 16 ;
        }

        int loopc;
        ::fb_cmap startcmap;
        startcmap.start=0;
        startcmap.len=screencols;
        startcmap.red=(unsigned short int *)
                malloc(sizeof(unsigned short int)*screencols);
        startcmap.green=(unsigned short int *)
                malloc(sizeof(unsigned short int)*screencols);
        startcmap.blue=(unsigned short int *)
                malloc(sizeof(unsigned short int)*screencols);
        startcmap.transp=(unsigned short int *)
                malloc(sizeof(unsigned short int)*screencols);

        createPalette(startcmap, vinfo, finfo);

        int bits_used = 0;
        for(loopc=0;loopc<screencols;loopc++) {
            screenclut[loopc]=qRgb(startcmap.red[loopc] >> 8,
                                   startcmap.green[loopc] >> 8,
                                   startcmap.blue[loopc] >> 8);
            bits_used |= startcmap.red[loopc]
                    | startcmap.green[loopc]
                    | startcmap.blue[loopc];
        }
        // WORKAROUND: Some framebuffer drivers only return 8 bit
        // color values, so we need to not bit shift them..
        if ((bits_used & 0x00ff) && !(bits_used & 0xff00)) {
            for(loopc=0;loopc<screencols;loopc++) {
                screenclut[loopc] = qRgb(startcmap.red[loopc],
                                         startcmap.green[loopc],
                                         startcmap.blue[loopc]);
            }
            qWarning("8 bits cmap returned due to faulty FB driver, colors corrected");
        }
        free(startcmap.red);
        free(startcmap.green);
        free(startcmap.blue);
        free(startcmap.transp);
    } else {