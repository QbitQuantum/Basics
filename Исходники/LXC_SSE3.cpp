//-----------------------------------------------------------------------------------------
// SSE3 complex multiplication with different kernel sizes
//-----------------------------------------------------------------------------------------
// SSE3 2x complex multiplication (for details see example 6-9 in Intel 64 and IA-32 Architectures Optimization Reference Manual)
// complex multiplication is defined as: (a+jb)*(c+jd) = a*c - b*d + j(a*d + b*c)
// z1 = a1*c1 - b1*d1 + j(a1*d1 + b1*c1)
// z2 = a2*c2 - b2*d2 + j(a2*d2 + b2*c2)
// A = { a1, jb1, c1, jd1 }
// B = { a2, jb2, c2, jd2 }
// C = { Re{z1}, Im{z1}, Re{z2}, Im{z2} } = { a1*c1 - b1*d1, j(a1*d1 + b1*c1), a2*c2 - b2*d2, j(a2*d2 + b2*c2) }
LXC_ERROR_CODE LXC_SSE3CpxMul_K2(uint Size, void *X, void *H, void *Z)
{
    if(!X || !H || !Z)
    {
        return LXC_ERR_INVALID_INPUT;
    }

    Size = Size*2;
    float *m_X = (float*)X;
    float *m_H = (float*)H;
    float *m_Z = (float*)Z;
    for(uint ii=0; ii < Size; ii+=4)
    {
        // local variables
        __m128 val1;
        __m128 val2;
        //__m128 val3;
        //__m128 val4;

        // load values into __m128
        val1 = _mm_load_ps(&m_X[ii]);			// _mm_load_ps:		src{ a1, b1, a2, b2 } --> val1 { a1, b1, a2, b2 }
        val2 = _mm_load_ps(&m_H[ii]);			// _mm_load_ps:		src{ c1, d1, c2, d2 } --> val2 { c1, d1, c2, d2 }

        // add/subtract, scale and store operations
        // duplicate values
        // _A1 = _mm_moveldup_ps: src{ a1, b1, a2, b2 } --> val2 { a1, a1, a2, a2 }
        // _A2 = _mm_movehdup_ps:	src{ a1, b1, a2, b2 } --> val3 { b1, b1, b2, b2 }
        // a = calc { a1*c1, a1*d1, a2*c2, a2*d2 } --> sse3 multiply
        // b = reorder im and re numbers { c1, d1, c2, d2 } --> { d1, c1, d2, c2 } and multiply { b1*d1, b1*c1, b2*d2, b2*c2 }
        // A = _mm_addsub_ps: ret { a1*c1 - b1*d1, j(a1*d1 + b1*c1), a2*c2 - b2*d2, j(a2*d2 + b2*c2) }
        // _mm_store_ps: C[0] = result0, C[1] = result1, C[2] = result2, C[3] = result3
        _mm_store_ps(&m_Z[ii], _mm_addsub_ps(_mm_mul_ps(_mm_moveldup_ps(val1), val2), _mm_mul_ps(_mm_movehdup_ps(val1), _mm_shuffle_ps(val2, val2, _MM_SHUFFLE(2,3,0,1)))));


        // old loop
        //// local variables
        //__m128 val1;
        //__m128 val2;
        //__m128 val3;
        //__m128 val4;

        //// load values into __m128
        //val1 = _mm_load_ps(&m_X[ii]);			// _mm_load_ps:		src{ a1, b1, a2, b2 } --> val1 { a1, b1, a2, b2 }
        //val2 = _mm_load_ps(&m_H[ii]);			// _mm_load_ps:		src{ c1, d1, c2, d2 } --> val2 { c1, d1, c2, d2 }

        //// duplicate values
        //val3 = _mm_moveldup_ps(val1);			// _mm_moveldup_ps: src{ a1, b1, a2, b2 } --> val2 { a1, a1, a2, a2 }
        //val4 = _mm_movehdup_ps(val1);			// _mm_movehdup_ps:	src{ a1, b1, a2, b2 } --> val3 { b1, b1, b2, b2 }

        //// sse3 multiply
        //val1 = _mm_mul_ps(val3, val2);			// calc { a1*c1, a1*d1, a2*c2, a2*d2 }
        //// reorder im and re numbers { c1, d1, c2, d2 } --> { d1, c1, d2, c2 } and multiply { b1*d1, b1*c1, b2*d2, b2*c2 }
        //val3 = _mm_mul_ps(val4, _mm_shuffle_ps(val2, val2, _MM_SHUFFLE(2,3,0,1)));

        //// add/subtract, scale and store operations
        //val3 = _mm_addsub_ps(val1, val3);		// _mm_addsub_ps: ret { a1*c1 - b1*d1, j(a1*d1 + b1*c1), a2*c2 - b2*d2, j(a2*d2 + b2*c2) }
        //_mm_store_ps(&m_Z[ii], val3);			// _mm_store_ps: C[0] = result0, C[1] = result1, C[2] = result2, C[3] = result3
    }

    return LXC_NO_ERR;
}