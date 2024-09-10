void compute(int dimX, int dimY, int dimZ, int length, REAL_POINTER out1,
             REAL_POINTER out2)
{

    // Shows an efficient way of tiling the original code.
    // Define number of tiles based on tile_size.
    int num_tile = dimY / tile_size;

    #pragma omp parallel for collapse(3)
    for (int i = 0; i < dimX; i++) {
        //!!a Tile loop j.
        for (int j = 0; j < num_tile; j++) {
            //!!a Tile loop k.
            //%% EXERCISE: Correctly put limits for loop k as shown in loop j.
            for (int k = 0; k < num_tile; k++) {
                int startj = j * tile_size;
                int endj = startj + tile_size;
                int startk = k * tile_size;
                int endk = startk + tile_size;
                //!!b Indexing inside a particular j tile.
                for (int jj = startj; jj < endj; jj++) {
                    //!!b Indexing inside a particular k tile.
                    for (int kk = startk; kk < endk; kk++) {

                        //!!b Notice how the index offset was found in the code shown in folder 0.
                        //%% EXERCISE: Correctly fill in % % based following example in folder 0.
                        int idx = (i * dimY * dimZ + jj * dimZ + kk) * length;

                        REAL_POINTER pout1 = out1 + idx;
                        REAL_POINTER pout2 = out2 + idx;
                        for (int n = 0; n < length; n++) {
                            REAL val1 = log2f(i + n + 2.0);
                            for (int m = 0; m < length; m++) {
                                /* NOTE: For MIC architecture, Intel compiler
                                 * understands the importance of aligned memory
                                 * access. Therefore, in this case, Intel
                                 * compiler will perform loop peeling which
                                 * splits the whole loop into three sections.
                                 * The middle part will have aligned memory
                                 * access, while the first part (PEEL) and the
                                 * last part (REMAINDER) may have unaligned
                                 * memory accesses. Adding "#pragma vector
                                 * aligned" makes the code generation for the
                                 * PEEL part unnecessary.
                                 */
                                REAL val2 = log2f(j + m + 2.0);
#pragma vector aligned
                                for (int l = 0; l < length - 16; l++) {
                                    REAL val3 = log2f(k + l + 2.0);
                                    REAL inc = sqrtf(val1 + val2) - sqrtf(
                                                   val2 + val3);
                                    pout1[l] = pout1[l + 16] + inc;
                                    pout2[l] = pout2[l] + inc;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}