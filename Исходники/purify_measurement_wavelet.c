/*!
 * Initialization for the continuos Fourier transform operator.
 * 
 * \param[out] mat (purify_sparsemat_row*) Sparse matrix containing
 * the interpolation kernels for each visibility. The matrix is 
 * stored in compressed row storage format.
 * \param[out] deconv (double*) Deconvolution kernel in real space
 * \param[in] u (double*) u coodinates between -pi and pi
 * \param[in] v (double*) v coodinates between -pi and pi
 * \param[in] param structure storing information for the operator
 *
 * \authors Rafael Carrillo
 */
void purify_measurement_init_cft(purify_sparsemat_row *mat, 
                                 double *deconv, double *u, double *v, 
                                 purify_measurement_cparam *param) {

    int D = 20;
    int nmask = 9;
    int i, j;
    int nx2, ny2;
    int row, numel;
    double uinc, vinc;

// initialize wavelet kernel
    int dummy, q, len;
    double qq, *phi;
    char buf[128];
    sprintf(buf, "D%d.phi", D);
    FILE *fwav = fopen(buf, "rb");
    fread(&dummy, sizeof(int), 1, fwav);
    if(dummy != D){
        printf("%s: wrong wavelet number (%d)!\n", __FUNCTION__, dummy);
        exit(-1);
    }
    fread(&q, sizeof(int), 1, fwav);
    len = (1 << q) * (D - 1);
    qq = 1 << q;
    phi = (double *)malloc(sizeof(double) * len);
    fread(phi, sizeof(double), len, fwav);
    fclose(fwav);

    //Sparse matrix initialization
    nx2 = param->ofx*param->nx1;
    ny2 = param->ofy*param->ny1;

    mat->nrows = param->nmeas;
    mat->ncols = nx2*ny2;
//    mat->nvals = param->kx*param->ky*param->nmeas;
    mat->nvals = param->nmeas * (nmask + 1) * (nmask + 1);
    mat->real = 1;
    mat->cvals = NULL;
//    numel = param->kx*param->ky;
    numel = (nmask + 1) * (nmask + 1);
    
 
    mat->vals = (double*)malloc(mat->nvals * sizeof(double));
    PURIFY_ERROR_MEM_ALLOC_CHECK(mat->vals);
    mat->colind = (int*)malloc(mat->nvals * sizeof(int));
    PURIFY_ERROR_MEM_ALLOC_CHECK(mat->colind);
    mat->rowptr = (int*)malloc((mat->nrows + 1) * sizeof(int));
    PURIFY_ERROR_MEM_ALLOC_CHECK(mat->rowptr);

    uinc = param->umax / (nx2 / 2);
    vinc = param->vmax / (ny2 / 2);

//    sigmax = 1.0 / (double)param->nx1;
//    sigmay = 1.0 / (double)param->ny1;

//    uinc = 4.0 * M_PI / nx2;
//    vinc = 4.0 * M_PI / ny2;

// Row pointer vector
    for (j = 0; j < mat->nrows + 1; j++){
        mat->rowptr[j] = j*numel;
    }

    int idu, idv, iv, iu, iv2, iu2, counter; 
    double ufrc, vfrc;
    double fv, fu;
  //Main loop
    for (i=0; i < param->nmeas; i++){

        // always the smaller pixel:
        idu = floor(u[i] / uinc);
        idv = floor(v[i] / vinc);
        vfrc = v[i] / vinc;
        ufrc = u[i] / uinc;
        row = i * numel;

        counter = 0;
        for(iv = idv - nmask; iv <= idv; ++iv){
            fv = phi[(int) (qq * fabs(iv - vfrc) + 0.5)];
            for(iu = idu - nmask; iu <= idu; ++iu){
                fu = phi[(int) (qq * fabs(iu - ufrc) + 0.5)];
                
                iu2 = iu; iv2 = iv;
                if(iu2 < 0) iu2 += nx2;
                if(iu2 >= nx2) iu2 -= nx2;

                if(iv2 < 0) iv2 += ny2;
                if(iv2 >= ny2) iv2 -= ny2;

                mat->vals[row + counter] = fv * fu;
//                mat->vals[row + counter] = 1.0;
                mat->colind[row + counter] = iv2 * nx2 + iu2;

                counter++;
            } // for iu
        } // for iv
    } // for nmeas

    for(i = 0; i < param->nx1 * param->ny1; ++i){
        deconv[i] = 1.0;
    }

    free(phi);
}