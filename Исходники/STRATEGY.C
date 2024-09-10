static VOID StratRead( REQP_RWV FAR *rp )
{
        tick_mask ticks;
        PVOID     virt;

       _disable();
        outp( i8253CtrlZeroOrTwo, i8253CmdReadCtrZero );
        ticks.b[0] = inp(i8253CounterZero );
        ticks.b[1] = inp(i8253CounterZero );
        UpdateTimeStamp( ticks.w ); // Update the running time stamp
        if( rp->count < sizeof( TIMESTAMP )  ) {
            rp->count = 0;          // Caller's buffer is too small
            goto Exit;
        }
        if( DevPhysToVirt( rp->transaddr, rp->count, &virt ) != 0 ) {
            rp->count = 0;          // DevHlp failed
            goto Exit;
        }
        rp->count = sizeof( TIMESTAMP );
        (*(TIMESTAMP FAR*)virt) = ReadDataBuf;
Exit:
        _enable();
        rp->header.status |=  RPDONE;
}