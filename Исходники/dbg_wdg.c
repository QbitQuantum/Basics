void prvGetRegistersFromStack2( uint32_t *pulFaultStackAddress )
{
    /* These are volatile to try and prevent the compiler/linker optimising them
    away as the variables never actually get used.  If the debugger won't show the
    values of the variables, make them global my moving their declaration outside
    of this function. */
    volatile uint32_t r0;
    volatile uint32_t r1;
    volatile uint32_t r2;
    volatile uint32_t r3;
    volatile uint32_t r12;
    volatile uint32_t lr; /* Link register. */
    volatile uint32_t pc; /* Program counter. */
    volatile uint32_t psr;/* Program status register. */

    r0 = pulFaultStackAddress[ 0 ];
    r1 = pulFaultStackAddress[ 1 ];
    r2 = pulFaultStackAddress[ 2 ];
    r3 = pulFaultStackAddress[ 3 ];

    r12 = pulFaultStackAddress[ 4 ];
    lr  = pulFaultStackAddress[ 5 ];
    pc  = pulFaultStackAddress[ 6 ];
    psr = pulFaultStackAddress[ 7 ];

    /* When the following line is hit, the variables contain the register values. */
    dbg_printf(DBGMODE_ERR, "\r\n WDG Handler (%d)\r\n", systick_1ms_cnt);
    dbg_printf(DBGMODE_ERR, "r0: 0x%08X, r1: 0x%08X, r2: 0x%08X, r3: 0x%08X,", r0, r1, r2, r3);
    dbg_printf(DBGMODE_ERR, " r12: 0x%08X\r\nLR: 0x%08X, PC: 0x%08X, PSR: 0x%08X, \r\n", r12, lr, pc, psr);
    volatile int cntdn = 0x7FFFFF;
    while (cntdn--) __NOP();
    NVIC_SystemReset();
    while (1);
}