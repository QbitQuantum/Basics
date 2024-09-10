DECLSPEC_NORETURN
VOID
FASTCALL
KiTrap0DHandler(IN PKTRAP_FRAME TrapFrame)
{
    ULONG i, j, Iopl;
    BOOLEAN Privileged = FALSE;
    PUCHAR Instructions;
    UCHAR Instruction = 0;
    KIRQL OldIrql;
    
    /* Check for V86 GPF */
    if (__builtin_expect(KiV86Trap(TrapFrame), 1))
    {
        /* Enter V86 trap */
        KiEnterV86Trap(TrapFrame);
        
        /* Must be a VDM process */
        if (__builtin_expect(!PsGetCurrentProcess()->VdmObjects, 0))
        {
            /* Enable interrupts */
            _enable();
            
            /* Setup illegal instruction fault */
            KiDispatchException0Args(STATUS_ILLEGAL_INSTRUCTION,
                                     TrapFrame->Eip,
                                     TrapFrame);
        }
        
        /* Go to APC level */
        OldIrql = KfRaiseIrql(APC_LEVEL);
        _enable();
        
        /* Handle the V86 opcode */
        if (__builtin_expect(Ki386HandleOpcodeV86(TrapFrame) == 0xFF, 0))
        {
            /* Should only happen in VDM mode */
            UNIMPLEMENTED;
            while (TRUE);
        }
        
        /* Bring IRQL back */
        KfLowerIrql(OldIrql);
        _disable();
        
        /* Do a quick V86 exit if possible */
        KiExitV86Trap(TrapFrame);
    }
    
    /* Save trap frame */
    KiEnterTrap(TrapFrame);

    /* Check for user-mode GPF */
    if (KiUserTrap(TrapFrame))
    {
        /* Should not be VDM */
        ASSERT(KiVdmTrap(TrapFrame) == FALSE);
        
        /* Enable interrupts and check error code */
        _enable();
        if (!TrapFrame->ErrCode)
        {
            /* FIXME: Use SEH */
            Instructions = (PUCHAR)TrapFrame->Eip;
            
            /* Scan next 15 bytes */
            for (i = 0; i < 15; i++)
            {
                /* Skip prefix instructions */
                for (j = 0; j < sizeof(KiTrapPrefixTable); j++)
                {
                    /* Is this a prefix instruction? */
                    if (Instructions[i] == KiTrapPrefixTable[j])
                    {
                        /* Stop looking */
                        break;
                    }
                }
                
                /* Is this NOT any prefix instruction? */
                if (j == sizeof(KiTrapPrefixTable))
                {
                    /* We can go ahead and handle the fault now */
                    Instruction = Instructions[i];
                    break;
                }
            }
            
            /* If all we found was prefixes, then this instruction is too long */
            if (i == 15)
            {
                /* Setup illegal instruction fault */
                KiDispatchException0Args(STATUS_ILLEGAL_INSTRUCTION,
                                         TrapFrame->Eip,
                                         TrapFrame);
            }
            
            /* Check for privileged instructions */
            if (Instruction == 0xF4)                            // HLT
            {
                /* HLT is privileged */
                Privileged = TRUE;
            }
            else if (Instruction == 0x0F)
            {
                /* Test if it's any of the privileged two-byte opcodes */
                if (((Instructions[i + 1] == 0x00) &&              // LLDT or LTR
                     (((Instructions[i + 2] & 0x38) == 0x10) ||        // LLDT
                      (Instructions[i + 2] == 0x18))) ||               // LTR
                    ((Instructions[i + 1] == 0x01) &&              // LGDT or LIDT or LMSW
                     (((Instructions[i + 2] & 0x38) == 0x10) ||        // LGDT
                      (Instructions[i + 2] == 0x18) ||                 // LIDT
                      (Instructions[i + 2] == 0x30))) ||               // LMSW
                    (Instructions[i + 1] == 0x08) ||               // INVD
                    (Instructions[i + 1] == 0x09) ||               // WBINVD
                    (Instructions[i + 1] == 0x35) ||               // SYSEXIT
                    (Instructions[i + 1] == 0x26) ||               // MOV DR, XXX
                    (Instructions[i + 1] == 0x06) ||               // CLTS
                    (Instructions[i + 1] == 0x20) ||               // MOV CR, XXX
                    (Instructions[i + 1] == 0x24) ||               // MOV YYY, DR
                    (Instructions[i + 1] == 0x30) ||               // WRMSR
                    (Instructions[i + 1] == 0x33))                 // RDPMC
                    // INVLPG, INVLPGA, SYSRET
                {
                    /* These are all privileged */
                    Privileged = TRUE;
                }
            }
            else
            {
                /* Get the IOPL and compare with the RPL mask */
                Iopl = (TrapFrame->EFlags & EFLAGS_IOPL) >> 12;
                if ((TrapFrame->SegCs & RPL_MASK) > Iopl)
                {
                    /* I/O privilege error -- check for known instructions */
                    if ((Instruction == 0xFA) || (Instruction == 0xFB)) // CLI or STI
                    {
                        /* These are privileged */
                        Privileged = TRUE;
                    }
                    else
                    {
                        /* Last hope: an IN/OUT instruction */
                        for (j = 0; j < sizeof(KiTrapIoTable); j++)
                        {
                            /* Is this an I/O instruction? */
                            if (Instruction == KiTrapIoTable[j])
                            {
                                /* Then it's privileged */
                                Privileged = TRUE;
                                break;
                            }
                        }
                    }
                }
            }
            
            /* So now... was the instruction privileged or not? */
            if (Privileged)
            {
                /* Whew! We have a privileged instruction, so dispatch the fault */
                KiDispatchException0Args(STATUS_PRIVILEGED_INSTRUCTION,
                                         TrapFrame->Eip,
                                         TrapFrame);
            }
        }
            
        /* If we got here, send an access violation */
        KiDispatchException2Args(STATUS_ACCESS_VIOLATION,
                                 TrapFrame->Eip,
                                 0,
                                 0xFFFFFFFF,
                                 TrapFrame);
    }