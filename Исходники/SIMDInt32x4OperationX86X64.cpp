    SIMDValue SIMDInt32x4Operation::OpMul(const SIMDValue& aValue, const SIMDValue& bValue)
    {
        SIMDValue result;
        X86SIMDValue x86Result;
        X86SIMDValue tmpaValue = X86SIMDValue::ToX86SIMDValue(aValue);
        X86SIMDValue tmpbValue = X86SIMDValue::ToX86SIMDValue(bValue);

        if (AutoSystemInfo::Data.SSE4_1Available())
        {   // a * b, only available in SSE4
            x86Result.m128i_value = _mm_mullo_epi32(tmpaValue.m128i_value, tmpbValue.m128i_value);
            result = X86SIMDValue::ToSIMDValue(x86Result);
        }
        else if (AutoSystemInfo::Data.SSE2Available())
        {
            // mul 2,0: r0 = a0*b0; r1 = a2*b2
            __m128i tmp1 = _mm_mul_epu32(tmpaValue.m128i_value, tmpbValue.m128i_value);
            // mul 3,1: r0=a1*b1; r1=a3*b3
            __m128i tmp2 = _mm_mul_epu32(_mm_srli_si128(tmpaValue.m128i_value, 4), _mm_srli_si128(tmpbValue.m128i_value, 4));
            // shuffle x86Results to [63..0] and pack
            x86Result.m128i_value = _mm_unpacklo_epi32(_mm_shuffle_epi32(tmp1, _MM_SHUFFLE(0, 0, 2, 0)), _mm_shuffle_epi32(tmp2, _MM_SHUFFLE(0, 0, 2, 0)));
            result = X86SIMDValue::ToSIMDValue(x86Result);
        }
        else
        {
            result.i32[SIMD_X] = aValue.i32[SIMD_X] * bValue.i32[SIMD_X];
            result.i32[SIMD_Y] = aValue.i32[SIMD_Y] * bValue.i32[SIMD_Y];
            result.i32[SIMD_Z] = aValue.i32[SIMD_Z] * bValue.i32[SIMD_Z];
            result.i32[SIMD_W] = aValue.i32[SIMD_W] * bValue.i32[SIMD_W];
        }

        return result;
    }