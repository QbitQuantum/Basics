/* Initialize the /dev/fbN device for a specific screen */
static int pvrQwsInitFbScreen(int screen)
{
    struct fb_var_screeninfo var;
    struct fb_fix_screeninfo fix;
    unsigned long start;
    unsigned long length;
    int width, height, stride;
    PVR2DFORMAT format;
    void *mapped;
    int fd, bytesPerPixel;
    char name[64];
    PVR2DMEMINFO *memInfo;
    unsigned long pageAddresses[2];

    /* Bail out if already initialized, or the number is incorrect */
    if (screen < 0 || screen >= PVRQWS_MAX_SCREENS)
        return 0;
    if (pvrQwsDisplay.screens[screen].initialized)
        return 1;

    /* Open the framebuffer and fetch its properties */
    sprintf(name, "/dev/fb%d", screen);
    fd = open(name, O_RDWR, 0);
    if (fd < 0) {
        perror(name);
        return 0;
    }
    if (ioctl(fd, FBIOGET_VSCREENINFO, &var) < 0) {
        perror("FBIOGET_VSCREENINFO");
        close(fd);
        return 0;
    }
    if (ioctl(fd, FBIOGET_FSCREENINFO, &fix) < 0) {
        perror("FBIOGET_FSCREENINFO");
        close(fd);
        return 0;
    }
    width = var.xres;
    height = var.yres;
    bytesPerPixel = var.bits_per_pixel / 8;
    stride = fix.line_length;
    format = PVR2D_1BPP;
    if (var.bits_per_pixel == 16) {
        if (var.red.length == 5 && var.green.length == 6 &&
            var.blue.length == 5 && var.red.offset == 11 &&
            var.green.offset == 5 && var.blue.offset == 0) {
            format = PVR2D_RGB565;
        }
        if (var.red.length == 4 && var.green.length == 4 &&
            var.blue.length == 4 && var.transp.length == 4 &&
            var.red.offset == 8 && var.green.offset == 4 &&
            var.blue.offset == 0 && var.transp.offset == 12) {
            format = PVR2D_ARGB4444;
        }
    } else if (var.bits_per_pixel == 32) {
        if (var.red.length == 8 && var.green.length == 8 &&
            var.blue.length == 8 && var.transp.length == 8 &&
            var.red.offset == 16 && var.green.offset == 8 &&
            var.blue.offset == 0 && var.transp.offset == 24) {
            format = PVR2D_ARGB8888;
        }
    }
    if (format == PVR2D_1BPP) {
        fprintf(stderr, "%s: could not find a suitable PVR2D pixel format\n", name);
        close(fd);
        return 0;
    }
    start = fix.smem_start;
    length = var.xres_virtual * var.yres_virtual * bytesPerPixel;

    if (screen == 0) {
        /* We use PVR2DGetFrameBuffer to map the first screen.
           On some chipsets it is more reliable than using PVR2DMemWrap */
        mapped = 0;
        memInfo = 0;
    } else {
        /* Other screens: map the framebuffer region into memory */
        mapped = mmap(0, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (!mapped || mapped == (void *)(-1)) {
            perror("mmap");
            close(fd);
            return 0;
        }

        /* Allocate a PVR2D memory region for the framebuffer */
        memInfo = 0;
        if (pvrQwsDisplay.context) {
            pageAddresses[0] = start & 0xFFFFF000;
            pageAddresses[1] = 0;
            if (PVR2DMemWrap
                    (pvrQwsDisplay.context, mapped, PVR2D_WRAPFLAG_CONTIGUOUS,
                     length, pageAddresses, &memInfo) != PVR2D_OK) {
                munmap(mapped, length);
                close(fd);
                return 0;
            }
        }
    }

    /* We don't need the file descriptor any more */
    close(fd);

    /* The framebuffer is ready, so initialize the PvrQwsScreenInfo */
    pvrQwsDisplay.screens[screen].screenRect.x = 0;
    pvrQwsDisplay.screens[screen].screenRect.y = 0;
    pvrQwsDisplay.screens[screen].screenRect.width = width;
    pvrQwsDisplay.screens[screen].screenRect.height = height;
    pvrQwsDisplay.screens[screen].screenStride = stride;
    pvrQwsDisplay.screens[screen].pixelFormat = format;
    pvrQwsDisplay.screens[screen].bytesPerPixel = bytesPerPixel;
    pvrQwsDisplay.screens[screen].screenDrawable = 0;
    if (mapped) {
        /* Don't set these fields if mapped is 0, because PVR2DGetFrameBuffer
           may have already been called and set them */
        pvrQwsDisplay.screens[screen].frameBuffer = memInfo;
        pvrQwsDisplay.screens[screen].mapped = mapped;
    }
    pvrQwsDisplay.screens[screen].mappedLength = length;
    pvrQwsDisplay.screens[screen].screenStart = start;
    pvrQwsDisplay.screens[screen].needsUnmap = (mapped != 0);
    pvrQwsDisplay.screens[screen].initialized = 1;
    return 1;
}