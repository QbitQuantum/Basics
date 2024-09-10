//
// The x86 walker is currently pretty minimal.  It only recognizes call and return opcodes, plus a few jumps.  The rest
// is treated as unknown.
//
void NativeWalker::Decode()
{
    const BYTE *ip = m_ip;

    m_type = WALK_UNKNOWN;
    m_skipIP = NULL;
    m_nextIP = NULL;

    LOG((LF_CORDB, LL_INFO100000, "NW:Decode: m_ip 0x%x\n", m_ip));
    //
    // Skip instruction prefixes
    //
    do 
    {
        switch (*ip)
        {
        // Segment overrides
        case 0x26: // ES
        case 0x2E: // CS
        case 0x36: // SS
        case 0x3E: // DS 
        case 0x64: // FS
        case 0x65: // GS

        // Size overrides
        case 0x66: // Operand-Size
        case 0x67: // Address-Size

        // Lock
        case 0xf0:

        // String REP prefixes
        case 0xf1:
        case 0xf2: // REPNE/REPNZ
        case 0xf3: 
            LOG((LF_CORDB, LL_INFO10000, "NW:Decode: prefix:%0.2x ", *ip));
            ip++;
            continue;

        default:
            break;
        }
    } while (0);

    // Read the opcode
    m_opcode = *ip++;

    LOG((LF_CORDB, LL_INFO100000, "NW:Decode: ip 0x%x, m_opcode:%0.2x\n", ip, m_opcode));

    if (m_opcode == 0xcc)
    {
        m_opcode = DebuggerController::GetPatchedOpcode(m_ip);
        LOG((LF_CORDB, LL_INFO100000, "NW:Decode after patch look up: m_opcode:%0.2x\n", m_opcode));
    }

    // Analyze what we can of the opcode
    switch (m_opcode)
    {
    case 0xff:
        {

        BYTE modrm = *ip++;
        BYTE mod = (modrm & 0xC0) >> 6;
        BYTE reg = (modrm & 0x38) >> 3;
        BYTE rm  = (modrm & 0x07);

        BYTE *result = 0;
        WORD displace = 0;

        if ((reg != 2) && (reg != 3) && (reg != 4) && (reg != 5)) {
            //
            // This is not a CALL or JMP instruction, return, unknown.
            //
            return;
        }


        if (m_registers != NULL)
        {
            // Only try to decode registers if we actually have reg sets.
            switch (mod) {
            case 0:
            case 1:
            case 2:
                
                if (rm == 4) {
                    
                    //
                    // Get values from the SIB byte
                    //
                    BYTE ss    = (*ip & 0xC0) >> 6;
                    BYTE index = (*ip & 0x38) >> 3;
                    BYTE base  = (*ip & 0x7);

                    ip++;

                    //
                    // Get starting value
                    //
                    if ((mod == 0) && (base == 5)) {
                        result = 0;
                    } else {
                        result = (BYTE *)(size_t)GetRegisterValue(base);
                    }

                    //
                    // Add in the [index]
                    //
                    if (index != 0x4) {
                        result = result + (GetRegisterValue(index) << ss);
                    }

                    //
                    // Finally add in the offset
                    //
                    if (mod == 0) {

                        if (base == 5) {
                            result = result + *((unsigned int *)ip);
                            displace = 7;
                        } else {
                            displace = 3;
                        }

                    } else if (mod == 1) {

                        result = result + *((char *)ip);
                        displace = 4;

                    } else { // == 2

                        result = result + *((unsigned int *)ip);
                        displace = 7;

                    }

                } else {

                    //
                    // Get the value we need from the register.
                    //

                    if ((mod == 0) && (rm == 5)) {
                        result = 0;
                    } else {
                        result = (BYTE *)GetRegisterValue(rm);
                    }

                    if (mod == 0) {

                        if (rm == 5) {
                            result = result + *((unsigned int *)ip);
                            displace = 6;
                        } else {
                            displace = 2;
                        }

                    } else if (mod == 1) {

                        result = result + *((char *)ip);
                        displace = 3;

                    } else { // == 2

                        result = result + *((unsigned int *)ip);
                        displace = 6;

                    }

                }

                //
                // Now dereference thru the result to get the resulting IP.
                //

                // If result is bad, then this means we can't predict what the nextIP will be.
                // That's ok - we just leave m_nextIp=NULL. We can still provide callers
                // with the proper walk-type.
                // In practice, this shouldn't happen unless the jit emits bad opcodes.
                if (result != NULL)
                {
                    result = (BYTE *)(*((unsigned int *)result)); 
                }

                break;

            case 3:
            default:

                result = (BYTE *)GetRegisterValue(rm);
                displace = 2;
                break;

            }
        } // have registers
        
        if ((reg == 2) || (reg == 3)) {
            m_type = WALK_CALL;
        } else if ((reg == 4) || (reg == 5)) {
            m_type = WALK_BRANCH;
        } else {
            break;
        }

        if (m_registers != NULL)
        {
            m_nextIP = result;
            m_skipIP = m_ip + displace;
        }            
        
        break; 
        }  // end of 0xFF case