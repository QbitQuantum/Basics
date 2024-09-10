/*******************************************************************************************
    Video capture routines

 - set input
 - setup_pixelformat
 - set_geometry

 - set_brightness
 - set_chroma
 - set_contrast
 - set_channelset
 - set_channel
 - set_capture_mode

*/
static unsigned char *v4l_start(struct video_dev *viddev, int width, int height,
                                unsigned input, unsigned norm, unsigned long freq)
{
    int dev_bktr = viddev->fd_bktr;
    struct sigaction act, old;
    //int dev_tunner = viddev->fd_tuner;
    /* to ensure that all device will be support the capture mode
      _TODO_ : Autodected the best capture mode .
    */
    int dummy = 1;
    //    int pixelformat = BSD_VIDFMT_I420;

    void *map;

    /* If we have choose the tuner is needed to setup the frequency. */
    if ((viddev->tuner_device != NULL) && (input == IN_TV)) {
        if (!freq) {
            MOTION_LOG(WRN, TYPE_VIDEO, NO_ERRNO, "%s: Not valid Frequency [%lu] for "
                       "Source input [%i]", freq, input);
            return NULL;
        } else if (set_freq(viddev, freq) == -1) {
            MOTION_LOG(NTC, TYPE_VIDEO, NO_ERRNO, "%s: Frequency [%lu] Source input [%i]",
                       freq, input);
            return NULL;
        }
    }

    /* FIXME if we set as input tuner , we need to set option for tuner not for bktr */
    if ((dummy = set_input(viddev, input)) == -1) {
        MOTION_LOG(NTC, TYPE_VIDEO, NO_ERRNO, "%s: set input [%d]", input);
        return NULL;
    }

    viddev->input = dummy;

    if ((dummy = set_input_format(viddev, norm)) == -1) {
        MOTION_LOG(NTC, TYPE_VIDEO, NO_ERRNO, "%s: set input format [%d]",
                   norm);
        return NULL;
    }

    viddev->norm = dummy;

    if (set_geometry(viddev, width, height) == -1) {
        MOTION_LOG(NTC, TYPE_VIDEO, NO_ERRNO, "%s: set geometry [%d]x[%d]",
                   width, height);
        return NULL;
    }

    /*
    if (ioctl(dev_bktr, METEORSACTPIXFMT, &pixelformat) < 0) {
        MOTION_LOG(ERR, TYPE_VIDEO, SHOW_ERRNO, "%s: set encoding method BSD_VIDFMT_I420");
        return NULL;
    }

    NEEDED !? FIXME

    if (setup_pixelformat(viddev) == -1)
        return NULL;
    */

    if (freq) {
        MOTION_LOG(WRN, TYPE_VIDEO, NO_ERRNO, "%s: Frequency set (no implemented yet");
    /*
     TODO missing implementation
        set_channelset(viddev);
        set_channel(viddev);
        if (set_freq (viddev, freq) == -1)
            return NULL;
    */

    }

    /*
     * Set capture mode and capture buffers
     * That is the buffer size for capture images ,
     * so is dependent of color space of input format / FIXME
     */
    viddev->v4l_bufsize = (((width * height * 3 / 2)) * sizeof(unsigned char));
    viddev->v4l_fmt = VIDEO_PALETTE_YUV420P;


    map = mmap((caddr_t)0, viddev->v4l_bufsize, PROT_READ|PROT_WRITE, MAP_SHARED,
               dev_bktr, (off_t)0);

    if (map == MAP_FAILED) {
        MOTION_LOG(ERR, TYPE_VIDEO, SHOW_ERRNO, "%s: mmap failed");
        return NULL;
    }

    /* FIXME double buffer */
    if (0) {
        viddev->v4l_maxbuffer = 2;
        viddev->v4l_buffers[0] = map;
        viddev->v4l_buffers[1] = (unsigned char *)map + 0; /* 0 is not valid just a test */
        //viddev->v4l_buffers[1] = map+vid_buf.offsets[1];
    } else {
        viddev->v4l_buffers[0] = map;
        viddev->v4l_maxbuffer = 1;
    }

    viddev->v4l_curbuffer = 0;

    /* Clear the buffer */
    if (ioctl(dev_bktr, BT848SCBUF, &dummy) < 0) {
        MOTION_LOG(ERR, TYPE_VIDEO, SHOW_ERRNO, "%s: BT848SCBUF");
        return NULL;
    }

    /* Signal handler to know when data is ready to be read() */
    memset(&act, 0, sizeof(act));
    sigemptyset(&act.sa_mask);
    act.sa_handler = catchsignal;
    sigaction(SIGUSR2, &act, &old);

    dummy = SIGUSR2;

    //viddev->capture_method = METEOR_CAP_CONTINOUS;
    //viddev->capture_method = METEOR_CAP_SINGLE;

    if ((viddev->capture_method == METEOR_CAP_CONTINOUS) &&
        (ioctl(dev_bktr, METEORSSIGNAL, &dummy) < 0)) {
        MOTION_LOG(NTC, TYPE_VIDEO, NO_ERRNO, "%s: METEORSSIGNAL");

        viddev->capture_method = METEOR_CAP_SINGLE;

        if (ioctl(dev_bktr, METEORCAPTUR, &viddev->capture_method) < 0) {
            MOTION_LOG(ERR, TYPE_VIDEO, SHOW_ERRNO, "%s: METEORCAPTUR using single method "
                       "Error capturing");
            MOTION_LOG(NTC, TYPE_VIDEO, NO_ERRNO, "%s: METEORCAPTUR using single method "
                       "Error capturing");
        }
    } else {
        if (ioctl(dev_bktr, METEORCAPTUR, &viddev->capture_method) < 0) {
            viddev->capture_method = METEOR_CAP_SINGLE;

            if (ioctl(dev_bktr, METEORCAPTUR, &viddev->capture_method) < 0) {
                MOTION_LOG(ERR, TYPE_VIDEO, SHOW_ERRNO, "%s: METEORCAPTUR using single method "
                           "Error capturing");
            }
        }
    }

    if (viddev->capture_method == METEOR_CAP_CONTINOUS)
        MOTION_LOG(NTC, TYPE_VIDEO, NO_ERRNO, "%s: METEORCAPTUR METEOR_CAP_CONTINOUS");
    else
        MOTION_LOG(NTC, TYPE_VIDEO, NO_ERRNO, "%s: METEORCAPTUR METEOR_CAP_SINGLE");

    // settle , sleep(1) replaced
    SLEEP(1, 0);

    /* FIXME */
    switch (viddev->v4l_fmt) {
    case VIDEO_PALETTE_YUV420P:
        viddev->v4l_bufsize = (width * height * 3) / 2;
        break;
    case VIDEO_PALETTE_YUV422:
        viddev->v4l_bufsize = (width * height * 2);
        break;
    case VIDEO_PALETTE_RGB24:
        viddev->v4l_bufsize = (width * height * 3);
        break;
    case VIDEO_PALETTE_GREY:
        viddev->v4l_bufsize = width * height;
        break;
    }

    MOTION_LOG(NTC, TYPE_VIDEO, NO_ERRNO, "%s: HUE [%d]",
               get_hue(dev_bktr, &dummy));
    MOTION_LOG(NTC, TYPE_VIDEO, NO_ERRNO, "%s: SATURATION [%d]",
               get_saturation(dev_bktr, &dummy));
    MOTION_LOG(NTC, TYPE_VIDEO, NO_ERRNO, "%s: BRIGHTNESS [%d]",
               get_brightness(dev_bktr, &dummy));
    MOTION_LOG(NTC, TYPE_VIDEO, NO_ERRNO, "%s: CONTRAST [%d]",
               get_contrast(dev_bktr, &dummy));

    return map;
}