    SIMDValue SIMDUint16x8Operation::OpLessThan(const SIMDValue& aValue, const SIMDValue& bValue)
    {
        X86SIMDValue x86Result;
        X86SIMDValue tmpaValue = X86SIMDValue::ToX86SIMDValue(aValue);
        X86SIMDValue tmpbValue = X86SIMDValue::ToX86SIMDValue(bValue);

        // Signed comparison of unsigned ints can be done if the ints have the "sign" bit xored with 1
        tmpaValue.m128i_value = _mm_xor_si128(tmpaValue.m128i_value, X86_WORD_SIGNBITS.m128i_value);
        tmpbValue.m128i_value = _mm_xor_si128(tmpbValue.m128i_value, X86_WORD_SIGNBITS.m128i_value);
        x86Result.m128i_value = _mm_cmplt_epi16(tmpaValue.m128i_value, tmpbValue.m128i_value); // compare a < b?

        return X86SIMDValue::ToSIMDValue(x86Result);
    }