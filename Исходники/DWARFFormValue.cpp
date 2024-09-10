void
DWARFFormValue::Dump(Stream &s, const DWARFDataExtractor* debug_str_data, const DWARFCompileUnit* cu) const
{
    uint64_t uvalue = Unsigned();
    bool cu_relative_offset = false;

    bool verbose = s.GetVerbose();

    switch (m_form)
    {
    case DW_FORM_addr:      s.Address(uvalue, sizeof (uint64_t)); break;
    case DW_FORM_flag:
    case DW_FORM_data1:     s.PutHex8(uvalue);     break;
    case DW_FORM_data2:     s.PutHex16(uvalue);        break;
    case DW_FORM_sec_offset:
    case DW_FORM_data4:     s.PutHex32(uvalue);        break;
    case DW_FORM_ref_sig8:
    case DW_FORM_data8:     s.PutHex64(uvalue);        break;
    case DW_FORM_string:    s.QuotedCString(AsCString(NULL));          break;
    case DW_FORM_exprloc:
    case DW_FORM_block:
    case DW_FORM_block1:
    case DW_FORM_block2:
    case DW_FORM_block4:
        if (uvalue > 0)
        {
            switch (m_form)
            {
            case DW_FORM_exprloc:
            case DW_FORM_block:  s.Printf("<0x%" PRIx64 "> ", uvalue);                break;
            case DW_FORM_block1: s.Printf("<0x%2.2x> ", (uint8_t)uvalue);      break;
            case DW_FORM_block2: s.Printf("<0x%4.4x> ", (uint16_t)uvalue);     break;
            case DW_FORM_block4: s.Printf("<0x%8.8x> ", (uint32_t)uvalue);     break;
            default:                                                            break;
            }

            const uint8_t* data_ptr = m_value.data;
            if (data_ptr)
            {
                const uint8_t* end_data_ptr = data_ptr + uvalue;    // uvalue contains size of block
                while (data_ptr < end_data_ptr)
                {
                    s.Printf("%2.2x ", *data_ptr);
                    ++data_ptr;
                }
            }
            else
                s.PutCString("NULL");
        }
        break;

    case DW_FORM_sdata:     s.PutSLEB128(uvalue); break;
    case DW_FORM_udata:     s.PutULEB128(uvalue); break;
    case DW_FORM_strp:
        if (debug_str_data)
        {
            if (verbose)
                s.Printf(" .debug_str[0x%8.8x] = ", (uint32_t)uvalue);

            const char* dbg_str = AsCString(debug_str_data);
            if (dbg_str)
                s.QuotedCString(dbg_str);
        }
        else
        {
            s.PutHex32(uvalue);
        }
        break;

    case DW_FORM_ref_addr:
    {
        if (cu->GetVersion() <= 2)
            s.Address(uvalue, sizeof (uint64_t) * 2);
        else
            s.Address(uvalue, 4 * 2);// 4 for DWARF32, 8 for DWARF64, but we don't support DWARF64 yet
        break;
    }
    case DW_FORM_ref1:      cu_relative_offset = true;  if (verbose) s.Printf("cu + 0x%2.2x", (uint8_t)uvalue); break;
    case DW_FORM_ref2:      cu_relative_offset = true;  if (verbose) s.Printf("cu + 0x%4.4x", (uint16_t)uvalue); break;
    case DW_FORM_ref4:      cu_relative_offset = true;  if (verbose) s.Printf("cu + 0x%4.4x", (uint32_t)uvalue); break;
    case DW_FORM_ref8:      cu_relative_offset = true;  if (verbose) s.Printf("cu + 0x%8.8" PRIx64, uvalue); break;
    case DW_FORM_ref_udata: cu_relative_offset = true;  if (verbose) s.Printf("cu + 0x%" PRIx64, uvalue); break;

    // All DW_FORM_indirect attributes should be resolved prior to calling this function
    case DW_FORM_indirect:  s.PutCString("DW_FORM_indirect"); break;
    case DW_FORM_flag_present: break;
    default:
        s.Printf("DW_FORM(0x%4.4x)", m_form);
        break;
    }

    if (cu_relative_offset)
    {
        if (verbose)
            s.PutCString(" => ");

        s.Printf("{0x%8.8" PRIx64 "}", (uvalue + (cu ? cu->GetOffset() : 0)));
    }
}