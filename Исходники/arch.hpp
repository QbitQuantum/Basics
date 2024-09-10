inline void rotate_left_wm1(F64vec8 *v0, const F64vec8 v1)
{
    //v0 {1.0,  2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0};
    //v1 {9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};

    //v0 {8, 9, 10, 11, 12, 13, 14, 15};

    static const I32vec16 shift1(13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14);
    *v0 = _mm512_permutevar_epi32     (                                   shift1, _mm512_castpd_si512(*v0));
    *v0 = _mm512_mask_permutevar_epi32(_mm512_castpd_si512(*v0), 0xFFFCU, shift1, _mm512_castpd_si512(v1));
}