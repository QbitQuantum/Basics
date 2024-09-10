 constants()
     : shuf128(_mm_set_epi8(15, 11, 7, 3, 14, 10, 6, 2, 13, 9, 5, 1, 12, 8,
                            4, 0)),
       const2020(_mm_set1_epi64x(0x0000000200000000)),
       constFFFF(_mm_set1_epi32(0x0F)) {
 }