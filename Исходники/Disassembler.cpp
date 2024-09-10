size_t
Disassembler::ParseInstructions
(
    const ExecutionContext *exe_ctx,
    const AddressRange &range,
    DataExtractor& data
)
{
    Target *target = exe_ctx->target;

    const addr_t byte_size = range.GetByteSize();
    if (target == NULL || byte_size == 0 || !range.GetBaseAddress().IsValid())
        return 0;

    DataBufferHeap *heap_buffer = new DataBufferHeap (byte_size, '\0');
    DataBufferSP data_sp(heap_buffer);

    Error error;
    const size_t bytes_read = target->ReadMemory (range.GetBaseAddress(), heap_buffer->GetBytes(), heap_buffer->GetByteSize(), error);
    
    if (bytes_read > 0)
    {
        if (bytes_read != heap_buffer->GetByteSize())
            heap_buffer->SetByteSize (bytes_read);

        data.SetData(data_sp);
        if (exe_ctx->process)
        {
            data.SetByteOrder(exe_ctx->process->GetByteOrder());
            data.SetAddressByteSize(exe_ctx->process->GetAddressByteSize());
        }
        else
        {
            data.SetByteOrder(target->GetArchitecture().GetDefaultEndian());
            data.SetAddressByteSize(target->GetArchitecture().GetAddressByteSize());
        }
        return DecodeInstructions (data, 0, UINT32_MAX);
    }

    return 0;
}