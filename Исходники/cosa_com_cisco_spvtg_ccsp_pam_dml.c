ANSC_STATUS
Pam_GetFirstIpInterfaceObjectName
(
    BOOL                        bUpstream,
    char*                       pIfObjName,
    PULONG                      pulObjNameSize
)
{
    ANSC_STATUS                     returnStatus        = ANSC_STATUS_CANT_FIND;
    int                             iReturnValue        = 0;
    ULONG                           ulTotal             = 0;
    ULONG                           ulIndex             = 0;
    ULONG                           ulInstNum           = 0;
    ULONG                           ulLen               = 0;
    char                            pObjName[256]       = {0};
    char                            Buffer[128]         = {0};
    ULONG                           BufferSize          = 0;
    char                            LowerLayers[256]    = {0};
    ULONG                           LowerLayersSize     = 0;
    BOOL                            bLowerLayerUpstream = FALSE;
    char*                           EnvIndex            = NULL;
    ULONG                           ulEnvIndex          = PAM_MAX_IP_INTERFACE_NUM;

#ifdef _COSA_SIM_
    // Hard coded, RTian 09/20/2013
    {
        if(bUpstream) {
            pulObjNameSize = sprintf(pIfObjName, "Device.IP.Interface.1.") + 1;
            //        else pulObjNameSize = sprintf(pIfObjName, "Device.IP.Interface.4.") + 1;
            return ANSC_STATUS_SUCCESS;
        }
    }
#endif

    ulTotal = CosaGetParamValueUlong("Device.IP.InterfaceNumberOfEntries");

    EnvIndex = getenv(PAM_FIRST_IP_INTERFACE);
    if(EnvIndex != NULL)
    {
        ulEnvIndex = atol(EnvIndex);
    }

    for ( ulIndex = 0; ulIndex < ulTotal; ulIndex++ )
    {
        if(EnvIndex != NULL && ulEnvIndex < PAM_MAX_IP_INTERFACE_NUM)
        {
            ulInstNum = CosaGetInstanceNumberByIndex("Device.IP.Interface.", ulEnvIndex);
            if( 0 == ulInstNum)
            {
                EnvIndex    = NULL;
                ulEnvIndex  = PAM_MAX_IP_INTERFACE_NUM;
            }
            else
            {
                ulIndex     = EnvIndex;
            }
        }
        ulInstNum = CosaGetInstanceNumberByIndex("Device.IP.Interface.", ulIndex);

        if ( 0 == ulInstNum )
        {
            CcspTraceWarning(("Pam_GetFirstIpInterfaceObjectName -- invalid Device.IP.Interface instance number!\n"));
            returnStatus = ANSC_STATUS_FAILURE;
            break;
        }
        else
        {
            _ansc_sprintf(pObjName, "Device.IP.Interface.%d.LowerLayers", ulInstNum);
            /*CcspTraceInfo(("Checking %s...\n", pObjName));*/

            LowerLayersSize = sizeof(LowerLayers);
            iReturnValue    = CosaGetParamValueString(pObjName, LowerLayers, &LowerLayersSize);

            if ( iReturnValue != 0 )
            {
                returnStatus = ANSC_STATUS_FAILURE;
                break;
            }
            else if ( LowerLayersSize == 0 )
            {
                continue;
            }

            do
            {
                /*
                 *  We have to check whether LowerLayers is a partial object name (without '.' at the end) or not
                 *  Assuming only one lower layer value for now
                 *  Look for the LowerLayer with a empty LowerLayers parameter
                 */
                ulLen = _ansc_strlen(LowerLayers);

                if ( LowerLayers[ulLen - 1] == '.' )
                {
                    LowerLayers[ulLen - 1] = '\0';
                }

                _ansc_strcpy (pObjName, LowerLayers);
                _ansc_sprintf(Buffer, "%s.LowerLayers", LowerLayers);

                CcspTraceInfo(("Checking %s...\n", Buffer));

                LowerLayersSize = sizeof(LowerLayers);
                iReturnValue    = CosaGetParamValueString(Buffer, LowerLayers, &LowerLayersSize);

                if ( iReturnValue != 0 )
                {
                    break;
                }
                else if ( LowerLayersSize == 0 )
                {
                    break;
                }
            }
            while (TRUE);

            /*
             *  Check the Upstream parameter.
             *  Note, not all error cases are covered well here, which happened to help to pass the test
             *  on DRG -- LowerLayers parameter of IP.Interface on top of Bridge.1 is not actually correct.
             */
            _ansc_sprintf(Buffer, "%s.Upstream", pObjName);
            bLowerLayerUpstream = CosaGetParamValueBool(Buffer);

            if ( bUpstream == bLowerLayerUpstream )
            {
                CcspTraceInfo
                ((
                     "Found the lowest %s layer %s for IP interface Device.IP.Interface.%d.\n",
                     bUpstream ? "upstream" : "downstream",
                     LowerLayers,
                     ulInstNum
                 ));

                _ansc_sprintf(Buffer, "Device.IP.Interface.%d.", ulInstNum);
                BufferSize = _ansc_strlen(Buffer);

                if ( BufferSize < *pulObjNameSize )
                {
                    AnscCopyString(pIfObjName, Buffer);
                    *pulObjNameSize = BufferSize;
                    returnStatus    = ANSC_STATUS_SUCCESS;
                }
                else
                {
                    *pulObjNameSize = BufferSize;
                    returnStatus = ANSC_STATUS_MORE_DATA;
                }

                break;
            }
        }
    }

    return  returnStatus;
}