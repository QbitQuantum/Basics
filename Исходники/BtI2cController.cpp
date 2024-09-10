// Method to initialize the I2C Controller at the start of a transaction.
HRESULT BtI2cControllerClass::_initializeForTransaction(ULONG slaveAddress, BOOL useHighSpeed)
{
    ULONGLONG waitStartTicks = 0;
    BoardPinsClass::BOARD_TYPE board;
    _IC_CON icConReg;

    // If we need to initialize, or re-initialize, the I2C Controller:
    if (!isInitialized() || (m_registers->IC_TAR.IC_TAR != slaveAddress))
    {
        // Disable the I2C controller.  This also clears the FIFOs.
        m_registers->IC_ENABLE.ENABLE = 0;

        // Wait for the controller to go disabled, but only for 100 mS.
        // It can latch in a mode in which it does not go disabled, but appears 
        // to come out of this state when used again.
        waitStartTicks = GetTickCount64();
        while ((m_registers->IC_ENABLE_STATUS.IC_EN == 1) && ((GetTickCount64() - waitStartTicks) < 100))
        {
            Sleep(0);       // Give the CPU to any thread that is waiting
        }

        // Set the desired I2C Clock speed.
        g_pins.getBoardType(board);
        if ((board == BoardPinsClass::BOARD_TYPE::MBM_BARE) ||
            (board == BoardPinsClass::BOARD_TYPE::MBM_IKA_LURE))
        {
            if (useHighSpeed)
            {
                m_registers->IC_FS_SCL_HCNT.IC_FS_SCL_HCNT = 0x3C;
                m_registers->IC_FS_SCL_LCNT.IC_FS_SCL_LCNT = 0x82;
                m_registers->IC_CON.SPEED = 2;
            }
            else
            {
                m_registers->IC_SS_SCL_HCNT.IC_SS_SCL_HCNT = 0x190;
                m_registers->IC_SS_SCL_LCNT.IC_SS_SCL_LCNT = 0x1D6;
                m_registers->IC_CON.SPEED = 1;
            }
        }
        else
        {
            if (useHighSpeed)
            {
                m_registers->IC_FS_SCL_HCNT.IC_FS_SCL_HCNT = 0x14;
                m_registers->IC_FS_SCL_LCNT.IC_FS_SCL_LCNT = 0x2E;
                m_registers->IC_CON.SPEED = 2;
            }
            else
            {
                m_registers->IC_SS_SCL_HCNT.IC_SS_SCL_HCNT = 0x92;
                m_registers->IC_SS_SCL_LCNT.IC_SS_SCL_LCNT = 0xAB;
                m_registers->IC_CON.SPEED = 1;
            }
        }

        // Allow bus restarts.
        m_registers->IC_CON.IC_RESTART_EN = 1;

        // Set 7-bit addressing.
        icConReg.ALL_BITS = m_registers->IC_CON.ALL_BITS;
        icConReg.IC_10BITADDR_MASTER = 0;
        m_registers->IC_CON.ALL_BITS = icConReg.ALL_BITS;

        // Set the address of the slave this tranaction affects.
        // All bits but the 7-bit address are intentionally cleared here.  This is needed
        // for Bay Trail, which supports additional bits (all of which we want clear).
        m_registers->IC_TAR.ALL_BITS = (slaveAddress & 0x7F);

        // Mask all interrupts.
        m_registers->IC_INTR_MASK.ALL_BITS = 0;

        // Clear any outstanding interrupts.
        ULONG dummy = m_registers->IC_CLR_INTR.ALL_BITS;

        // Enable the controller.
        m_registers->IC_ENABLE.ENABLE = 1;

        // Indicate the I2C Controller is now initialized.
        setInitialized();

    } // End - if (!isInitialized() || (getAddress() != m_slaveAddress))

    return S_OK;
}