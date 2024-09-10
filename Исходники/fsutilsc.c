INT _reentrant FSFileWrite(INT wNumberBytes, INT Handle, INT memory_type, INT iModulo, WORD *buffer)
{
    INT memtype;
    if (memory_type == 0x100000)
        memtype = P_MEMORY;
    else if (memory_type == 0x400000)
        memtype = Y_MEMORY;
    else
        memtype = X_MEMORY;

    return Fwrite(Handle, (INT *)buffer, (LONG) wNumberBytes, memtype, iModulo);
}