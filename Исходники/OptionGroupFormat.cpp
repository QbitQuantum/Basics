bool
OptionGroupFormat::ParserGDBFormatLetter (CommandInterpreter &interpreter, char format_letter, Format &format, uint32_t &byte_size)
{
    m_has_gdb_format = true;
    switch (format_letter)
    {
        case 'o': format = eFormatOctal;        m_prev_gdb_format = format_letter; return true; 
        case 'x': format = eFormatHex;          m_prev_gdb_format = format_letter; return true;
        case 'd': format = eFormatDecimal;      m_prev_gdb_format = format_letter; return true;
        case 'u': format = eFormatUnsigned;     m_prev_gdb_format = format_letter; return true;
        case 't': format = eFormatBinary;       m_prev_gdb_format = format_letter; return true;
        case 'f': format = eFormatFloat;        m_prev_gdb_format = format_letter; return true;
        case 'a': format = eFormatAddressInfo;
        {
            ExecutionContext exe_ctx(interpreter.GetExecutionContext());
            Target *target = exe_ctx.GetTargetPtr();
            if (target)
                byte_size = target->GetArchitecture().GetAddressByteSize();
            m_prev_gdb_format = format_letter;
            return true;
        }
        case 'i': format = eFormatInstruction;  m_prev_gdb_format = format_letter; return true;
        case 'c': format = eFormatChar;         m_prev_gdb_format = format_letter; return true;
        case 's': format = eFormatCString;      m_prev_gdb_format = format_letter; return true;
        case 'T': format = eFormatOSType;       m_prev_gdb_format = format_letter; return true;
        case 'A': format = eFormatHexFloat;     m_prev_gdb_format = format_letter; return true;
        case 'b': byte_size = 1;                m_prev_gdb_size = format_letter;   return true;
        case 'h': byte_size = 2;                m_prev_gdb_size = format_letter;   return true;
        case 'w': byte_size = 4;                m_prev_gdb_size = format_letter;   return true;
        case 'g': byte_size = 8;                m_prev_gdb_size = format_letter;   return true;
        default:  break;
    }
    return false;
}