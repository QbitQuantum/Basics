    inline void Sort4Deg6(__m256 llrI, int pos[], int ipos[])
    {
        int llr[8] __attribute__((aligned(64)));
        const auto v1 = _mm256_set1_ps( 67108864.0f );
        const auto v2 = _mm256_mul_ps( v1, llrI );
        _mm256_store_si256((__m256i *)llr,  _mm256_cvttps_epi32(v2));

        //register float x0,x1,x2,x3,x4,x5;
        const auto x0 = llr[0];
        const auto x1 = llr[1];
        const auto x2 = llr[2];
        const auto x3 = llr[3];
        const auto x4 = llr[4];
        const auto x5 = llr[5];
        int o0 = (x0<x1) +(x0<x2)+(x0<x3)+(x0<x4)+(x0<x5);
        int o1 = (x1<=x0)+(x1<x2)+(x1<x3)+(x1<x4)+(x1<x5);
        int o2 = (x2<=x0)+(x2<=x1)+(x2<x3)+(x2<x4)+(x2<x5);
        int o3 = (x3<=x0)+(x3<=x1)+(x3<=x2)+(x3<x4)+(x3<x5);
        int o4 = (x4<=x0)+(x4<=x1)+(x4<=x2)+(x4<=x3)+(x4<x5);
        int o5 = 15-(o0+o1+o2+o3+o4);
        pos[o0] =  0;  pos[o1]= 1;  pos[o2]= 2;  pos[o3]= 3;  pos[o4]= 4;  pos[o5]= 5;  pos[6]=6;  pos[7]=7;
        ipos[ 0] = o0; ipos[ 1]=o1; ipos[ 2]=o2; ipos[ 3]=o3; ipos[ 4]=o4; ipos[ 5]=o5; ipos[6]=6; ipos[7]=7;
    }