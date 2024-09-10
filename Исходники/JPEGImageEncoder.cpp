static void handleError(j_common_ptr common)
{
    jmp_buf* jumpBufferPtr = static_cast<jmp_buf*>(common->client_data);
    longjmp(*jumpBufferPtr, -1);
}