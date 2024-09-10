        friend float4 operator*(float4 v, const M44& m)
        {
            // 0b00000000 = 0x00
            // 0b01010101 = 0x55
            // 0b10101010 = 0xAA
            // 0b11111111 = 0xFF
            float4 hvec =
                  m.m_rows[0]*float4(_mm_shuffle_ps(v.get(), v.get(), 0x00))
                + m.m_rows[1]*float4(_mm_shuffle_ps(v.get(), v.get(), 0x55))
                + m.m_rows[2]*float4(_mm_shuffle_ps(v.get(), v.get(), 0xAA))
                + m.m_rows[3]*float4(_mm_shuffle_ps(v.get(), v.get(), 0xFF));
//            return hvec * _mm_div_ps(_mm_set1_ps(1), _mm_shuffle_ps(hvec.get(), hvec.get(), 0xFF));
            // calculate approximate reciprocal of last element of hvec using
            // rcp and one iteration of Newton's method.  This is faster than
            // using direct division.
            float4 w = _mm_shuffle_ps(hvec.get(), hvec.get(), 0xFF);
            float4 rcp = _mm_rcp_ps(w.get());
            rcp *= (2 - rcp*w);
            return hvec * rcp;
        }