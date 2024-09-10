RTP_BOOL SH7264_SMSC_open(PIFACE pi)   
{
    DWORD mac[2], dwCnt, dwReg, dw; 
    PSH7264_SMSC_SOFTC sc = iface_to_softc(pi);

    if (!sc)
    {
        RTP_DEBUG_ERROR("SH7264_SMSC_open: softc invalid!\r\n", NOVAR, 0, 0);
        set_errno(ENUMDEVICE);
        return(RTP_FALSE);
    }

    // Set Interface
    sc->iface = pi;
    iface = pi;

    //Setting port
    PJCR0 |= 0x3300;
    
    if (WORD_SWAP != 0xFFFFFFFF)    //Need at least one read from LAN chip before writing to WORD_SWAP register
    {
        WORD_SWAP = 0xFFFFFFFF;
    }
    
    ETHERNET_DELAY(10000);

    // soft reset
    HW_CFG = HWCFG_SRST;
    
    dwCnt = 100000;
    do
    {
        ETHERNET_DELAY(10);
        dwReg = HW_CFG;
        dwCnt--;
    }while ((dwCnt > 0) && (dwReg & HWCFG_SRST));
    
    if (dwReg & HWCFG_SRST)
    {
        debug_printf("SH7264_SMSC_open: Error in Soft reset.\r\n");
        return;
    }

    ETHERNET_DELAY(10000);
    
    //Read Mac address from EEPROM          
    mac[0]  = BIT_EDIANDW(SMSC9218_Read_Mac_Reg(ADDRL));
    mac[1]  = BIT_EDIANDW(SMSC9218_Read_Mac_Reg(ADDRH));
    
    int macLen = __min(g_NetworkConfig.NetworkInterfaces[NETWORK_INTERFACE_INDEX_SH7264RSK].macAddressLen, sizeof(sc->mac_address));
    
    dw = (DWORD)&g_NetworkConfig.NetworkInterfaces[NETWORK_INTERFACE_INDEX_SH7264RSK].macAddressBuffer[0];
    if (((dw >= 0x00000000) && (dw <= 0x03000000)) || ((dw >= 0x20000000) && (dw <= 0x23000000)))
    {
        g_AM29DL_16_BS_DeviceTable.InitializeDevice(pBLOCK_CONFIG);
        g_AM29DL_16_BS_DeviceTable.Write(pBLOCK_CONFIG,(DWORD)&g_NetworkConfig.NetworkInterfaces[NETWORK_INTERFACE_INDEX_SH7264RSK].macAddressBuffer[0],6,(BYTE *)mac,TRUE);
    }
    else
    {
        memcpy((void *)&g_NetworkConfig.NetworkInterfaces[NETWORK_INTERFACE_INDEX_SH7264RSK].macAddressBuffer[0], (void *)&mac[0], 6);
    }
    if(macLen > 0)
    {
        memcpy(&sc->mac_address[0], &g_NetworkConfig.NetworkInterfaces[NETWORK_INTERFACE_INDEX_SH7264RSK].macAddressBuffer[0], macLen);
    }
    else
    {
        RTP_DEBUG_ERROR("Device initialize without MAC address!!!\r\n", NOVAR, 0, 0);
    }
        
    // Now put in a dummy ethernet address
    rtp_memcpy(&pi->addr.my_hw_addr[0], sc->mac_address, 6); // Get the ethernet address
    
    // clear statistic information
    sc->stats.packets_in     = 0L;
    sc->stats.packets_out    = 0L;
    sc->stats.bytes_in       = 0L;
    sc->stats.bytes_out      = 0L;
    sc->stats.errors_in      = 0L;
    sc->stats.errors_out     = 0L;    

    if(RTP_FALSE == SH7264_SMSC_SetupDevice())
    {
        return RTP_FALSE;
    }
    
    rtp_irq_hook_interrupt( (RTP_PFVOID) pi, 
                            (RTP_IRQ_FN_POINTER)SH7264_SMSC_recv, 
                            (RTP_IRQ_FN_POINTER) 0);

    return(RTP_TRUE);
}