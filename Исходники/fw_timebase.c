int fw_sync_timebase( void ) 
{

    uint64_t numloops = 10;
    uint64_t value;
    uint64_t rc;
    Personality_t *pers = &FW_Personality;    
    uint64_t numthreads;
    uint64_t msr;
    uint64_t geamap8 = 0;
    
    if(!PERS_ENABLED(PERS_ENABLE_MU))
        return 0;    

    if(!PERS_ENABLED(PERS_ENABLE_ND))
        return 0;    
    
    msr = mfmsr();
    mtmsr(msr & ~(MSR_EE | MSR_CE | MSR_ME));
    isync();
    
    numthreads = popcnt64(DCRReadPriv(TESTINT_DCR(THREAD_ACTIVE0))) + popcnt64(DCRReadPriv(TESTINT_DCR(THREAD_ACTIVE1)));
    if(PhysicalThreadID() == 0)
    {
#define WU_MMIO_PRIV_BASE ((volatile unsigned long *)0x3ffe8001c00)
#define SET_THREAD(i)           ((0x300 + (i)*0x40) / sizeof (unsigned long))
        WU_MMIO_PRIV_BASE[SET_THREAD(0)] = WU_DCR__THREAD0_WU_EVENT_SET__GEA_WU_EN_set(0x8);
        
        if(ProcessorID() == 0)
        {
            // Setup classroute 14.  Identical to classroute 15.
            value = DCRReadPriv(ND_500_DCR(CTRL_GI_CLASS_14_15));
            ND_500_DCR__CTRL_GI_CLASS_14_15__CLASS14_UP_PORT_I_insert(value, ND_500_DCR__CTRL_GI_CLASS_14_15__CLASS15_UP_PORT_I_get(value));
            ND_500_DCR__CTRL_GI_CLASS_14_15__CLASS14_UP_PORT_O_insert(value, ND_500_DCR__CTRL_GI_CLASS_14_15__CLASS15_UP_PORT_O_get(value));
            DCRWritePriv(ND_500_DCR(CTRL_GI_CLASS_14_15), value);
            ppc_msync();
            
            // Initialize GI pulse
            MUSPI_GIInit (&GI, 14, 0);
            
            // Initialize the GI barrier interrupt on classroute 14
            DCRWritePriv(MU_DCR(BARRIER_INT_EN), MU_DCR__BARRIER_INT_EN__CLASS14_set(4));
            
            // Route MU MAP4 interrupt to GEA lane 12 (wakeup unit bit 0)
            geamap8 = DCRReadPriv(GEA_DCR(GEA_INTERRUPT_MAP8));
            DCRWritePriv(GEA_DCR(GEA_INTERRUPT_MAP8), GEA_DCR__GEA_INTERRUPT_MAP8__MU_MAP4_set(12));
            rc = MUSPI_GIBarrierInit(&GIBarrier, 15);
        }
        
        // do local barrier
        BeDRAM_ReadIncSat(BeDRAM_LOCKNUM_TIMESYNC_BARRIER);
        while(BeDRAM_Read(BeDRAM_LOCKNUM_TIMESYNC_BARRIER) != numthreads)
        {
        }
        
        if(ProcessorID() == 0)
        {
            // Perform a barrier across all nodes.
            MUSPI_GIBarrierEnterAndWait(&GIBarrier);
            if ( rc != 0 )
            {
                FW_Warning("MUSPI_GIBarrierInit for class route 15 returned rc = %ld.", rc);
                return -1;
            }
            
            // Start gsync counter (for debug)
            DCRWritePriv(TESTINT_DCR(GSYNC_CTR), -1);
        }
        doTimeSync(numloops);
        mtspr(SPRN_TENS, 0xf);
    }
    else if((ProcessorID() == 1) && (pers->Network_Config.PrimordialClassRoute.GlobIntUpPortOutputs == 0))
    {
        BeDRAM_ReadIncSat(BeDRAM_LOCKNUM_TIMESYNC_BARRIER);
        createSendGIPulseThread(numloops);
    }
    else
    {
        BeDRAM_ReadIncSat(BeDRAM_LOCKNUM_TIMESYNC_BARRIER);
        mtspr(SPRN_TENC, 1 << ProcessorThreadID());
        isync();
    }
    
    // Wait for all hwthreads on node
    BeDRAM_ReadIncSat(BeDRAM_LOCKNUM_TIMESYNC_BARRIER);
    while(BeDRAM_Read(BeDRAM_LOCKNUM_TIMESYNC_BARRIER) != numthreads * 2)
    {
    }
    
    if(ProcessorID() == 0)
    {
        value = DCRReadPriv(ND_500_DCR(CTRL_GI_CLASS_14_15));
        ND_500_DCR__CTRL_GI_CLASS_14_15__CLASS14_UP_PORT_I_insert(value, 0);
        ND_500_DCR__CTRL_GI_CLASS_14_15__CLASS14_UP_PORT_O_insert(value, 0);
        DCRWritePriv(ND_500_DCR(CTRL_GI_CLASS_14_15), value);
        ppc_msync();
        
        // Initialize the barrier structure.  
        DCRWritePriv(MU_DCR(BARRIER_INT_EN), MU_DCR__BARRIER_INT_EN__CLASS14_set(0));
        DCRWritePriv(GEA_DCR(GEA_INTERRUPT_MAP8), geamap8);
    }
    WU_MMIO_PRIV_BASE[SET_THREAD(0)] = WU_DCR__THREAD0_WU_EVENT_SET__GEA_WU_EN_set(0);
    
    BeDRAM_ReadIncSat(BeDRAM_LOCKNUM_TIMESYNC_BARRIER);
    while(BeDRAM_Read(BeDRAM_LOCKNUM_TIMESYNC_BARRIER) != numthreads * 3)
    {
    }
    
    mtmsr(msr);
    isync();
    
    return 0;
}