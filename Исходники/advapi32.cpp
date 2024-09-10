uint Advapi32_CryptAcquireContextW(Processor *cpu)
{
    RET_VALUE = (u32) CryptAcquireContextW(
        (HCRYPTPROV *)  PARAM_PTR(0),
        (LPCWSTR)       PARAM_PTR(1),
        (LPCWSTR)       PARAM_PTR(2),
        (DWORD)         PARAM(3),
        (DWORD)         PARAM(4)
        );
    RET_PARAMS(5);

}