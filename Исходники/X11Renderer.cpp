    bool ensureImage(int w, int h) {
        if (ximage && ximage->width == w && ximage->height == h)
            return true;
        warn_bad_pitch = true;
        destroyX11Image();
        use_shm = XShmQueryExtension(display);
        qDebug("use x11 shm: %d", use_shm);
        if (!use_shm)
            goto no_shm;
        // data seems not aligned
        ximage = XShmCreateImage(display, vinfo.visual, depth, ZPixmap, NULL, &shm, w, h);
        if (!ximage) {
            qWarning("XShmCreateImage error");
            goto no_shm;
        }
        shm.shmid = shmget(IPC_PRIVATE, ximage->bytes_per_line*ximage->height, IPC_CREAT | 0777);
        if (shm.shmid < 0) {
            qWarning("shmget error");
            goto no_shm;
        }
        shm.shmaddr = (char *)shmat(shm.shmid, 0, 0);
        if (shm.shmaddr == (char*)-1) {
            if (!ximage_data.isEmpty())
                   ximage->data = NULL;
            XDestroyImage(ximage);
            ximage = NULL;
            ximage_data.clear();
            qWarning("Shared memory error,disabling ( seg id error )");
            goto no_shm;
        }
        ximage->data = shm.shmaddr;
        shm.readOnly = False;
        if (!XShmAttach(display, &shm)) {
            qWarning("Attach to shm failed! try to use none shm");
            goto no_shm;
        }
        XSync(display, False);
        shmctl(shm.shmid, IPC_RMID, 0);
        pixfmt = pixelFormat(ximage);
        return true;
no_shm:
        ximage = XCreateImage(display, vinfo.visual, depth, ZPixmap, 0, NULL, w, h, 8, 0);
        if (!ximage)
            return false;
        pixfmt = pixelFormat(ximage);
        ximage->data = NULL;
        XSync(display, False);
        // TODO: align 16 or?
        ximage_data.resize(ximage->bytes_per_line*ximage->height + 32);
        return true;
    }