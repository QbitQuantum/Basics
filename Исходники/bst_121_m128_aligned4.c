double bst_compute_121_m128_aligned4( void*_bst_obj, double* p, double* q, size_t nn ) {
    segments_t* mem = (segments_t*) _bst_obj;
    int n, i, r, l_end, l_end_pre, j;
    double t, e_tmp;
    double* e = mem->e, *w = mem->w;
    int* root = mem->r;
    __m128d v_tmp;
    __m128d v00, v01, v02, v03;
    __m128d v10, v11, v12, v13;
    __m128i v_cur_roots, v_old_roots, v_new_roots;
    __m128 v_rootmask;
    // initialization
    // mem->n = nn;
    n = nn; // subtractions with n potentially negative. say hello to all the bugs

    int idx1, idx2, idx3, pad, pad_r;
    
    idx1 = (n+1)*(n+2)/2 + n/2;
    e[idx1] = q[n];
    idx1++;
    pad = 1;
    // pad contains the padding for row i+1
    // for row n it's always 1
    for (i = n-1; i >= 0; --i) {
        idx1 -= 2*(n-i)+1 + pad;
        idx2 = idx1 + 1;
        e[idx1] = q[i];
        w[idx1] = q[i];
        for (j = i+1; j < n+1; ++j,++idx2) {
            e[idx2] = INFINITY;
            w[idx2] = w[idx2-1] + p[j-1] + q[j];
        }
        // idx2 now points to the beginning of the next line.
        idx2 += pad; // padding of line i+1

        idx3 = idx1;
        pad_r = pad; // padding of line r
        for (r = i; r < n; ++r) {
            pad_r = !pad_r; // padding of line r+1
            // idx2 = IDX(r+1, r+1);
            idx1 = idx3;
            l_end = idx2 + (n-r);
            e_tmp = e[idx1++];
            // calculate until a multiple of 8 doubles is left
            // 8 = 4 * 2 128-bit vectors
            l_end_pre = idx2 + ((n-r)&3);
            for( ; (idx2 < l_end_pre) && (idx2 < l_end); ++idx2 ) {
                t = e_tmp + e[idx2] + w[idx1];
                if (t < e[idx1]) {
                    e[idx1] = t;
                    root[idx1] = r;
                }
                idx1++;
            }

            v_tmp = _mm_set_pd( e_tmp, e_tmp );
            // execute the shit for 4 vectors of size 2
            v_cur_roots = _mm_set_epi32(r, r, r, r);
            for( ; idx2 < l_end; idx2 += 4 ) {
                v01 = _mm_load_pd( &w[idx1  ] );
                v11 = _mm_load_pd( &w[idx1+2] );

                v00 = _mm_load_pd( &e[idx2  ] );
                v01 = _mm_add_pd( v01, v_tmp ); // supoptimal for raw-dependency
                v10 = _mm_load_pd( &e[idx2+2] );
                v11 = _mm_add_pd( v11, v_tmp );

                v01 = _mm_add_pd( v01, v00 );
                v03 = _mm_load_pd( &e[idx1  ] );
                v11 = _mm_add_pd( v11, v10 );
                v13 = _mm_load_pd( &e[idx1+2] );

                v02 = _mm_cmplt_pd( v01, v03 );
                v12 = _mm_cmplt_pd( v11, v13 );

                v00 = _mm_or_pd( _mm_and_pd( v02, v01 ), _mm_andnot_pd( v02, v03 ));
                v10 = _mm_or_pd( _mm_and_pd( v12, v11 ), _mm_andnot_pd( v12, v13 ));

                _mm_store_pd( &e[idx1  ], v00 );
                _mm_store_pd( &e[idx1+2], v10 );

                v_rootmask = _mm_shuffle_ps(
                        _mm_castpd_ps( v02 ),
                        _mm_castpd_ps( v12 ),
                        _MM_SHUFFLE(0,2,0,2) );

                v_old_roots = _mm_lddqu_si128( &root[idx1] );
                v_new_roots = _mm_or_si128(
                        _mm_and_si128(    v_cur_roots, 
                            _mm_castps_si128( v_rootmask ) ),
                        _mm_andnot_si128( v_old_roots,
                            _mm_castps_si128( v_rootmask ) )
                        );
                _mm_storeu_si128( &root[idx1], v_new_roots );

                idx1 += 4;
            }

            idx2 += pad_r;
            idx3++;
        }
        pad = !pad;
        // every other line as padding 0, or 1, respectively
    }

    // if n is even, the total number of entries in the first
    // row of the table is odd, so we need padding
    return e[n + !(n&1)];
}