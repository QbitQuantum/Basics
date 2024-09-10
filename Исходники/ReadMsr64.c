/**
  Read data to MSR.

  @param  Index                Register index of MSR.

  @return Value read from MSR.

**/
UINT64
EFIAPI
AsmReadMsr64 (
  IN UINT32  Index
  )
{
  return __readmsr (Index);
}