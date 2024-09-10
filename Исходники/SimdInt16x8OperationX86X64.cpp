    // SIMD.Int16x8 operation wrappers that cover instrinsics for x86/x64 system
    SIMDValue SIMDInt16x8Operation::OpInt16x8(int16 values[])
    {
        X86SIMDValue x86Result;
        // Sets the 8 signed 16-bit integer values, note in revised order: starts with x7
        x86Result.m128i_value = _mm_set_epi16(values[7], values[6], values[5], values[4], values[3], values[2], values[1], values[0]);

        return X86SIMDValue::ToSIMDValue(x86Result);
    }