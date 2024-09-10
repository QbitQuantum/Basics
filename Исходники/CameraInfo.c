static BOOL ProcessData(void)
{
    // Loop through any new incoming packets
    while (OrionCommReceive(&PktIn))
    {
        // If this is a response to the request we just sent
        if (PktIn.ID == getOrionCamerasPacketID())
        {
            OrionCameras_t Cameras;

            // If the cameras packet decodes properly
            if (decodeOrionCamerasPacketStructure(&PktIn, &Cameras))
            {
                int i;

                // Print a header row to stdout
                printf(" Index  Type     Zoom  WFOV  NFOV\n");
                printf("----------------------------------\n");

                // Loop through each camera in the array
                for (i = 0; i < Cameras.NumCameras; i++)
                {
                    OrionCamSettings_t *pSettings = &Cameras.OrionCamSettings[i];
                    float ArraySize = pSettings->PixelPitch * pSettings->ArrayWidth;
                    float Zoom = 1.0f, Wfov, Nfov;
                    char TypeString[16];

                    // If this camera doesn't exist, skip it
                    if (pSettings->Type == CAMERA_TYPE_NONE)
                        continue;

                    // Build a type string based on the type enumeration
                    switch (pSettings->Type)
                    {
                    case CAMERA_TYPE_VISIBLE: strcpy(TypeString, "Visible"); break;
                    case CAMERA_TYPE_SWIR:    strcpy(TypeString, "SWIR");    break;
                    case CAMERA_TYPE_MWIR:    strcpy(TypeString, "MWIR");    break;
                    case CAMERA_TYPE_LWIR:    strcpy(TypeString, "LWIR");    break;
                    default:                  strcpy(TypeString, "Unknown"); break;
                    }

                    // Calculate max zoom ratio for use in OrionCameraState, avoiding (unlikely) divide by zero
                    if (pSettings->MinFocalLength > 0)
                        Zoom = pSettings->MaxFocalLength / pSettings->MinFocalLength;

                    // Compute wide and narrow horizontal FOV in radians
                    Wfov = atan2f(0.5f * ArraySize, pSettings->MinFocalLength) * 2.0f;
                    Nfov = atan2f(0.5f * ArraySize, pSettings->MaxFocalLength) * 2.0f;

                    // Print the index, type, max zoom, and min/max FOV in degrees for this camera
                    printf(" %5d  %-7s %5.1f %5.1f %5.1f\n", i, TypeString, Zoom, degreesf(Wfov), degreesf(Nfov));
                }

                // Packet decoded: Mission accomplished
                return TRUE;
            }
        }
    }

    // Haven't gotten the response we're looking for yet
    return FALSE;

}// ProcessData