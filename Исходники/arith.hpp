 result_type operator()(T const&) const
 {
   result_type that = { _mm256_set_epi16( 15, 14, 13, 12, 11, 10, 9, 8
                                        , 7,  6,  5,  4,  3,  2,  1, 0
                                        )
                      };
   return that;
 }