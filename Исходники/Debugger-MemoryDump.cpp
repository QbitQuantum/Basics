bool CDumpMemory::DumpMemory(LPCSTR FileName, DumpFormat Format, DWORD StartPC, DWORD EndPC, DWORD /*DumpPC*/)
{
    switch (Format)
    {
    case DisassemblyWithPC:
    {
        CLog LogFile;
        if (!LogFile.Open(FileName))
        {
            g_Notify->DisplayError(stdstr_f("Failed to open\n%s", FileName).c_str());
            return false;
        }
        LogFile.SetFlush(false);
        LogFile.SetTruncateFile(false);
        g_Notify->BreakPoint(__FILE__, __LINE__);
#ifdef legacycode
        char Command[200];
        for (COpcode OpCode(StartPC);  OpCode.PC() < EndPC; OpCode.Next())
        {
            const char * szOpName = OpCode.OpcodeName();
            OpCode.OpcodeParam(Command);
            LogFile.LogF("%X: %-15s%s\r\n",OpCode.PC(),szOpName,Command);
        }
#endif
        m_StartAddress.SetValue(StartPC, true, true);
        m_EndAddress.SetValue(EndPC, true, true);
        return true;
    }
    break;
    }
    return false;
}