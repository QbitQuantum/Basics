void init_functions ()
{
    int out [4];

    __cpuid (out, 1);

    BOOL sse42 = (out [2] & (1 << 20)) != 0;
    BOOL sse41 = (out [2] & (1 << 19)) != 0;
    BOOL fma = (out [2] & (1 << 12)) != 0;
    BOOL avx = (out [2] & (1 << 28)) != 0;
    BOOL osxsave = (out [2] & (1 << 29)) != 0;

    __cpuidex (out, 7, 0);
    BOOL avx2 = (out [1] & 0x20) != 0;

    int i = 0;
    funcs [i] = calculate_float; method_names [i] = "float"; if (full_mode) i++;

    if (sse42) {
        funcs [i] = calculate_sse_float; method_names [i] = "float SSE"; if (full_mode) i++;
    }
    if (osxsave && avx) {
        funcs [i] = calculate_avx_float; method_names [i] = "float AVX"; if (full_mode) i++;
    }
    if (osxsave && avx && avx2) {
        funcs [i] = calculate_avx2_float; method_names [i] = "float AVX2"; if (full_mode) i++;
    }
    if (osxsave && avx && avx2 && fma) {
        funcs [i] = calculate_fma_float; method_names [i] = "float FMA"; if (full_mode) i++;
    }
    if (!full_mode) i++;

    funcs [i] = calculate_double; method_names [i] = "double"; if (full_mode) i++;

    if (sse42) {
        funcs [i] = calculate_sse_double; method_names [i] = "double SSE"; if (full_mode) i++;
    }
    if (osxsave && avx) {
        funcs [i] = calculate_avx_double; method_names [i] = "double AVX"; if (full_mode) i++;
    }
    if (osxsave && avx && avx2) {
        funcs [i] = calculate_avx2_double; method_names [i] = "double AVX2"; if (full_mode) i++;
    }
    if (osxsave && avx && avx2 && fma) {
        funcs [i] = calculate_fma_double; method_names [i] = "double FMA"; if (full_mode) i++;
    }
    if (!full_mode) i++;

    func_count = i;
    func_index = 0;
    calculate_func = funcs [func_index];
}