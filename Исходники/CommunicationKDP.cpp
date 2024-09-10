void CommunicationKDP::DumpPacket(Stream &s, const DataExtractor &packet) {
  const char *error_desc = NULL;
  if (packet.GetByteSize() < 8) {
    error_desc = "error: invalid packet (too short): ";
  } else {
    lldb::offset_t offset = 0;
    const uint8_t first_packet_byte = packet.GetU8(&offset);
    const uint8_t sequence_id = packet.GetU8(&offset);
    const uint16_t length = packet.GetU16(&offset);
    const uint32_t key = packet.GetU32(&offset);
    const CommandType command = ExtractCommand(first_packet_byte);
    const char *command_name = GetCommandAsCString(command);
    if (command_name) {
      const bool is_reply = ExtractIsReply(first_packet_byte);
      s.Printf("(running=%i) %s %24s: 0x%2.2x 0x%2.2x 0x%4.4x 0x%8.8x ",
               IsRunning(), is_reply ? "<--" : "-->", command_name,
               first_packet_byte, sequence_id, length, key);

      if (is_reply) {
        // Dump request reply packets
        switch (command) {
        // Commands that return a single 32 bit error
        case KDP_CONNECT:
        case KDP_WRITEMEM:
        case KDP_WRITEMEM64:
        case KDP_BREAKPOINT_SET:
        case KDP_BREAKPOINT_REMOVE:
        case KDP_BREAKPOINT_SET64:
        case KDP_BREAKPOINT_REMOVE64:
        case KDP_WRITEREGS:
        case KDP_LOAD:
        case KDP_WRITEIOPORT:
        case KDP_WRITEMSR64: {
          const uint32_t error = packet.GetU32(&offset);
          s.Printf(" (error=0x%8.8x)", error);
        } break;

        case KDP_DISCONNECT:
        case KDP_REATTACH:
        case KDP_HOSTREBOOT:
        case KDP_SUSPEND:
        case KDP_RESUMECPUS:
        case KDP_EXCEPTION:
        case KDP_TERMINATION:
          // No return value for the reply, just the header to ack
          s.PutCString(" ()");
          break;

        case KDP_HOSTINFO: {
          const uint32_t cpu_mask = packet.GetU32(&offset);
          const uint32_t cpu_type = packet.GetU32(&offset);
          const uint32_t cpu_subtype = packet.GetU32(&offset);
          s.Printf(" (cpu_mask=0x%8.8x, cpu_type=0x%8.8x, cpu_subtype=0x%8.8x)",
                   cpu_mask, cpu_type, cpu_subtype);
        } break;

        case KDP_VERSION: {
          const uint32_t version = packet.GetU32(&offset);
          const uint32_t feature = packet.GetU32(&offset);
          s.Printf(" (version=0x%8.8x, feature=0x%8.8x)", version, feature);
        } break;

        case KDP_REGIONS: {
          const uint32_t region_count = packet.GetU32(&offset);
          s.Printf(" (count = %u", region_count);
          for (uint32_t i = 0; i < region_count; ++i) {
            const addr_t region_addr = packet.GetPointer(&offset);
            const uint32_t region_size = packet.GetU32(&offset);
            const uint32_t region_prot = packet.GetU32(&offset);
            s.Printf("\n\tregion[%" PRIu64 "] = { range = [0x%16.16" PRIx64
                     " - 0x%16.16" PRIx64 "), size = 0x%8.8x, prot = %s }",
                     region_addr, region_addr, region_addr + region_size,
                     region_size, GetPermissionsAsCString(region_prot));
          }
        } break;

        case KDP_READMEM:
        case KDP_READMEM64:
        case KDP_READPHYSMEM64: {
          const uint32_t error = packet.GetU32(&offset);
          const uint32_t count = packet.GetByteSize() - offset;
          s.Printf(" (error = 0x%8.8x:\n", error);
          if (count > 0)
            DumpDataExtractor(packet, 
                              &s,                      // Stream to dump to
                              offset,                  // Offset within "packet"
                              eFormatBytesWithASCII,   // Format to use
                              1,                       // Size of each item 
                                                       // in bytes
                              count,                   // Number of items
                              16,                      // Number per line
                              m_last_read_memory_addr, // Don't show addresses
                                                       // before each line
                              0, 0);                   // No bitfields
        } break;

        case KDP_READREGS: {
          const uint32_t error = packet.GetU32(&offset);
          const uint32_t count = packet.GetByteSize() - offset;
          s.Printf(" (error = 0x%8.8x regs:\n", error);
          if (count > 0)
            DumpDataExtractor(packet, 
                              &s,                       // Stream to dump to
                              offset,                   // Offset within "packet"
                              eFormatHex,               // Format to use
                              m_addr_byte_size,         // Size of each item 
                                                        // in bytes
                              count / m_addr_byte_size, // Number of items
                              16 / m_addr_byte_size,    // Number per line
                              LLDB_INVALID_ADDRESS, 
                                                        // Don't 
                                                        // show addresses before
                                                        // each line
                              0, 0);                    // No bitfields
        } break;

        case KDP_KERNELVERSION: {
          const char *kernel_version = packet.PeekCStr(8);
          s.Printf(" (version = \"%s\")", kernel_version);
        } break;

        case KDP_MAXBYTES: {
          const uint32_t max_bytes = packet.GetU32(&offset);
          s.Printf(" (max_bytes = 0x%8.8x (%u))", max_bytes, max_bytes);
        } break;
        case KDP_IMAGEPATH: {
          const char *path = packet.GetCStr(&offset);
          s.Printf(" (path = \"%s\")", path);
        } break;

        case KDP_READIOPORT:
        case KDP_READMSR64: {
          const uint32_t error = packet.GetU32(&offset);
          const uint32_t count = packet.GetByteSize() - offset;
          s.Printf(" (error = 0x%8.8x io:\n", error);
          if (count > 0)
            DumpDataExtractor(packet, 
                              &s,                   // Stream to dump to
                              offset,               // Offset within "packet"
                              eFormatHex,           // Format to use
                              1,                    // Size of each item in bytes
                              count,                // Number of items
                              16,                   // Number per line
                              LLDB_INVALID_ADDRESS, // Don't show addresses 
                                                    // before each line
                              0, 0);                // No bitfields
        } break;
        case KDP_DUMPINFO: {
          const uint32_t count = packet.GetByteSize() - offset;
          s.Printf(" (count = %u, bytes = \n", count);
          if (count > 0)
            DumpDataExtractor(packet, 
                              &s,                   // Stream to dump to
                              offset,               // Offset within "packet"
                              eFormatHex,           // Format to use
                              1,                    // Size of each item in 
                                                    // bytes
                              count,                // Number of items
                              16,                   // Number per line
                              LLDB_INVALID_ADDRESS, // Don't show addresses 
                                                    // before each line
                              0, 0);                // No bitfields

        } break;

        default:
          s.Printf(" (add support for dumping this packet reply!!!");
          break;
        }
      } else {
        // Dump request packets
        switch (command) {
        case KDP_CONNECT: {
          const uint16_t reply_port = ntohs(packet.GetU16(&offset));
          const uint16_t exc_port = ntohs(packet.GetU16(&offset));
          s.Printf(" (reply_port = %u, exc_port = %u, greeting = \"%s\")",
                   reply_port, exc_port, packet.GetCStr(&offset));
        } break;

        case KDP_DISCONNECT:
        case KDP_HOSTREBOOT:
        case KDP_HOSTINFO:
        case KDP_VERSION:
        case KDP_REGIONS:
        case KDP_KERNELVERSION:
        case KDP_MAXBYTES:
        case KDP_IMAGEPATH:
        case KDP_SUSPEND:
          // No args, just the header in the request...
          s.PutCString(" ()");
          break;

        case KDP_RESUMECPUS: {
          const uint32_t cpu_mask = packet.GetU32(&offset);
          s.Printf(" (cpu_mask = 0x%8.8x)", cpu_mask);
        } break;

        case KDP_READMEM: {
          const uint32_t addr = packet.GetU32(&offset);
          const uint32_t size = packet.GetU32(&offset);
          s.Printf(" (addr = 0x%8.8x, size = %u)", addr, size);
          m_last_read_memory_addr = addr;
        } break;

        case KDP_WRITEMEM: {
          const uint32_t addr = packet.GetU32(&offset);
          const uint32_t size = packet.GetU32(&offset);
          s.Printf(" (addr = 0x%8.8x, size = %u, bytes = \n", addr, size);
          if (size > 0)
            DumpHexBytes(&s, packet.GetData(&offset, size), size, 32, addr);
        } break;

        case KDP_READMEM64: {
          const uint64_t addr = packet.GetU64(&offset);
          const uint32_t size = packet.GetU32(&offset);
          s.Printf(" (addr = 0x%16.16" PRIx64 ", size = %u)", addr, size);
          m_last_read_memory_addr = addr;
        } break;

        case KDP_READPHYSMEM64: {
          const uint64_t addr = packet.GetU64(&offset);
          const uint32_t size = packet.GetU32(&offset);
          const uint32_t lcpu = packet.GetU16(&offset);
          s.Printf(" (addr = 0x%16.16llx, size = %u, lcpu = %u)", addr, size,
                   lcpu);
          m_last_read_memory_addr = addr;
        } break;

        case KDP_WRITEMEM64: {
          const uint64_t addr = packet.GetU64(&offset);
          const uint32_t size = packet.GetU32(&offset);
          s.Printf(" (addr = 0x%16.16" PRIx64 ", size = %u, bytes = \n", addr,
                   size);
          if (size > 0)
            DumpHexBytes(&s, packet.GetData(&offset, size), size, 32, addr);
        } break;

        case KDP_WRITEPHYSMEM64: {
          const uint64_t addr = packet.GetU64(&offset);
          const uint32_t size = packet.GetU32(&offset);
          const uint32_t lcpu = packet.GetU16(&offset);
          s.Printf(" (addr = 0x%16.16llx, size = %u, lcpu = %u, bytes = \n",
                   addr, size, lcpu);
          if (size > 0)
            DumpHexBytes(&s, packet.GetData(&offset, size), size, 32, addr);
        } break;

        case KDP_READREGS: {
          const uint32_t cpu = packet.GetU32(&offset);
          const uint32_t flavor = packet.GetU32(&offset);
          s.Printf(" (cpu = %u, flavor = %u)", cpu, flavor);
        } break;

        case KDP_WRITEREGS: {
          const uint32_t cpu = packet.GetU32(&offset);
          const uint32_t flavor = packet.GetU32(&offset);
          const uint32_t nbytes = packet.GetByteSize() - offset;
          s.Printf(" (cpu = %u, flavor = %u, regs = \n", cpu, flavor);
          if (nbytes > 0)
            DumpDataExtractor(packet, 
                              &s,                        // Stream to dump to
                              offset,                    // Offset within 
                                                         // "packet"
                              eFormatHex,                // Format to use
                              m_addr_byte_size,          // Size of each item in 
                                                         // bytes
                              nbytes / m_addr_byte_size, // Number of items
                              16 / m_addr_byte_size,     // Number per line
                              LLDB_INVALID_ADDRESS,      // Don't show addresses
                                                         // before each line
                              0, 0);                // No bitfields
        } break;

        case KDP_BREAKPOINT_SET:
        case KDP_BREAKPOINT_REMOVE: {
          const uint32_t addr = packet.GetU32(&offset);
          s.Printf(" (addr = 0x%8.8x)", addr);
        } break;

        case KDP_BREAKPOINT_SET64:
        case KDP_BREAKPOINT_REMOVE64: {
          const uint64_t addr = packet.GetU64(&offset);
          s.Printf(" (addr = 0x%16.16" PRIx64 ")", addr);
        } break;

        case KDP_LOAD: {
          const char *path = packet.GetCStr(&offset);
          s.Printf(" (path = \"%s\")", path);
        } break;

        case KDP_EXCEPTION: {
          const uint32_t count = packet.GetU32(&offset);

          for (uint32_t i = 0; i < count; ++i) {
            const uint32_t cpu = packet.GetU32(&offset);
            const uint32_t exc = packet.GetU32(&offset);
            const uint32_t code = packet.GetU32(&offset);
            const uint32_t subcode = packet.GetU32(&offset);
            const char *exc_cstr = NULL;
            switch (exc) {
            case 1:
              exc_cstr = "EXC_BAD_ACCESS";
              break;
            case 2:
              exc_cstr = "EXC_BAD_INSTRUCTION";
              break;
            case 3:
              exc_cstr = "EXC_ARITHMETIC";
              break;
            case 4:
              exc_cstr = "EXC_EMULATION";
              break;
            case 5:
              exc_cstr = "EXC_SOFTWARE";
              break;
            case 6:
              exc_cstr = "EXC_BREAKPOINT";
              break;
            case 7:
              exc_cstr = "EXC_SYSCALL";
              break;
            case 8:
              exc_cstr = "EXC_MACH_SYSCALL";
              break;
            case 9:
              exc_cstr = "EXC_RPC_ALERT";
              break;
            case 10:
              exc_cstr = "EXC_CRASH";
              break;
            default:
              break;
            }

            s.Printf("{ cpu = 0x%8.8x, exc = %s (%u), code = %u (0x%8.8x), "
                     "subcode = %u (0x%8.8x)} ",
                     cpu, exc_cstr, exc, code, code, subcode, subcode);
          }
        } break;

        case KDP_TERMINATION: {
          const uint32_t term_code = packet.GetU32(&offset);
          const uint32_t exit_code = packet.GetU32(&offset);
          s.Printf(" (term_code = 0x%8.8x (%u), exit_code = 0x%8.8x (%u))",
                   term_code, term_code, exit_code, exit_code);
        } break;

        case KDP_REATTACH: {
          const uint16_t reply_port = ntohs(packet.GetU16(&offset));
          s.Printf(" (reply_port = %u)", reply_port);
        } break;

        case KDP_READMSR64: {
          const uint32_t address = packet.GetU32(&offset);
          const uint16_t lcpu = packet.GetU16(&offset);
          s.Printf(" (address=0x%8.8x, lcpu=0x%4.4x)", address, lcpu);
        } break;

        case KDP_WRITEMSR64: {
          const uint32_t address = packet.GetU32(&offset);
          const uint16_t lcpu = packet.GetU16(&offset);
          const uint32_t nbytes = packet.GetByteSize() - offset;
          s.Printf(" (address=0x%8.8x, lcpu=0x%4.4x, nbytes=0x%8.8x)", lcpu,
                   address, nbytes);
          if (nbytes > 0)
            DumpDataExtractor(packet, 
                              &s,                   // Stream to dump to
                              offset,               // Offset within "packet"
                              eFormatHex,           // Format to use
                              1,                    // Size of each item in 
                                                    // bytes
                              nbytes,               // Number of items
                              16,                   // Number per line
                              LLDB_INVALID_ADDRESS, // Don't show addresses 
                                                    // before each line
                              0, 0);                // No bitfields
        } break;

        case KDP_READIOPORT: {
          const uint16_t lcpu = packet.GetU16(&offset);
          const uint16_t address = packet.GetU16(&offset);
          const uint16_t nbytes = packet.GetU16(&offset);
          s.Printf(" (lcpu=0x%4.4x, address=0x%4.4x, nbytes=%u)", lcpu, address,
                   nbytes);
        } break;

        case KDP_WRITEIOPORT: {
          const uint16_t lcpu = packet.GetU16(&offset);
          const uint16_t address = packet.GetU16(&offset);
          const uint16_t nbytes = packet.GetU16(&offset);
          s.Printf(" (lcpu = %u, addr = 0x%4.4x, nbytes = %u, bytes = \n", lcpu,
                   address, nbytes);
          if (nbytes > 0)
            DumpDataExtractor(packet, 
                              &s,                   // Stream to dump to
                              offset,               // Offset within "packet"
                              eFormatHex,           // Format to use
                              1,                    // Size of each item in 
                                                    // bytes
                              nbytes,               // Number of items
                              16,                   // Number per line
                              LLDB_INVALID_ADDRESS, // Don't show addresses 
                                                    // before each line
                              0, 0);                // No bitfields
        } break;

        case KDP_DUMPINFO: {
          const uint32_t count = packet.GetByteSize() - offset;
          s.Printf(" (count = %u, bytes = \n", count);
          if (count > 0)
            DumpDataExtractor(packet, 
                &s,                   // Stream to dump to
                offset,               // Offset within "packet"
                eFormatHex,           // Format to use
                1,                    // Size of each item in bytes
                count,                // Number of items
                16,                   // Number per line
                LLDB_INVALID_ADDRESS, // Don't show addresses before each line
                0, 0);                // No bitfields

        } break;
        }
      }
    } else {
      error_desc = "error: invalid packet command: ";
    }
  }

  if (error_desc) {
    s.PutCString(error_desc);

    DumpDataExtractor(packet,
                      &s,                   // Stream to dump to
                      0,                    // Offset into "packet"
                      eFormatBytes,         // Dump as hex bytes
                      1,                    // Size of each item is 1 for 
                                            // single bytes
                      packet.GetByteSize(), // Number of bytes
                      UINT32_MAX,           // Num bytes per line
                      LLDB_INVALID_ADDRESS, // Base address
                      0, 0);                // Bitfield info set to not do  
                                            // anything bitfield related
  }
}