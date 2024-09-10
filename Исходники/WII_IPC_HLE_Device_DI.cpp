IPCCommandResult CWII_IPC_HLE_Device_di::Open(u32 _CommandAddress, u32 _Mode)
{
    Memory::Write_U32(GetDeviceID(), _CommandAddress + 4);
    m_Active = true;
    return GetDefaultReply();
}