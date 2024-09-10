void AT91_USBHS_Driver::Global_ISR( void* Param )
{
    struct AT91_UDPHS *pUdp = (struct AT91_UDPHS *) (AT91C_BASE_UDP);

    UINT32 USB_INTR = (pUdp->UDPHS_INTSTA & pUdp->UDPHS_IEN);
    UINT32 endpoint  = 0;

//    debug_printf("%x", USB_INTR);
    // Handle all UDP interrupts
    while(USB_INTR != 0)
    {
        // Start Of Frame (SOF)
        if(USB_INTR & AT91C_UDPHS_IEN_SOF)
        {

            // Acknowledge interrupt
            pUdp->UDPHS_CLRINT = AT91C_UDPHS_IEN_SOF;
            USB_INTR &= ~AT91C_UDPHS_IEN_SOF;
            // This interrupt should not happen, as it is not enabled.
            
            ASSERT(0);
        }

        // Suspend
        if (USB_INTR & AT91C_UDPHS_DET_SUSPD)
        {
            AT91_PMC_DisableUTMIBIAS();
            // Acknowledge interrupt
            pUdp->UDPHS_CLRINT  = AT91C_UDPHS_DET_SUSPD | AT91C_UDPHS_WAKE_UP;
            USB_INTR &= ~AT91C_UDPHS_DET_SUSPD;
            
            SuspendEvent();        
        }

        // Resume or Wakeup
        if((USB_INTR & AT91C_UDPHS_WAKE_UP) ||(USB_INTR & AT91C_UDPHS_ENDOFRSM))
        {
            ResumeEvent();

            // Acknowledge interrupt
            pUdp->UDPHS_CLRINT = AT91C_UDPHS_WAKE_UP | AT91C_UDPHS_ENDOFRSM;
            USB_INTR &= ~(AT91C_UDPHS_WAKE_UP | AT91C_UDPHS_ENDOFRSM);
        }

        // End of bus reset
        if(USB_INTR & AT91C_UDPHS_ENDRESET)
        {
            // Acknowledge end of bus reset interrupt
            

            ResetEvent();
            pUdp->UDPHS_CLRINT = AT91C_UDPHS_WAKE_UP | AT91C_UDPHS_DET_SUSPD | AT91C_UDPHS_ENDRESET;
            pUdp->UDPHS_IEN |= AT91C_UDPHS_DET_SUSPD;

            USB_INTR &= ~AT91C_UDPHS_ENDRESET;
        }
        
        if(USB_INTR & AT91C_UDPHS_UPSTR_RES)
        {
            pUdp->UDPHS_CLRINT = AT91C_UDPHS_UPSTR_RES;
            USB_INTR &= ~AT91C_UDPHS_UPSTR_RES;
        }
        else //Endpoint Interrupt
        {
            UINT32 i = 0;
            USB_INTR >>= 8;
            while(USB_INTR != 0)
            {
                if (USB_INTR & 1)
                {
                        
                    endpoint  = i;
                    Endpoint_ISR(endpoint);
                    if (endpoint == 1)
                    {
//                        debug_printf("1\r\n");
//                        num_ep_int1 += 1;
                    }
                    if (endpoint == 2)
                    {
//                        debug_printf("2\r\n");
//                        num_ep_int2 += 1;
                    }
                    
                }
                USB_INTR >>= 1;
                i++;
            }
        }
        USB_INTR = pUdp->UDPHS_INTSTA & pUdp->UDPHS_IEN;
    }
}