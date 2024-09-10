void     MsiPciConfigWrite(PPDMDEVINS pDevIns, PCPDMPCIHLP pPciHlp, PPCIDEVICE pDev, uint32_t u32Address, uint32_t val, unsigned len)
{
    int32_t iOff = u32Address - pDev->Int.s.u8MsiCapOffset;
    Assert(iOff >= 0 && (pciDevIsMsiCapable(pDev) && iOff < pDev->Int.s.u8MsiCapSize));

    Log2(("MsiPciConfigWrite: %d <- %x (%d)\n", iOff, val, len));

    uint32_t uAddr = u32Address;
    bool f64Bit = msiIs64Bit(pDev);

    for (uint32_t i = 0; i < len; i++)
    {
        uint32_t reg = i + iOff;
        uint8_t u8Val = (uint8_t)val;
        switch (reg)
        {
            case 0: /* Capability ID, ro */
            case 1: /* Next pointer,  ro */
                break;
            case VBOX_MSI_CAP_MESSAGE_CONTROL:
                /* don't change read-only bits: 1-3,7 */
                u8Val &= UINT8_C(~0x8e);
                pDev->config[uAddr] = u8Val | (pDev->config[uAddr] & UINT8_C(0x8e));
                break;
            case VBOX_MSI_CAP_MESSAGE_CONTROL + 1:
                /* don't change read-only bit 8, and reserved 9-15 */
                break;
            default:
                if (pDev->config[uAddr] != u8Val)
                {
                    int32_t maskUpdated = -1;

                    /* If we're enabling masked vector, and have pending messages
                       for this vector, we have to send this message now */
                    if (    !f64Bit
                         && (reg >= VBOX_MSI_CAP_MASK_BITS_32)
                         && (reg < VBOX_MSI_CAP_MASK_BITS_32 + 4)
                        )
                    {
                        maskUpdated = reg - VBOX_MSI_CAP_MASK_BITS_32;
                    }
                    if (    f64Bit
                         && (reg >= VBOX_MSI_CAP_MASK_BITS_64)
                         && (reg < VBOX_MSI_CAP_MASK_BITS_64 + 4)
                       )
                    {
                        maskUpdated = reg - VBOX_MSI_CAP_MASK_BITS_64;
                    }

                    if (maskUpdated != -1 && msiIsEnabled(pDev))
                    {
                        uint32_t*  puPending = msiGetPendingBits(pDev);
                        for (int iBitNum = 0; iBitNum < 8; iBitNum++)
                        {
                            int32_t iBit = 1 << iBitNum;
                            uint32_t uVector = maskUpdated*8 + iBitNum;

                            if (msiBitJustCleared(pDev->config[uAddr], u8Val, iBit))
                            {
                                Log(("msi: mask updated bit %d@%x (%d)\n", iBitNum, uAddr, maskUpdated));

                                /* To ensure that we're no longer masked */
                                pDev->config[uAddr] &= ~iBit;
                                if ((*puPending & (1 << uVector)) != 0)
                                {
                                    Log(("msi: notify earlier masked pending vector: %d\n", uVector));
                                    MsiNotify(pDevIns, pPciHlp, pDev, uVector, PDM_IRQ_LEVEL_HIGH);
                                }
                            }
                            if (msiBitJustSet(pDev->config[uAddr], u8Val, iBit))
                            {
                                Log(("msi: mask vector: %d\n", uVector));
                            }
                        }
                    }

                    pDev->config[uAddr] = u8Val;
                }
        }
        uAddr++;
        val >>= 8;
    }
}