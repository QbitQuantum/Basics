/**
 * Performs a duplexing operation over "M[rowInOut][col] [+] M[rowIn][col]" (i.e.,
 * the wordwise addition of two columns, ignoring carries between words). The
 * output of this operation, "rand", is then used to make
 * "M[rowOut][(N_COLS-1)-col] = M[rowIn][col] XOR rand" and
 * "M[rowInOut][col] =  M[rowInOut][col] XOR rotW(rand)", where rotW is a 64-bit
 * rotation to the left and N_COLS is a system parameter.
 *
 * @param state          The current state of the sponge
 * @param rowIn          Row used only as input
 * @param rowInOut       Row used as input and to receive output after rotation
 * @param rowOut         Row receiving the output
 *
 */
inline void reducedDuplexRowSetup( uint64_t *state, uint64_t *rowIn,
                                   uint64_t *rowInOut, uint64_t *rowOut,
                                   uint64_t nCols )
{
    uint64_t* ptrWordIn = rowIn;	//In Lyra2: pointer to prev
    uint64_t* ptrWordInOut = rowInOut;	//In Lyra2: pointer to row*
    uint64_t* ptrWordOut = rowOut + (nCols-1)*BLOCK_LEN_INT64; //In Lyra2: pointer to row
    int i;

#if defined __AVX2__
    __m256i state_v[4], in_v[3], inout_v[3];
    #define t_state in_v

    state_v[0] = _mm256_load_si256( (__m256i*)(&state[0]) );
    state_v[1] = _mm256_load_si256( (__m256i*)(&state[4]) );
    state_v[2] = _mm256_load_si256( (__m256i*)(&state[8]) );
    state_v[3] = _mm256_load_si256( (__m256i*)(&state[12]) );

    for ( i = 0; i < nCols; i++ )
    {
       in_v   [0] = _mm256_loadu_si256( (__m256i*)(&ptrWordIn[0]) );
       inout_v[0] = _mm256_loadu_si256( (__m256i*)(&ptrWordInOut[0]) );
       in_v   [1] = _mm256_loadu_si256( (__m256i*)(&ptrWordIn[4]) );
       inout_v[1] = _mm256_loadu_si256( (__m256i*)(&ptrWordInOut[4]) );
       in_v   [2] = _mm256_loadu_si256( (__m256i*)(&ptrWordIn[8]) );
       inout_v[2] = _mm256_loadu_si256( (__m256i*)(&ptrWordInOut[8]) );

       state_v[0] = _mm256_xor_si256( state_v[0],  _mm256_add_epi64( in_v[0],
                                                                inout_v[0] ) );
       state_v[1] = _mm256_xor_si256( state_v[1],  _mm256_add_epi64( in_v[1],
                                                                inout_v[1] ) );
       state_v[2] = _mm256_xor_si256( state_v[2],  _mm256_add_epi64( in_v[2],
                                                                inout_v[2] ) );

       LYRA_ROUND_AVX2( state_v[0], state_v[1], state_v[2], state_v[3] );

       _mm256_storeu_si256( (__m256i*)(&ptrWordOut[0]),
                              _mm256_xor_si256( state_v[0], in_v[0] ) );
       _mm256_storeu_si256( (__m256i*)(&ptrWordOut[4]),
                              _mm256_xor_si256( state_v[1], in_v[1] ) );
       _mm256_storeu_si256( (__m256i*)(&ptrWordOut[8]),
                              _mm256_xor_si256( state_v[2], in_v[2] ) );

       //M[row*][col] = M[row*][col] XOR rotW(rand)
      t_state[0] = _mm256_permute4x64_epi64( state_v[0], 0x93 );
      t_state[1] = _mm256_permute4x64_epi64( state_v[1], 0x93 );
      t_state[2] = _mm256_permute4x64_epi64( state_v[2], 0x93 );

      inout_v[0] = _mm256_xor_si256( inout_v[0],
                         _mm256_blend_epi32( t_state[0], t_state[2], 0x03 ) );
      inout_v[1] = _mm256_xor_si256( inout_v[1],
                         _mm256_blend_epi32( t_state[1], t_state[0], 0x03 ) );
      inout_v[2] = _mm256_xor_si256( inout_v[2],
                         _mm256_blend_epi32( t_state[2], t_state[1], 0x03 ) );

      _mm256_storeu_si256( (__m256i*)&ptrWordInOut[0], inout_v[0] );
      _mm256_storeu_si256( (__m256i*)&ptrWordInOut[4], inout_v[1] );
      _mm256_storeu_si256( (__m256i*)&ptrWordInOut[8], inout_v[2] );

       //Inputs: next column (i.e., next block in sequence)
       ptrWordInOut += BLOCK_LEN_INT64;
       ptrWordIn += BLOCK_LEN_INT64;
       //Output: goes to previous column
       ptrWordOut -= BLOCK_LEN_INT64;
    }

    _mm256_store_si256( (__m256i*)&state[0], state_v[0] );
    _mm256_store_si256( (__m256i*)&state[4], state_v[1] );
    _mm256_store_si256( (__m256i*)&state[8], state_v[2] );
    _mm256_store_si256( (__m256i*)&state[12], state_v[3] );

    #undef t_state 

#elif defined __AVX__

        __m128i state_v[6], in_v[6], inout_v[6];

    for ( i = 0; i < nCols; i++ )
    {

        state_v[0] = _mm_load_si128( (__m128i*)(&state[0]) );
        state_v[1] = _mm_load_si128( (__m128i*)(&state[2]) );
        state_v[2] = _mm_load_si128( (__m128i*)(&state[4]) );
        state_v[3] = _mm_load_si128( (__m128i*)(&state[6]) );
        state_v[4] = _mm_load_si128( (__m128i*)(&state[8]) );
        state_v[5] = _mm_load_si128( (__m128i*)(&state[10]) );

        inout_v[0]    = _mm_load_si128( (__m128i*)(&ptrWordInOut[0]) );
        inout_v[1]    = _mm_load_si128( (__m128i*)(&ptrWordInOut[2]) );
        inout_v[2]    = _mm_load_si128( (__m128i*)(&ptrWordInOut[4]) );
        inout_v[3]    = _mm_load_si128( (__m128i*)(&ptrWordInOut[6]) );
        inout_v[4]    = _mm_load_si128( (__m128i*)(&ptrWordInOut[8]) );
        inout_v[5]    = _mm_load_si128( (__m128i*)(&ptrWordInOut[10]) );

        in_v[0]    = _mm_load_si128( (__m128i*)(&ptrWordIn[0]) );
        in_v[1]    = _mm_load_si128( (__m128i*)(&ptrWordIn[2]) );
        in_v[2]    = _mm_load_si128( (__m128i*)(&ptrWordIn[4]) );
        in_v[3]    = _mm_load_si128( (__m128i*)(&ptrWordIn[6]) );
        in_v[4]    = _mm_load_si128( (__m128i*)(&ptrWordIn[8]) );
        in_v[5]    = _mm_load_si128( (__m128i*)(&ptrWordIn[10]) );

        _mm_store_si128( (__m128i*)(&state[0]),
                          _mm_xor_si128( state_v[0],
                                         _mm_add_epi64( in_v[0],
                                                        inout_v[0] ) ) );
        _mm_store_si128( (__m128i*)(&state[2]),
                          _mm_xor_si128( state_v[1],
                                         _mm_add_epi64( in_v[1],
                                                        inout_v[1] ) ) );
        _mm_store_si128( (__m128i*)(&state[4]),
                          _mm_xor_si128( state_v[2],
                                         _mm_add_epi64( in_v[2],
                                                        inout_v[2] ) ) );
        _mm_store_si128( (__m128i*)(&state[6]),
                          _mm_xor_si128( state_v[3],
                                         _mm_add_epi64( in_v[3],
                                                        inout_v[3] ) ) );
        _mm_store_si128( (__m128i*)(&state[8]),
                          _mm_xor_si128( state_v[4],
                                         _mm_add_epi64( in_v[4],
                                                        inout_v[4] ) ) );
        _mm_store_si128( (__m128i*)(&state[10]),
                          _mm_xor_si128( state_v[5],
                                         _mm_add_epi64( in_v[5],
                                                        inout_v[5] ) ) );

    //Applies the reduced-round transformation f to the sponge's state
    reducedBlake2bLyra(state);
#else
    for ( i = 0; i < nCols; i++ )
    {

    //Absorbing "M[prev] [+] M[row*]"
    state[0]  ^= (ptrWordIn[0]  + ptrWordInOut[0]);
    state[1]  ^= (ptrWordIn[1]  + ptrWordInOut[1]);
    state[2]  ^= (ptrWordIn[2]  + ptrWordInOut[2]);
    state[3]  ^= (ptrWordIn[3]  + ptrWordInOut[3]);
    state[4]  ^= (ptrWordIn[4]  + ptrWordInOut[4]);
    state[5]  ^= (ptrWordIn[5]  + ptrWordInOut[5]);
    state[6]  ^= (ptrWordIn[6]  + ptrWordInOut[6]);
    state[7]  ^= (ptrWordIn[7]  + ptrWordInOut[7]);
    state[8]  ^= (ptrWordIn[8]  + ptrWordInOut[8]);
    state[9]  ^= (ptrWordIn[9]  + ptrWordInOut[9]);
    state[10] ^= (ptrWordIn[10] + ptrWordInOut[10]);
    state[11] ^= (ptrWordIn[11] + ptrWordInOut[11]);
    //Applies the reduced-round transformation f to the sponge's state
    reducedBlake2bLyra(state);

    //M[row][col] = M[prev][col] XOR rand
#endif


      #if defined __AVX2__

      #elif defined __AVX__

         state_v[0] = _mm_load_si128( (__m128i*)(&state[0]) );
         state_v[1] = _mm_load_si128( (__m128i*)(&state[2]) );
         state_v[2] = _mm_load_si128( (__m128i*)(&state[4]) );
         state_v[3] = _mm_load_si128( (__m128i*)(&state[6]) );
         state_v[4] = _mm_load_si128( (__m128i*)(&state[8]) );
         state_v[5] = _mm_load_si128( (__m128i*)(&state[10]) );

         _mm_store_si128( (__m128i*)(&ptrWordOut[0]),
                           _mm_xor_si128( state_v[0], in_v[0] ) );
         _mm_store_si128( (__m128i*)(&ptrWordOut[2]),
                           _mm_xor_si128( state_v[1], in_v[1] ) );
         _mm_store_si128( (__m128i*)(&ptrWordOut[4]),
                           _mm_xor_si128( state_v[2], in_v[2] ) );
         _mm_store_si128( (__m128i*)(&ptrWordOut[6]),
                           _mm_xor_si128( state_v[3], in_v[3] ) );
         _mm_store_si128( (__m128i*)(&ptrWordOut[8]),
                           _mm_xor_si128( state_v[4], in_v[4] ) );
         _mm_store_si128( (__m128i*)(&ptrWordOut[10]),
                           _mm_xor_si128( state_v[5], in_v[5] ) );

      #else

    ptrWordOut[0] = ptrWordIn[0]  ^ state[0];
    ptrWordOut[1] = ptrWordIn[1]  ^ state[1];
    ptrWordOut[2] = ptrWordIn[2]  ^ state[2];
    ptrWordOut[3] = ptrWordIn[3]  ^ state[3];
    ptrWordOut[4] = ptrWordIn[4]  ^ state[4];
    ptrWordOut[5] = ptrWordIn[5]  ^ state[5];
    ptrWordOut[6] = ptrWordIn[6]  ^ state[6];
    ptrWordOut[7] = ptrWordIn[7]  ^ state[7];
    ptrWordOut[8] = ptrWordIn[8]  ^ state[8];
    ptrWordOut[9] = ptrWordIn[9]  ^ state[9];
    ptrWordOut[10] = ptrWordIn[10] ^ state[10];
    ptrWordOut[11] = ptrWordIn[11] ^ state[11];
#endif

    //M[row*][col] = M[row*][col] XOR rotW(rand)
// Need to fix this before taking state load/store out of loop
#ifdef __AVX2__


#else

    ptrWordInOut[0]  ^= state[11];
    ptrWordInOut[1]  ^= state[0];
    ptrWordInOut[2]  ^= state[1];
    ptrWordInOut[3]  ^= state[2];
    ptrWordInOut[4]  ^= state[3];
    ptrWordInOut[5]  ^= state[4];
    ptrWordInOut[6]  ^= state[5];
    ptrWordInOut[7]  ^= state[6];
    ptrWordInOut[8]  ^= state[7];
    ptrWordInOut[9]  ^= state[8];
    ptrWordInOut[10] ^= state[9];
    ptrWordInOut[11] ^= state[10];

       //Inputs: next column (i.e., next block in sequence)
       ptrWordInOut += BLOCK_LEN_INT64;
       ptrWordIn += BLOCK_LEN_INT64;
       //Output: goes to previous column
       ptrWordOut -= BLOCK_LEN_INT64;
    }

#endif

}

/**
 * Performs a duplexing operation over "M[rowInOut][col] [+] M[rowIn][col]" (i.e.,
 * the wordwise addition of two columns, ignoring carries between words). The
 * output of this operation, "rand", is then used to make
 * "M[rowOut][col] = M[rowOut][col] XOR rand" and
 * "M[rowInOut][col] =  M[rowInOut][col] XOR rotW(rand)", where rotW is a 64-bit
 * rotation to the left.
 *
 * @param state          The current state of the sponge
 * @param rowIn          Row used only as input
 * @param rowInOut       Row used as input and to receive output after rotation
 * @param rowOut         Row receiving the output
 *
 */
inline void reducedDuplexRow( uint64_t *state, uint64_t *rowIn,
                              uint64_t *rowInOut, uint64_t *rowOut,
                              uint64_t nCols )
{
    uint64_t* ptrWordInOut = rowInOut; //In Lyra2: pointer to row*
    uint64_t* ptrWordIn = rowIn; //In Lyra2: pointer to prev
    uint64_t* ptrWordOut = rowOut; //In Lyra2: pointer to row
    int i;


#if defined __AVX2__

    for ( i = 0; i < nCols; i++)
    {

       //Absorbing "M[prev] [+] M[row*]"

       __m256i state_v[4], in_v[3], inout_v[3];
       #define out_v in_v    // reuse register in next code block
       #define t_state in_v
       state_v[0] = _mm256_load_si256( (__m256i*)(&state[0]) );
       in_v   [0] = _mm256_loadu_si256( (__m256i*)(&ptrWordIn[0]) );
       inout_v[0] = _mm256_loadu_si256( (__m256i*)(&ptrWordInOut[0]) );
       state_v[1] = _mm256_load_si256( (__m256i*)(&state[4]) );
       in_v   [1] = _mm256_loadu_si256( (__m256i*)(&ptrWordIn[4]) );
       inout_v[1] = _mm256_loadu_si256( (__m256i*)(&ptrWordInOut[4]) );
       state_v[2] = _mm256_load_si256( (__m256i*)(&state[8]) );
       in_v   [2] = _mm256_loadu_si256( (__m256i*)(&ptrWordIn[8]) );
       inout_v[2] = _mm256_loadu_si256( (__m256i*)(&ptrWordInOut[8]) );
       state_v[3] = _mm256_load_si256( (__m256i*)(&state[12]) );

       state_v[0] = _mm256_xor_si256( state_v[0], _mm256_add_epi64( in_v[0],
                                                               inout_v[0] ) );
       state_v[1] = _mm256_xor_si256( state_v[1], _mm256_add_epi64( in_v[1],
                                                               inout_v[1] ) );
       state_v[2] = _mm256_xor_si256( state_v[2], _mm256_add_epi64( in_v[2],
                                                               inout_v[2] ) );

       out_v[0] = _mm256_loadu_si256( (__m256i*)(&ptrWordOut[0]) );
       out_v[1] = _mm256_loadu_si256( (__m256i*)(&ptrWordOut[4]) );
       out_v[2] = _mm256_loadu_si256( (__m256i*)(&ptrWordOut[8]) );

       LYRA_ROUND_AVX2( state_v[0], state_v[1], state_v[2], state_v[3] );

       _mm256_store_si256( (__m256i*)&state[0], state_v[0] );
       _mm256_store_si256( (__m256i*)&state[4], state_v[1] );
       _mm256_store_si256( (__m256i*)&state[8], state_v[2] );
       _mm256_store_si256( (__m256i*)&state[12], state_v[3] );

       _mm256_storeu_si256( (__m256i*)(&ptrWordOut[0]),
                            _mm256_xor_si256( state_v[0], out_v[0] ) );
       _mm256_storeu_si256( (__m256i*)(&ptrWordOut[4]),
                            _mm256_xor_si256( state_v[1], out_v[1] ) );
       _mm256_storeu_si256( (__m256i*)(&ptrWordOut[8]),
                            _mm256_xor_si256( state_v[2], out_v[2] ) );

/*
       t_state[0] = _mm256_permute4x64_epi64( state_v[0], 0x93 );
       t_state[1] = _mm256_permute4x64_epi64( state_v[1], 0x93 );
       t_state[2] = _mm256_permute4x64_epi64( state_v[2], 0x93 );

       inout_v[0] = _mm256_xor_si256( inout_v[0],
                        _mm256_blend_epi32( t_state[0], t_state[2], 0x03 ) );
       inout_v[1] = _mm256_xor_si256( inout_v[1], 
                        _mm256_blend_epi32( t_state[1], t_state[0], 0x03 ) );
       inout_v[2] = _mm256_xor_si256( inout_v[2], 
                        _mm256_blend_epi32( t_state[2], t_state[1], 0x03 ) );

       _mm256_storeu_si256( (__m256i*)(&ptrWordInOut[0]), inout_v[0] );
       _mm256_storeu_si256( (__m256i*)(&ptrWordInOut[4]), inout_v[1] );
       _mm256_storeu_si256( (__m256i*)(&ptrWordInOut[8]), inout_v[2] );

       _mm256_store_si256( (__m256i*)&state[0], state_v[0] );
       _mm256_store_si256( (__m256i*)&state[4], state_v[1] );
       _mm256_store_si256( (__m256i*)&state[8], state_v[2] );
       _mm256_store_si256( (__m256i*)&state[12], state_v[3] );
*/
       #undef out_v
       #undef t_state 

    //M[rowInOut][col] = M[rowInOut][col] XOR rotW(rand)
    ptrWordInOut[0] ^= state[11];
    ptrWordInOut[1] ^= state[0];
    ptrWordInOut[2] ^= state[1];
    ptrWordInOut[3] ^= state[2];
    ptrWordInOut[4] ^= state[3];
    ptrWordInOut[5] ^= state[4];
    ptrWordInOut[6] ^= state[5];
    ptrWordInOut[7] ^= state[6];
    ptrWordInOut[8] ^= state[7];
    ptrWordInOut[9] ^= state[8];
    ptrWordInOut[10] ^= state[9];
    ptrWordInOut[11] ^= state[10];

       //Goes to next block
       ptrWordOut += BLOCK_LEN_INT64;
       ptrWordInOut += BLOCK_LEN_INT64;
       ptrWordIn += BLOCK_LEN_INT64;
    }

   #elif defined __AVX__

    for ( i = 0; i < nCols; i++)
    {

       __m128i state_v[6], in_v[6], inout_v[6];
       #define out_v in_v    // reuse register in next code block

       state_v[0] = _mm_load_si128( (__m128i*)(&state[0]) );
       state_v[1] = _mm_load_si128( (__m128i*)(&state[2]) );
       state_v[2] = _mm_load_si128( (__m128i*)(&state[4]) );
       state_v[3] = _mm_load_si128( (__m128i*)(&state[6]) );
       state_v[4] = _mm_load_si128( (__m128i*)(&state[8]) );
       state_v[5] = _mm_load_si128( (__m128i*)(&state[10]) );

       inout_v[0]    = _mm_load_si128( (__m128i*)(&ptrWordInOut[0]) );
       inout_v[1]    = _mm_load_si128( (__m128i*)(&ptrWordInOut[2]) );
       inout_v[2]    = _mm_load_si128( (__m128i*)(&ptrWordInOut[4]) );
       inout_v[3]    = _mm_load_si128( (__m128i*)(&ptrWordInOut[6]) );
       inout_v[4]    = _mm_load_si128( (__m128i*)(&ptrWordInOut[8]) );
       inout_v[5]    = _mm_load_si128( (__m128i*)(&ptrWordInOut[10]) );

       in_v[0]    = _mm_load_si128( (__m128i*)(&ptrWordIn[0]) );
       in_v[1]    = _mm_load_si128( (__m128i*)(&ptrWordIn[2]) );
       in_v[2]    = _mm_load_si128( (__m128i*)(&ptrWordIn[4]) );
       in_v[3]    = _mm_load_si128( (__m128i*)(&ptrWordIn[6]) );
       in_v[4]    = _mm_load_si128( (__m128i*)(&ptrWordIn[8]) );
       in_v[5]    = _mm_load_si128( (__m128i*)(&ptrWordIn[10]) );

       _mm_store_si128( (__m128i*)(&state[0]),
                         _mm_xor_si128( state_v[0],
                                        _mm_add_epi64( in_v[0],
                                                       inout_v[0] ) ) );
       _mm_store_si128( (__m128i*)(&state[2]),
                         _mm_xor_si128( state_v[1],
                                        _mm_add_epi64( in_v[1],
                                                       inout_v[1] ) ) );
       _mm_store_si128( (__m128i*)(&state[4]),
                         _mm_xor_si128( state_v[2],
                                        _mm_add_epi64( in_v[2],
                                                       inout_v[2] ) ) );
       _mm_store_si128( (__m128i*)(&state[6]),
                         _mm_xor_si128( state_v[3],
                                        _mm_add_epi64( in_v[3],
                                                       inout_v[3] ) ) );
       _mm_store_si128( (__m128i*)(&state[8]),
                         _mm_xor_si128( state_v[4],
                                        _mm_add_epi64( in_v[4],
                                                       inout_v[4] ) ) );
       _mm_store_si128( (__m128i*)(&state[10]),
                         _mm_xor_si128( state_v[5],
                                        _mm_add_epi64( in_v[5],
                                                       inout_v[5] ) ) );

    //Applies the reduced-round transformation f to the sponge's state
    reducedBlake2bLyra(state);

   #else

    for ( i = 0; i < nCols; i++)
    {

    state[0]  ^= (ptrWordIn[0]  + ptrWordInOut[0]);
    state[1]  ^= (ptrWordIn[1]  + ptrWordInOut[1]);
    state[2]  ^= (ptrWordIn[2]  + ptrWordInOut[2]);
    state[3]  ^= (ptrWordIn[3]  + ptrWordInOut[3]);
    state[4]  ^= (ptrWordIn[4]  + ptrWordInOut[4]);
    state[5]  ^= (ptrWordIn[5]  + ptrWordInOut[5]);
    state[6]  ^= (ptrWordIn[6]  + ptrWordInOut[6]);
    state[7]  ^= (ptrWordIn[7]  + ptrWordInOut[7]);
    state[8]  ^= (ptrWordIn[8]  + ptrWordInOut[8]);
    state[9]  ^= (ptrWordIn[9]  + ptrWordInOut[9]);
    state[10] ^= (ptrWordIn[10] + ptrWordInOut[10]);
    state[11] ^= (ptrWordIn[11] + ptrWordInOut[11]);

    //Applies the reduced-round transformation f to the sponge's state
    reducedBlake2bLyra(state);
#endif

    //M[rowOut][col] = M[rowOut][col] XOR rand

    #if defined __AVX2__
/*
       state_v[0] = _mm256_load_si256( (__m256i*)(&state[0]) );
       out_v  [0] = _mm256_loadu_si256( (__m256i*)(&ptrWordOut[0]) );
       state_v[1] = _mm256_load_si256( (__m256i*)(&state[4]) );
       out_v  [1] = _mm256_loadu_si256( (__m256i*)(&ptrWordOut[4]) );
       state_v[2] = _mm256_load_si256( (__m256i*)(&state[8]) );
       out_v  [2] = _mm256_loadu_si256( (__m256i*)(&ptrWordOut[8]) );

       _mm256_storeu_si256( (__m256i*)(&ptrWordOut[0]),
                            _mm256_xor_si256( state_v[0], out_v[0] ) );
       _mm256_storeu_si256( (__m256i*)(&ptrWordOut[4]),
                            _mm256_xor_si256( state_v[1], out_v[1] ) );
       _mm256_storeu_si256( (__m256i*)(&ptrWordOut[8]),
                            _mm256_xor_si256( state_v[2], out_v[2] ) );
*/
    #elif defined __AVX__

       state_v[0] = _mm_load_si128( (__m128i*)(&state[0]) );
       state_v[1] = _mm_load_si128( (__m128i*)(&state[2]) );
       state_v[2] = _mm_load_si128( (__m128i*)(&state[4]) );
       state_v[3] = _mm_load_si128( (__m128i*)(&state[6]) );
       state_v[4] = _mm_load_si128( (__m128i*)(&state[8]) );
       state_v[5] = _mm_load_si128( (__m128i*)(&state[10]) );

       out_v[0]    = _mm_load_si128( (__m128i*)(&ptrWordOut[0]) );
       out_v[1]    = _mm_load_si128( (__m128i*)(&ptrWordOut[2]) );
       out_v[2]    = _mm_load_si128( (__m128i*)(&ptrWordOut[4]) );
       out_v[3]    = _mm_load_si128( (__m128i*)(&ptrWordOut[6]) );
       out_v[4]    = _mm_load_si128( (__m128i*)(&ptrWordOut[8]) );
       out_v[5]    = _mm_load_si128( (__m128i*)(&ptrWordOut[10]) );

       _mm_store_si128( (__m128i*)(&ptrWordOut[0]),
                         _mm_xor_si128( state_v[0], out_v[0] ) );
       _mm_store_si128( (__m128i*)(&ptrWordOut[2]),
                         _mm_xor_si128( state_v[1], out_v[1] ) );
       _mm_store_si128( (__m128i*)(&ptrWordOut[4]),
                         _mm_xor_si128( state_v[2], out_v[2] ) );
       _mm_store_si128( (__m128i*)(&ptrWordOut[6]),
                         _mm_xor_si128( state_v[3], out_v[3] ) );
       _mm_store_si128( (__m128i*)(&ptrWordOut[8]),
                         _mm_xor_si128( state_v[4], out_v[4] ) );
       _mm_store_si128( (__m128i*)(&ptrWordOut[10]),
                         _mm_xor_si128( state_v[5], out_v[5] ) );

    //M[rowInOut][col] = M[rowInOut][col] XOR rotW(rand)
    ptrWordInOut[0] ^= state[11];
    ptrWordInOut[1] ^= state[0];
    ptrWordInOut[2] ^= state[1];
    ptrWordInOut[3] ^= state[2];
    ptrWordInOut[4] ^= state[3];
    ptrWordInOut[5] ^= state[4];
    ptrWordInOut[6] ^= state[5];
    ptrWordInOut[7] ^= state[6];
    ptrWordInOut[8] ^= state[7];
    ptrWordInOut[9] ^= state[8];
    ptrWordInOut[10] ^= state[9];
    ptrWordInOut[11] ^= state[10];

       //Goes to next block
       ptrWordOut += BLOCK_LEN_INT64;
       ptrWordInOut += BLOCK_LEN_INT64;
       ptrWordIn += BLOCK_LEN_INT64;
    }

#else
    ptrWordOut[0] ^= state[0];
    ptrWordOut[1] ^= state[1];
    ptrWordOut[2] ^= state[2];
    ptrWordOut[3] ^= state[3];
    ptrWordOut[4] ^= state[4];
    ptrWordOut[5] ^= state[5];
    ptrWordOut[6] ^= state[6];
    ptrWordOut[7] ^= state[7];
    ptrWordOut[8] ^= state[8];
    ptrWordOut[9] ^= state[9];
    ptrWordOut[10] ^= state[10];
    ptrWordOut[11] ^= state[11];

    //M[rowInOut][col] = M[rowInOut][col] XOR rotW(rand)
    ptrWordInOut[0] ^= state[11];
    ptrWordInOut[1] ^= state[0];
    ptrWordInOut[2] ^= state[1];
    ptrWordInOut[3] ^= state[2];
    ptrWordInOut[4] ^= state[3];
    ptrWordInOut[5] ^= state[4];
    ptrWordInOut[6] ^= state[5];
    ptrWordInOut[7] ^= state[6];
    ptrWordInOut[8] ^= state[7];
    ptrWordInOut[9] ^= state[8];
    ptrWordInOut[10] ^= state[9];
    ptrWordInOut[11] ^= state[10];

       //Goes to next block
       ptrWordOut += BLOCK_LEN_INT64;
       ptrWordInOut += BLOCK_LEN_INT64;
       ptrWordIn += BLOCK_LEN_INT64;
    }
#endif
}