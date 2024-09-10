// Initialize camera input
bool CvCaptureCAM_PvAPI::open( int index )
{
    tPvCameraInfo cameraList[MAX_CAMERAS];

    tPvCameraInfo  camInfo;
    tPvIpSettings ipSettings;


    if (PvInitialize()) {
    }
    //return false;

    Sleep(1000);

    //close();

    int numCameras=PvCameraList(cameraList, MAX_CAMERAS, NULL);

    if (numCameras <= 0 || index >= numCameras)
        return false;

    Camera.UID = cameraList[index].UniqueId;

    if (!PvCameraInfo(Camera.UID,&camInfo) && !PvCameraIpSettingsGet(Camera.UID,&ipSettings))
    {
        /*
        struct in_addr addr;
        addr.s_addr = ipSettings.CurrentIpAddress;
        printf("Current address:\t%s\n",inet_ntoa(addr));
        addr.s_addr = ipSettings.CurrentIpSubnet;
        printf("Current subnet:\t\t%s\n",inet_ntoa(addr));
        addr.s_addr = ipSettings.CurrentIpGateway;
        printf("Current gateway:\t%s\n",inet_ntoa(addr));
        */
    }
    else
    {
        fprintf(stderr,"ERROR: could not retrieve camera IP settings.\n");
        return false;
    }


    if (PvCameraOpen(Camera.UID, ePvAccessMaster, &(Camera.Handle))==ePvErrSuccess)
    {
        tPvUint32 frameWidth, frameHeight;
        unsigned long maxSize;

        // By Default, try to set the pixel format to Mono8.  This can be changed later
        // via calls to setProperty. Some colour cameras (i.e. the Manta line) have a default
        // image mode of Bayer8, which is currently unsupported, so Mono8 is a safe bet for
        // startup.

        monocrome = (PvAttrEnumSet(Camera.Handle, "PixelFormat", "Mono8") == ePvErrSuccess);

        PvAttrUint32Get(Camera.Handle, "Width", &frameWidth);
        PvAttrUint32Get(Camera.Handle, "Height", &frameHeight);

        // Determine the maximum packet size supported by the system (ethernet adapter)
        // and then configure the camera to use this value.  If the system's NIC only supports
        // an MTU of 1500 or lower, this will automatically configure an MTU of 1500.
        // 8228 is the optimal size described by the API in order to enable jumbo frames

        maxSize = 8228;
        //PvAttrUint32Get(Camera.Handle,"PacketSize",&maxSize);
        if (PvCaptureAdjustPacketSize(Camera.Handle,maxSize)!=ePvErrSuccess)
            return false;

        resizeCaptureFrame(frameWidth, frameHeight);

        return startCapture();

    }
    fprintf(stderr,"Error cannot open camera\n");
    return false;

}