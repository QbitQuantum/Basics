void X86CpuUtil::callCpuId(uint32_t inEax, uint32_t inEcx, X86CpuId* outResult) {

#ifdef _MSC_VER
// 2009-02-05: Thanks to Mike Tajmajer for supporting VC7.1 compiler.
// ASMJIT_HOST_X64 is here only for readibility, only VS2005 can compile 64-bit code.
# if _MSC_VER >= 1400 || defined(ASMJIT_HOST_X64)
  // Done by intrinsics.
  __cpuidex(reinterpret_cast<int*>(outResult->i), inEax, inEcx);
# else // _MSC_VER < 1400
  uint32_t cpuid_eax = inEax;
  uint32_t cpuid_ecx = inCax;
  uint32_t* cpuid_out = outResult->i;

  __asm {
    mov     eax, cpuid_eax
    mov     ecx, cpuid_ecx
    mov     edi, cpuid_out
    cpuid
    mov     dword ptr[edi +  0], eax
    mov     dword ptr[edi +  4], ebx
    mov     dword ptr[edi +  8], ecx
    mov     dword ptr[edi + 12], edx
  }
# endif // _MSC_VER < 1400

#elif defined(__GNUC__)
// Note, patched to preserve ebx/rbx register which is used by GCC.
# if defined(ASMJIT_HOST_X86)
#  define __myCpuId(inEax, inEcx, outEax, outEbx, outEcx, outEdx) \
  asm ("mov %%ebx, %%edi\n"  \
       "cpuid\n"             \
       "xchg %%edi, %%ebx\n" \
       : "=a" (outEax), "=D" (outEbx), "=c" (outEcx), "=d" (outEdx) : "a" (inEax), "c" (inEcx))
# else
#  define __myCpuId(inEax, inEcx, outEax, outEbx, outEcx, outEdx) \
  asm ("mov %%rbx, %%rdi\n"  \
       "cpuid\n"             \
       "xchg %%rdi, %%rbx\n" \
       : "=a" (outEax), "=D" (outEbx), "=c" (outEcx), "=d" (outEdx) : "a" (inEax), "c" (inEcx))
# endif
  __myCpuId(inEax, inEcx, outResult->eax, outResult->ebx, outResult->ecx, outResult->edx);
#endif // COMPILER
}