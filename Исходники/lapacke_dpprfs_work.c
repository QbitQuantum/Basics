lapack_int LAPACKE_dpprfs_work( int matrix_layout, char uplo, lapack_int n,
                                lapack_int nrhs, const double* ap,
                                const double* afp, const double* b,
                                lapack_int ldb, double* x, lapack_int ldx,
                                double* ferr, double* berr, double* work,
                                lapack_int* iwork )
{
    lapack_int info = 0;
    if( matrix_layout == LAPACK_COL_MAJOR ) {
        /* Call LAPACK function and adjust info */
        LAPACK_dpprfs( &uplo, &n, &nrhs, ap, afp, b, &ldb, x, &ldx, ferr, berr,
                       work, iwork, &info );
        if( info < 0 ) {
            info = info - 1;
        }
    } else if( matrix_layout == LAPACK_ROW_MAJOR ) {
        lapack_int ldb_t = MAX(1,n);
        lapack_int ldx_t = MAX(1,n);
        double* b_t = NULL;
        double* x_t = NULL;
        double* ap_t = NULL;
        double* afp_t = NULL;
        /* Check leading dimension(s) */
        if( ldb < nrhs ) {
            info = -8;
            LAPACKE_xerbla( "LAPACKE_dpprfs_work", info );
            return info;
        }
        if( ldx < nrhs ) {
            info = -10;
            LAPACKE_xerbla( "LAPACKE_dpprfs_work", info );
            return info;
        }
        /* Allocate memory for temporary array(s) */
        b_t = (double*)LAPACKE_malloc( sizeof(double) * ldb_t * MAX(1,nrhs) );
        if( b_t == NULL ) {
            info = LAPACK_TRANSPOSE_MEMORY_ERROR;
            goto exit_level_0;
        }
        x_t = (double*)LAPACKE_malloc( sizeof(double) * ldx_t * MAX(1,nrhs) );
        if( x_t == NULL ) {
            info = LAPACK_TRANSPOSE_MEMORY_ERROR;
            goto exit_level_1;
        }
        ap_t = (double*)
               LAPACKE_malloc( sizeof(double) * ( MAX(1,n) * MAX(2,n+1) ) / 2 );
        if( ap_t == NULL ) {
            info = LAPACK_TRANSPOSE_MEMORY_ERROR;
            goto exit_level_2;
        }
        afp_t = (double*)
                LAPACKE_malloc( sizeof(double) * ( MAX(1,n) * MAX(2,n+1) ) / 2 );
        if( afp_t == NULL ) {
            info = LAPACK_TRANSPOSE_MEMORY_ERROR;
            goto exit_level_3;
        }
        /* Transpose input matrices */
        LAPACKE_dge_trans( matrix_layout, n, nrhs, b, ldb, b_t, ldb_t );
        LAPACKE_dge_trans( matrix_layout, n, nrhs, x, ldx, x_t, ldx_t );
        LAPACKE_dpp_trans( matrix_layout, uplo, n, ap, ap_t );
        LAPACKE_dpp_trans( matrix_layout, uplo, n, afp, afp_t );
        /* Call LAPACK function and adjust info */
        LAPACK_dpprfs( &uplo, &n, &nrhs, ap_t, afp_t, b_t, &ldb_t, x_t, &ldx_t,
                       ferr, berr, work, iwork, &info );
        if( info < 0 ) {
            info = info - 1;
        }
        /* Transpose output matrices */
        LAPACKE_dge_trans( LAPACK_COL_MAJOR, n, nrhs, x_t, ldx_t, x, ldx );
        /* Release memory and exit */
        LAPACKE_free( afp_t );
exit_level_3:
        LAPACKE_free( ap_t );
exit_level_2:
        LAPACKE_free( x_t );
exit_level_1:
        LAPACKE_free( b_t );
exit_level_0:
        if( info == LAPACK_TRANSPOSE_MEMORY_ERROR ) {
            LAPACKE_xerbla( "LAPACKE_dpprfs_work", info );
        }
    } else {
        info = -1;
        LAPACKE_xerbla( "LAPACKE_dpprfs_work", info );
    }
    return info;
}