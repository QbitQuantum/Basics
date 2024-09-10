/**
* \brief         This function will get the hardware selection from the user
*                and will create essential networks.
* \param         unDefaultChannelCnt
* \return        returns defERR_OK (always)
* \authors       [email protected]
* \date          05.29.2015 Created
*/
static int nCreateMultipleHardwareNetwork(UINT unDefaultChannelCnt = 0)
{
    int nHwCount = sg_ucNoOfHardware;
    DWORD dwFirmWare[2];
    char chBuffer[512] = "";
    std::string name;
    int i = 0;
    // Get Hardware Network Map
    for (int nCount = 0; nCount < nHwCount; nCount++)
    {
        canGetChannelData(nCount, canCHANNELDATA_CHANNEL_NAME,
                          chBuffer, sizeof(chBuffer));
        name = chBuffer;

        if(name.find(" LIN ",0)!=std::string::npos)
        {
            sg_HardwareIntr[nCount].m_acDescription = chBuffer;

            sg_HardwareIntr[nCount].m_dwIdInterface = i;

            canGetChannelData(nCount, canCHANNELDATA_CARD_SERIAL_NO,
                              chBuffer, sizeof(chBuffer));
            sscanf_s( chBuffer, "%ld", &sg_HardwareIntr[nCount].m_dwVendor );

            //Get Firmware info
            canGetChannelData(nCount, canCHANNELDATA_CARD_FIRMWARE_REV, dwFirmWare, sizeof(dwFirmWare));

            sprintf_s(chBuffer, sizeof(chBuffer), "0x%08lx 0x%08lx", dwFirmWare[0], dwFirmWare[1]);
            sg_HardwareIntr[nCount].m_acDeviceName = chBuffer;
            //sprintf(sg_HardwareIntr[nCount].m_acDeviceName,"0x%08lx 0x%08lx", dwFirmWare[0], dwFirmWare[1]);

            canGetChannelData(nCount, canCHANNELDATA_CHANNEL_FLAGS, chBuffer, sizeof(chBuffer));
            i++;
        }
    }
    nHwCount = i;

    /* If the default channel count parameter is set, prevent displaying the hardware selection dialog */
    if ( unDefaultChannelCnt && nHwCount >= unDefaultChannelCnt )
    {
        for (UINT i = 0; i < unDefaultChannelCnt; i++)
        {
            sg_anSelectedItems[i] = i;
        }
        nHwCount = unDefaultChannelCnt;
    }
    else if ( ListHardwareInterfaces(sg_hOwnerWnd, DRIVER_LIN_KVASER, sg_HardwareIntr, sg_anSelectedItems, nHwCount) != 0 )
    {
        return HW_INTERFACE_NO_SEL;
    }
    sg_ucNoOfHardware = (UCHAR)nHwCount;
    sg_nNoOfChannels = (UINT)nHwCount;

    //Reorder hardware interface as per the user selection
    for (int nCount = 0; nCount < sg_ucNoOfHardware; nCount++)
    {
        sg_aodChannels[nCount].m_nChannel = sg_HardwareIntr[sg_anSelectedItems[nCount]].m_dwIdInterface;
        sprintf(sg_aodChannels[nCount].m_strName , _("Kvaser - %s, Serial Number- %ld, Firmware- %s"),
                sg_HardwareIntr[sg_anSelectedItems[nCount]].m_acDescription.c_str(),
                sg_HardwareIntr[sg_anSelectedItems[nCount]].m_dwVendor,
                sg_HardwareIntr[sg_anSelectedItems[nCount]].m_acDeviceName.c_str());
    }

    return defERR_OK;
}