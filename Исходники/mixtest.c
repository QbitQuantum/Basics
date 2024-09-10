HRESULT MixedRxTf(PSORA_RADIO pRadio)
{
    __REG32_TRANS_CTRL TransCtrl;
    __PSORA_RADIO_REGS pRegs = pRadio->__ctrl_reg.pRadioRegs;
    ULONG              uTemp  = 100000;

    pPhyFrameDesc->__FrameCtrlOwn = 1; //software own the phy frame

    TransCtrl.Value = 0;
    TransCtrl.Bits.TransferInit  = 1;

    WRITE_REGISTER_ULONG(
        (PULONG)&pRegs->TransferSrcAddrL, pPhyFrameDesc->ThisPa.u.LowPart);
    
    WRITE_REGISTER_ULONG(
        (PULONG)&pRegs->TransferSrcAddrH, pPhyFrameDesc->ThisPa.u.HighPart);
    WRITE_REGISTER_ULONG(
        (PULONG)&pRegs->TransferControl, TransCtrl.Value);

    while(pPhyFrameDesc->__FrameCtrlOwn == 1) //wait until hw owns the phy frame
    //hw will set it if TXDone. PHY frame desc is in MmWriteCombined mem, so not cached.
    {
        {
            __REG32_RX_CTRL RXControl;
            RXControl.Value         = 0;
            RXControl.Bits.RXEnable = 1;
            
            WRITE_REGISTER_ULONG(
                (PULONG)&pRadio->__phy_reg_manager.pRadioRegs->RXControl,
                RXControl.Value);
            pRadio->__fRxEnabled = TRUE;
        }
        
        uTemp--;
        if(uTemp < 1) {
            KdPrint(("Wait Own Timeout!"));
            hr = E_TX_TRANSFER_FAIL;
            break;
        }
        _mm_pause();
    }

    TransCtrl.Value = 0;
    WRITE_REGISTER_ULONG((PULONG)&pRegs->TransferControl, TransCtrl.Value); //clear init bit
    return hr;
}