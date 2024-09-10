INT 
  MyRtlCompareMemory(
    IN CONST VOID  *Source1,
    IN CONST VOID  *Source2,
    IN SIZE_T  Length
    )
{
    return (INT)RtlCompareMemory(Source1, Source2, Length);
}