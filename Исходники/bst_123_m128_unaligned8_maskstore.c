double bst_compute_123_m128_unaligned8_maskstore( void*_bst_obj, double* p, double* q, size_t nn ) {
    segments_t* mem = (segments_t*) _bst_obj;
    int n, i, r, l_end, j, l_end_pre;
    double t, e_tmp;
    double* e = mem->e, *w = mem->w;
    int* root = mem->r;
    __m128d v_tmp;
    __m128d v00, v01, v02, v03;
    __m128d v10, v11, v12, v13;
    __m128d v20, v21, v22, v23;
    __m128d v30, v31, v32, v33;
    __m128i v_cur_roots;
    __m128 v_rootmask0, v_rootmask1;
    // initialization
    // mem->n = nn;
    n = nn; // subtractions with n potentially negative. say hello to all the bugs

    int idx1, idx2, idx3;
    
    idx1 = IDX(n,n);
    e[idx1] = q[n];
    idx1++;
    for (i = n-1; i >= 0; --i) {
        idx1 -= 2*(n-i)+1;
        idx2 = idx1 + 1;
        e[idx1] = q[i];
        w[idx1] = q[i];
        for (j = i+1; j < n+1; ++j,++idx2) {
            e[idx2] = INFINITY;
            w[idx2] = w[idx2-1] + p[j-1] + q[j];
        }
        idx3 = idx1; 
        for (r = i; r < n; ++r) {
            // idx2 = IDX(r+1, r+1);
            idx1 = idx3;
            l_end = idx2 + (n-r);
            // l_end points to the first entry after the current row
            e_tmp = e[idx1++];
            // calculate until a multiple of 8 doubles is left
            // 8 = 4 * 2 128-bit vectors
            l_end_pre = idx2 + ((n-r)&7);
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
            for( ; idx2 < l_end; idx2 += 8 ) {
                v01 = _mm_loadu_pd( &w[idx1  ] );
                v11 = _mm_loadu_pd( &w[idx1+2] );
                v21 = _mm_loadu_pd( &w[idx1+4] );
                v31 = _mm_loadu_pd( &w[idx1+6] );

                v00 = _mm_loadu_pd( &e[idx2  ] );
                v01 = _mm_add_pd( v01, v_tmp ); 
                v10 = _mm_loadu_pd( &e[idx2+2] );
                v11 = _mm_add_pd( v11, v_tmp );
                v20 = _mm_loadu_pd( &e[idx2+4] );
                v21 = _mm_add_pd( v21, v_tmp );
                v30 = _mm_loadu_pd( &e[idx2+6] );
                v31 = _mm_add_pd( v31, v_tmp );

                v01 = _mm_add_pd( v01, v00 );
                v03 = _mm_loadu_pd( &e[idx1  ] );
                v11 = _mm_add_pd( v11, v10 );
                v13 = _mm_loadu_pd( &e[idx1+2] );
                v21 = _mm_add_pd( v21, v20 );
                v23 = _mm_loadu_pd( &e[idx1+4] );
                v31 = _mm_add_pd( v31, v30 );
                v33 = _mm_loadu_pd( &e[idx1+6] );

                v02 = _mm_cmplt_pd( v01, v03 );
                v12 = _mm_cmplt_pd( v11, v13 );
                v22 = _mm_cmplt_pd( v21, v23 );
                v32 = _mm_cmplt_pd( v31, v33 );

                _mm_maskstore_pd( &e[idx1  ],
                        _mm_castpd_si128( v02 ), v01 );
                _mm_maskstore_pd( &e[idx1+2],
                        _mm_castpd_si128( v12 ), v11 );
                _mm_maskstore_pd( &e[idx1+4],
                        _mm_castpd_si128( v22 ), v21 );
                _mm_maskstore_pd( &e[idx1+6], 
                        _mm_castpd_si128( v32 ), v31 );

                v_rootmask0 = _mm_shuffle_ps(
                        _mm_castpd_ps( v02 ),
                        _mm_castpd_ps( v12 ),
                        _MM_SHUFFLE(0,2,0,2) );
                v_rootmask1 = _mm_shuffle_ps(
                        _mm_castpd_ps( v12 ),
                        _mm_castpd_ps( v22 ),
                        _MM_SHUFFLE(0,2,0,2) );

                _mm_maskstore_ps( &root[idx1],
                        _mm_castps_si128( v_rootmask0 ),
                        _mm_castsi128_ps( v_cur_roots ) );
                _mm_maskstore_ps( &root[idx1+4],
                        _mm_castps_si128( v_rootmask1 ),
                        _mm_castsi128_ps( v_cur_roots ) );
                
                idx1 += 8;
            }
            idx3++;
        }
    }


    return e[IDX(0,n)];
}