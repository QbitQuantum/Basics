    SIMDValue SIMDUtils::FromSimdBits(const SIMDValue value)
    {
        X86SIMDValue x86Result;
        X86SIMDValue v = X86SIMDValue::ToX86SIMDValue(value);

        _mm_store_ps(x86Result.f32, v.m128_value);

        return X86SIMDValue::ToSIMDValue(x86Result);
    }