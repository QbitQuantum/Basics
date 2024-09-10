UINT64
EFIAPI
AsmWriteMsr64 (
    IN UINT32  Index,
    IN UINT64  Value
)
{
    __writemsr (Index, Value);
    return Value;
}