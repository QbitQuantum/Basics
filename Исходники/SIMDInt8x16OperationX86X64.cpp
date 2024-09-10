    SIMDValue SIMDInt8x16Operation::OpGreaterThanOrEqual(const SIMDValue& aValue, const SIMDValue& bValue)
    {
        X86SIMDValue x86Result;
        X86SIMDValue tmpaValue = X86SIMDValue::ToX86SIMDValue(aValue);
        X86SIMDValue tmpbValue = X86SIMDValue::ToX86SIMDValue(bValue);
        x86Result.m128i_value = _mm_max_epi8(tmpaValue.m128i_value, tmpbValue.m128i_value);  //  max(a,b) == b
        x86Result.m128i_value = _mm_cmpeq_epi8(tmpaValue.m128i_value, x86Result.m128i_value); //

        return X86SIMDValue::ToSIMDValue(x86Result);
    }