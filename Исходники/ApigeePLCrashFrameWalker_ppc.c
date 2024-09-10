// PLFrameWalker API
const char *Apigee_plframe_get_regname (Apigee_plframe_regnum_t regnum) {
    switch (regnum) {
        case Apigee_PLFRAME_PPC_SRR0:
            return "srr0";
        case Apigee_PLFRAME_PPC_SRR1:
            return "srr1";
            
        case Apigee_PLFRAME_PPC_DAR:
            return "dar";
        case Apigee_PLFRAME_PPC_DSISR:
            return "dsisr";

        case Apigee_PLFRAME_PPC_R0:
            return "r0";
        case Apigee_PLFRAME_PPC_R1:
            return "r1";
        case Apigee_PLFRAME_PPC_R2:
            return "r2";
        case Apigee_PLFRAME_PPC_R3:
            return "r3";
        case Apigee_PLFRAME_PPC_R4:
            return "r4";
        case Apigee_PLFRAME_PPC_R5:
            return "r5";
        case Apigee_PLFRAME_PPC_R6:
            return "r6";
        case Apigee_PLFRAME_PPC_R7:
            return "r7";
        case Apigee_PLFRAME_PPC_R8:
            return "r8";
        case Apigee_PLFRAME_PPC_R9:
            return "r9";
        case Apigee_PLFRAME_PPC_R10:
            return "r10";
        case Apigee_PLFRAME_PPC_R11:
            return "r11";
        case Apigee_PLFRAME_PPC_R12:
            return "r12";
        case Apigee_PLFRAME_PPC_R13:
            return "r13";
        case Apigee_PLFRAME_PPC_R14:
            return "r14";
        case Apigee_PLFRAME_PPC_R15:
            return "r15";
        case Apigee_PLFRAME_PPC_R16:
            return "r16";
        case Apigee_PLFRAME_PPC_R17:
            return "r17";
        case Apigee_PLFRAME_PPC_R18:
            return "r18";
        case Apigee_PLFRAME_PPC_R19:
            return "r19";
        case Apigee_PLFRAME_PPC_R20:
            return "r20";
        case Apigee_PLFRAME_PPC_R21:
            return "r21";
        case Apigee_PLFRAME_PPC_R22:
            return "r22";
        case Apigee_PLFRAME_PPC_R23:
            return "r23";
        case Apigee_PLFRAME_PPC_R24:
            return "r24";
        case Apigee_PLFRAME_PPC_R25:
            return "r25";
        case Apigee_PLFRAME_PPC_R26:
            return "r26";
        case Apigee_PLFRAME_PPC_R27:
            return "r27";
        case Apigee_PLFRAME_PPC_R28:
            return "r28";
        case Apigee_PLFRAME_PPC_R29:
            return "r29";
        case Apigee_PLFRAME_PPC_R30:
            return "r30";
        case Apigee_PLFRAME_PPC_R31:
            return "r31";
            
        case Apigee_PLFRAME_PPC_CR:
            return "cr";
            
        case Apigee_PLFRAME_PPC_XER:
            return "xer";
            
        case Apigee_PLFRAME_PPC_LR:
            return "lr";
            
        case Apigee_PLFRAME_PPC_CTR:
            return "ctr";
            
        case Apigee_PLFRAME_PPC_VRSAVE:
            return "vrsave";

        default:
            // Unsupported register
            break;
    }
    
    /* Unsupported register is an implementation error (checked in unit tests) */
    Apigee_PLCF_DEBUG("Missing register name for register id: %d", regnum);
    abort();
}