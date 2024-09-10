webcam::webcam(uint w, uint h, const std::string & device) : 
    width(w),
    height(h),
    device(device)
   
{
    struct stat st;
    if(stat(device.c_str(), &st) < 0) TERMINATE("can't find " + device);
    if(!S_ISCHR(st.st_mode)) TERMINATE(device + " is no device"); 
    fd = open(device.c_str(), O_RDWR | O_NONBLOCK, 0);
    if (fd < 0) TERMINATE ("can't open " + device);
    
    v4l2_capability cap;
    v4l2_cropcap    cropcap;
    v4l2_crop       crop;
    v4l2_format     fmt;

    if (IO_CTL(fd, VIDIOC_QUERYCAP, &cap) < 0)        TERMINATE("QUERYCAR request error");
    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) TERMINATE(device + " is not capture device");
    if (!(cap.capabilities & V4L2_CAP_STREAMING))     TERMINATE(device + " does not support streaming i/o");

    CLEAR(cropcap);
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (IO_CTL(fd, VIDIOC_CROPCAP, &cropcap) == 0) 
    {
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect;
        IO_CTL(fd, VIDIOC_S_CROP, &crop);
    }    
    CLEAR(fmt);
    fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width       = width;
    fmt.fmt.pix.height      = height;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    fmt.fmt.pix.field       = V4L2_FIELD_ANY;
    if (IO_CTL(fd, VIDIOC_S_FMT, &fmt) < 0) TERMINATE("can't set capture format");

    v4l2_requestbuffers req;
    CLEAR(req);

    req.count   = 4;
    req.type    = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory  = V4L2_MEMORY_MMAP;

    if(IO_CTL(fd, VIDIOC_REQBUFS, &req) < 0) TERMINATE("memory mapping not supported"); 
    if(req.count < 2) TERMINATE("insufficient buffer memory ");

    buffers = static_cast<buffer *>(calloc(req.count, sizeof(*buffers)));
    if(!buffers) TERMINATE("out of memory!");
    for(n_buffers = 0; n_buffers < req.count; ++n_buffers) 
    {
        v4l2_buffer buf;
        CLEAR(buf);

        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = n_buffers;

        if(IO_CTL(fd, VIDIOC_QUERYBUF, &buf) < 0) TERMINATE("can't create buffers");
        buffers[n_buffers].length = buf.length;
        buffers[n_buffers].start = mmap(NULL,buf.length,PROT_READ|PROT_WRITE,MAP_SHARED,fd, buf.m.offset);
        if (MAP_FAILED == buffers[n_buffers].start) TERMINATE("mmap");
    }
}