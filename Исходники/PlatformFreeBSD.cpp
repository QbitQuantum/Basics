size_t
PlatformFreeBSD::GetSoftwareBreakpointTrapOpcode (Target &target, BreakpointSite *bp_site)
{
    ArchSpec arch = target.GetArchitecture();
    const uint8_t *trap_opcode = NULL;
    size_t trap_opcode_size = 0;

    switch (arch.GetMachine())
    {
    default:
        assert(false && "Unhandled architecture in PlatformFreeBSD::GetSoftwareBreakpointTrapOpcode()");
        break;
    case llvm::Triple::aarch64:
        {
            static const uint8_t g_aarch64_opcode[] = { 0x00, 0x00, 0x20, 0xd4 };
            trap_opcode = g_aarch64_opcode;
            trap_opcode_size = sizeof(g_aarch64_opcode);
        }
        break;
    // TODO: support big-endian arm and thumb trap codes.
    case llvm::Triple::arm:
        {
            static const uint8_t g_arm_breakpoint_opcode[] = { 0xfe, 0xde, 0xff, 0xe7 };
            static const uint8_t g_thumb_breakpoint_opcode[] = { 0x01, 0xde };

            lldb::BreakpointLocationSP bp_loc_sp (bp_site->GetOwnerAtIndex (0));
            AddressClass addr_class = eAddressClassUnknown;

            if (bp_loc_sp)
                addr_class = bp_loc_sp->GetAddress ().GetAddressClass ();

            if (addr_class == eAddressClassCodeAlternateISA
                || (addr_class == eAddressClassUnknown && (bp_site->GetLoadAddress() & 1)))
            {
                // TODO: Enable when FreeBSD supports thumb breakpoints.
                // FreeBSD kernel as of 10.x, does not support thumb breakpoints
                trap_opcode = g_thumb_breakpoint_opcode;
                trap_opcode_size = 0;
            }
            else
            {
                trap_opcode = g_arm_breakpoint_opcode;
                trap_opcode_size = sizeof(g_arm_breakpoint_opcode);
            }
        }
        break;
    case llvm::Triple::mips64:
        {
            static const uint8_t g_hex_opcode[] = { 0x00, 0x00, 0x00, 0x0d };
            trap_opcode = g_hex_opcode;
            trap_opcode_size = sizeof(g_hex_opcode);
        }
        break;
    case llvm::Triple::mips64el:
        {
            static const uint8_t g_hex_opcode[] = { 0x0d, 0x00, 0x00, 0x00 };
            trap_opcode = g_hex_opcode;
            trap_opcode_size = sizeof(g_hex_opcode);
        }
        break;
    case llvm::Triple::ppc:
    case llvm::Triple::ppc64:
        {
            static const uint8_t g_ppc_opcode[] = { 0x7f, 0xe0, 0x00, 0x08 };
            trap_opcode = g_ppc_opcode;
            trap_opcode_size = sizeof(g_ppc_opcode);
        }
        break;
    case llvm::Triple::x86:
    case llvm::Triple::x86_64:
        {
            static const uint8_t g_i386_opcode[] = { 0xCC };
            trap_opcode = g_i386_opcode;
            trap_opcode_size = sizeof(g_i386_opcode);
        }
        break;
    }

    if (bp_site->SetTrapOpcode(trap_opcode, trap_opcode_size))
        return trap_opcode_size;
    return 0;
}