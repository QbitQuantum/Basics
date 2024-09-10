double bst_compute_129_m256_maskstore_root_aligned( void*_bst_obj, double* p, double* q, size_t nn ) {
    segments_t* mem = (segments_t*) _bst_obj;
    int n, i, r, l_end, j, l_end_pre;
    double t, e_tmp;
    double* e = mem->e, *w = mem->w;
    int* root = mem->r;
    __m256d v_tmp;
    __m256d v00, v01, v02, v03;
    __m256d v10, v11, v12, v13;
    __m256d v20, v21, v22, v23;
    __m256d v30, v31, v32, v33;
    __m256i v_cur_roots;
    __m256 v_rootmask0, v_rootmask1;
    // initialization
    // mem->n = nn;
    n = nn; // subtractions with n potentially negative. say hello to all the bugs

    int idx1, idx1_root;
    int idx2;
    int idx3, idx3_root;
    int pad_root, pad, pad_r;
    
    idx1      = ((int) mem->e_sz) - 1;
    idx1_root = ((int) mem->r_sz);
    // the conventio is that iteration i, idx1 points to the first element of line i+1
    e[idx1++] = q[n];
    
    // pad contains the padding for row i+1
    // for row n it's always 3
    pad = 3;
    pad_root = 7;
    for (i = n-1; i >= 0; --i) {
        idx1      -= 2*(n-i)+1 + pad;
        idx1_root -= 2*(n-i)+1 + pad_root;
        idx2       = idx1 + 1;
        e[idx1]    = q[i];
        w[idx1]    = q[i];
        for (j = i+1; j < n+1; ++j,++idx2) {
            e[idx2] = INFINITY;
            w[idx2] = w[idx2-1] + p[j-1] + q[j];
        }
        idx2     += pad; // padding of line i+1
        // idx2 now points to the first element of the next line

        idx3      = idx1;
        idx3_root = idx1_root;
        pad_r     = pad;
        for (r = i; r < n; ++r) {
            pad_r     = (pad_r+1)&3; // padding of line r+1
            idx1      = idx3;
            idx1_root = idx3_root;
            l_end     = idx2 + (n-r);
            // l_end points to the first entry after the current row
            e_tmp     = e[idx1++];
            idx1_root++;
            // calculate until a multiple of 8 doubles is left
            // 8 = 4 * 2 128-bit vectors
            l_end_pre = idx2 + ((n-r)&15);
            for( ; (idx2 < l_end_pre) && (idx2 < l_end); ++idx2 ) {
                t = e_tmp + e[idx2] + w[idx1];
                if (t < e[idx1]) {
                    e[idx1] = t;
                    root[idx1_root] = r;
                }
                idx1++;
                idx1_root++;
            }
            
            v_tmp = _mm256_set_pd( e_tmp, e_tmp, e_tmp, e_tmp );
            // execute the shit for 4 vectors of size 2
            v_cur_roots = _mm256_set_epi32(r, r, r, r, r, r, r, r);
            for( ; idx2 < l_end; idx2 += 16 ) {
                v01 = _mm256_load_pd( &w[idx1   ] );
                v11 = _mm256_load_pd( &w[idx1+ 4] );
                v21 = _mm256_load_pd( &w[idx1+ 8] );
                v31 = _mm256_load_pd( &w[idx1+12] );

                v00 = _mm256_load_pd( &e[idx2   ] );
                v01 = _mm256_add_pd( v01, v_tmp ); 
                v10 = _mm256_load_pd( &e[idx2+ 4] );
                v11 = _mm256_add_pd( v11, v_tmp );
                v20 = _mm256_load_pd( &e[idx2+ 8] );
                v21 = _mm256_add_pd( v21, v_tmp );
                v30 = _mm256_load_pd( &e[idx2+12] );
                v31 = _mm256_add_pd( v31, v_tmp );

                v01 = _mm256_add_pd( v01, v00 );
                v03 = _mm256_load_pd( &e[idx1   ] );
                v11 = _mm256_add_pd( v11, v10 );
                v13 = _mm256_load_pd( &e[idx1+ 4] );
                v21 = _mm256_add_pd( v21, v20 );
                v23 = _mm256_load_pd( &e[idx1+ 8] );
                v31 = _mm256_add_pd( v31, v30 );
                v33 = _mm256_load_pd( &e[idx1+12] );

                v02 = _mm256_cmp_pd( v01, v03, _CMP_LT_OQ );
                v12 = _mm256_cmp_pd( v11, v13, _CMP_LT_OQ );
                v22 = _mm256_cmp_pd( v21, v23, _CMP_LT_OQ );
                v32 = _mm256_cmp_pd( v31, v33, _CMP_LT_OQ );

                _mm256_maskstore_pd( &e[idx1   ],
                        _mm256_castpd_si256( v02 ), v01 );
                _mm256_maskstore_pd( &e[idx1+ 4],
                        _mm256_castpd_si256( v12 ), v11 );

                v_rootmask0 = _mm256_insertf128_ps(
                        _mm256_castps128_ps256(
                            _mm256_cvtpd_ps(v02)),
                            _mm256_cvtpd_ps(v12) , 1
                    );

                _mm256_maskstore_pd( &e[idx1+ 8],
                        _mm256_castpd_si256( v22 ), v21 );
                _mm256_maskstore_pd( &e[idx1+12], 
                        _mm256_castpd_si256( v32 ), v31 );
                v_rootmask1 = _mm256_insertf128_ps(
                        _mm256_castps128_ps256(
                            _mm256_cvtpd_ps(v22)),
                            _mm256_cvtpd_ps(v32) , 1
                    );
                
                _mm256_maskstore_ps( &root[idx1_root    ],
                        _mm256_castps_si256( v_rootmask0 ),
                        _mm256_castsi256_ps( v_cur_roots ) );
                _mm256_maskstore_ps( &root[idx1_root + 8],
                        _mm256_castps_si256( v_rootmask1 ),
                        _mm256_castsi256_ps( v_cur_roots ) );
                idx1      += 16;
                idx1_root += 16;
            }
            idx2 += pad_r;
            idx3++;
            idx3_root++;
        }
        pad      = (pad     -1)&3;
        pad_root = (pad_root-1)&7;
    }
    // the index of the last item of the first row is ((n/4)+1)*4-1, due to the padding
    // if n is even, the total number of entries in the first
    // row of the table is odd, so we need padding
    return e[ ((n/4)+1)*4 - 1 ];
}