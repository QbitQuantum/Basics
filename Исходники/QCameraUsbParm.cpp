/******************************************************************************
 * Function: usbCamGetParameters
 * Description: This function allocates memory for parameter string,
 *              composes and returns the parameter string
 *
 * Input parameters:
 *   camHal             - camera HAL handle
 *
 * Return values:
 *      Address to the parameter string
 *
 * Notes: none
 *****************************************************************************/
char* usbCamGetParameters(camera_hardware_t *camHal)
{
    ALOGD("%s: E", __func__);
    char *parms = NULL;
    char* rc = NULL;
    String8 str;

    QCameraParameters qParam = camHal->qCamParams;
    //qParam.dump();
    str = qParam.flatten( );
    rc = (char *)malloc(sizeof(char)*(str.length()+1));
    if(rc != NULL){
        memset(rc, 0, sizeof(char)*(str.length()+1));
        strncpy(rc, str.string(), str.length());
    rc[str.length()] = 0;
    parms = rc;
    }

    PRINT_PARAM_STR(parms);

    ALOGD("%s: X", __func__);
    return (parms);
} /* usbCamGetParameters */