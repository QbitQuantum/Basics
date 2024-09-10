lapack_int LAPACKE_cgelsd( int matrix_order, lapack_int m, lapack_int n,
                           lapack_int nrhs, lapack_complex_float* a,
                           lapack_int lda, lapack_complex_float* b,
                           lapack_int ldb, float* s, float rcond,
                           lapack_int* rank )
{
    lapack_int info = 0;
    lapack_int lwork = -1;
    /* Additional scalars declarations for work arrays */
    lapack_int liwork;
    lapack_int lrwork;
    lapack_int* iwork = NULL;
    float* rwork = NULL;
    lapack_complex_float* work = NULL;
    lapack_int iwork_query;
    float rwork_query;
    lapack_complex_float work_query;
    if( matrix_order != LAPACK_COL_MAJOR && matrix_order != LAPACK_ROW_MAJOR ) {
        LAPACKE_xerbla( "LAPACKE_cgelsd", -1 );
        return -1;
    }
#ifndef LAPACK_DISABLE_NAN_CHECK
    /* Optionally check input matrices for NaNs */
    if( LAPACKE_cge_nancheck( matrix_order, m, n, a, lda ) ) {
        return -5;
    }
    if( LAPACKE_cge_nancheck( matrix_order, MAX(m,n), nrhs, b, ldb ) ) {
        return -7;
    }
    if( LAPACKE_s_nancheck( 1, &rcond, 1 ) ) {
        return -10;
    }
#endif
    /* Query optimal working array(s) size */
    info = LAPACKE_cgelsd_work( matrix_order, m, n, nrhs, a, lda, b, ldb, s,
                                rcond, rank, &work_query, lwork, &rwork_query,
                                &iwork_query );
    if( info != 0 ) {
        goto exit_level_0;
    }
    liwork = (lapack_int)iwork_query;
    lrwork = (lapack_int)rwork_query;
    lwork = LAPACK_C2INT( work_query );
    /* Allocate memory for work arrays */
    iwork = (lapack_int*)LAPACKE_malloc( sizeof(lapack_int) * liwork );
    if( iwork == NULL ) {
        info = LAPACK_WORK_MEMORY_ERROR;
        goto exit_level_0;
    }
    rwork = (float*)LAPACKE_malloc( sizeof(float) * lrwork );
    if( rwork == NULL ) {
        info = LAPACK_WORK_MEMORY_ERROR;
        goto exit_level_1;
    }
    work = (lapack_complex_float*)
        LAPACKE_malloc( sizeof(lapack_complex_float) * lwork );
    if( work == NULL ) {
        info = LAPACK_WORK_MEMORY_ERROR;
        goto exit_level_2;
    }
    /* Call middle-level interface */
    info = LAPACKE_cgelsd_work( matrix_order, m, n, nrhs, a, lda, b, ldb, s,
                                rcond, rank, work, lwork, rwork, iwork );
    /* Release memory and exit */
    LAPACKE_free( work );
exit_level_2:
    LAPACKE_free( rwork );
exit_level_1:
    LAPACKE_free( iwork );
exit_level_0:
    if( info == LAPACK_WORK_MEMORY_ERROR ) {
        LAPACKE_xerbla( "LAPACKE_cgelsd", info );
    }
    return info;
}