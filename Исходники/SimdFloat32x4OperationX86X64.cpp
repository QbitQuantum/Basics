    SIMDValue SIMDFloat32x4Operation::OpFromUint32x4(const SIMDValue& value)
    {
        X86SIMDValue x86Result, temp1;

        X86SIMDValue v = X86SIMDValue::ToX86SIMDValue(value);

        // find unsigned values above 2^31-1. Comparison is signed, so look for values < 0
        temp1.m128i_value = _mm_cmplt_epi32(v.m128i_value, X86_ALL_ZEROS.m128i_value);
        // temp1 has f32(2^32) for unsigned values above 2^31, 0 otherwise
        temp1.m128_value = _mm_and_ps(temp1.m128_value, X86_TWO_32_F4.m128_value);
        // convert
        x86Result.m128_value = _mm_cvtepi32_ps(v.m128i_value);
        // Add f32(2^32) to negative values
        x86Result.m128_value = _mm_add_ps(x86Result.m128_value, temp1.m128_value);

        return X86SIMDValue::ToSIMDValue(x86Result);
    }