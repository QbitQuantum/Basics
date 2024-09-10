bool QLinuxFbScreen::connect(const QString &displaySpec)
{
    d_ptr->displaySpec = displaySpec;

    const QStringList args = displaySpec.split(QLatin1Char(':'));

    if (args.contains(QLatin1String("nographicsmodeswitch")))
        d_ptr->doGraphicsMode = false;

#ifdef QT_QWS_DEPTH_GENERIC
    if (args.contains(QLatin1String("genericcolors")))
        d_ptr->doGenericColors = true;
#endif

    QRegExp ttyRegExp(QLatin1String("tty=(.*)"));
    if (args.indexOf(ttyRegExp) != -1)
        d_ptr->ttyDevice = ttyRegExp.cap(1);

#if Q_BYTE_ORDER == Q_BIG_ENDIAN
#ifndef QT_QWS_FRAMEBUFFER_LITTLE_ENDIAN
    if (args.contains(QLatin1String("littleendian")))
#endif
        QScreen::setFrameBufferLittleEndian(true);
#endif

    QString dev = QLatin1String("/dev/fb0");
    foreach(QString d, args) {
	if (d.startsWith(QLatin1Char('/'))) {
	    dev = d;
	    break;
	}
    }

    if (access(dev.toLatin1().constData(), R_OK|W_OK) == 0)
        d_ptr->fd = QT_OPEN(dev.toLatin1().constData(), O_RDWR);
    if (d_ptr->fd == -1) {
        if (QApplication::type() == QApplication::GuiServer) {
            perror("QScreenLinuxFb::connect");
            qCritical("Error opening framebuffer device %s", qPrintable(dev));
            return false;
        }
        if (access(dev.toLatin1().constData(), R_OK) == 0)
            d_ptr->fd = QT_OPEN(dev.toLatin1().constData(), O_RDONLY);
    }

    ::fb_fix_screeninfo finfo;
    ::fb_var_screeninfo vinfo;
    //#######################
    // Shut up Valgrind
    memset(&vinfo, 0, sizeof(vinfo));
    memset(&finfo, 0, sizeof(finfo));
    //#######################

    /* Get fixed screen information */
    if (d_ptr->fd != -1 && ioctl(d_ptr->fd, FBIOGET_FSCREENINFO, &finfo)) {
        perror("QLinuxFbScreen::connect");
        qWarning("Error reading fixed information");
        return false;
    }

    d_ptr->driverType = strcmp(finfo.id, "8TRACKFB") ? GenericDriver : EInk8Track;

    if (finfo.type == FB_TYPE_VGA_PLANES) {
        qWarning("VGA16 video mode not supported");
        return false;
    }

    /* Get variable screen information */
    if (d_ptr->fd != -1 && ioctl(d_ptr->fd, FBIOGET_VSCREENINFO, &vinfo)) {
        perror("QLinuxFbScreen::connect");
        qWarning("Error reading variable information");
        return false;
    }

    fixupScreenInfo(finfo, vinfo);

    grayscale = vinfo.grayscale;
    d = vinfo.bits_per_pixel;
    if (d == 24) {
        d = vinfo.red.length + vinfo.green.length + vinfo.blue.length;
        if (d <= 0)
            d = 24; // reset if color component lengths are not reported
    } else if (d == 16) {
        d = vinfo.red.length + vinfo.green.length + vinfo.blue.length;
        if (d <= 0)
            d = 16;
    }
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
            if (xxoff < 0 || xxoff + w > vinfo.xres)
                xxoff = vinfo.xres - w;
            if (yyoff < 0 || yyoff + h > vinfo.yres)
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
    }

    if (w == 0 || h == 0) {
        qWarning("QScreenLinuxFb::connect(): Unable to find screen geometry, "
                 "will use 320x240.");
        dw = w = 320;
        dh = h = 240;
    }

    setPixelFormat(vinfo);

    // Handle display physical size spec.
    QStringList displayArgs = displaySpec.split(QLatin1Char(':'));
    QRegExp mmWidthRx(QLatin1String("mmWidth=?(\\d+)"));
    int dimIdxW = displayArgs.indexOf(mmWidthRx);
    QRegExp mmHeightRx(QLatin1String("mmHeight=?(\\d+)"));
    int dimIdxH = displayArgs.indexOf(mmHeightRx);
    if (dimIdxW >= 0) {
        mmWidthRx.exactMatch(displayArgs.at(dimIdxW));
        physWidth = mmWidthRx.cap(1).toInt();
        if (dimIdxH < 0)
            physHeight = dh*physWidth/dw;
    }
    if (dimIdxH >= 0) {
        mmHeightRx.exactMatch(displayArgs.at(dimIdxH));
        physHeight = mmHeightRx.cap(1).toInt();
        if (dimIdxW < 0)
            physWidth = dw*physHeight/dh;
    }
    if (dimIdxW < 0 && dimIdxH < 0) {
        if (vinfo.width != 0 && vinfo.height != 0
            && vinfo.width != UINT_MAX && vinfo.height != UINT_MAX) {
            physWidth = vinfo.width;
            physHeight = vinfo.height;
        } else {
            const int dpi = 72;
            physWidth = qRound(dw * 25.4 / dpi);
            physHeight = qRound(dh * 25.4 / dpi);
        }
    }

    dataoffset = yoff * lstep + xoff * d / 8;
    //qDebug("Using %dx%dx%d screen",w,h,d);

    /* Figure out the size of the screen in bytes */
    size = h * lstep;

    mapsize = finfo.smem_len;

    data = (unsigned char *)-1;
    if (d_ptr->fd != -1)
        data = (unsigned char *)mmap(0, mapsize, PROT_READ | PROT_WRITE,
                                     MAP_SHARED, d_ptr->fd, 0);

    if ((long)data == -1) {
        if (QApplication::type() == QApplication::GuiServer) {
            perror("QLinuxFbScreen::connect");
            qWarning("Error: failed to map framebuffer device to memory.");
            return false;
        }
        data = 0;
    } else {
        data += dataoffset;
    }

    canaccel = useOffscreen();
    if(canaccel)
        setupOffScreen();

    // Now read in palette
    if((vinfo.bits_per_pixel==8) || (vinfo.bits_per_pixel==4)) {
        screencols= (vinfo.bits_per_pixel==8) ? 256 : 16;
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
        if (d_ptr->fd == -1 || ioctl(d_ptr->fd, FBIOGETCMAP, &startcmap)) {
            perror("QLinuxFbScreen::connect");
            qWarning("Error reading palette from framebuffer, using default palette");
            createPalette(startcmap, vinfo, finfo);
        }
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