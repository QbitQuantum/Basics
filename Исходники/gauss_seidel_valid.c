int gauss_seidel_solve_pivoting(int nnodes, int nnz, int *ia, int *ja,  int *iau, double *A, double *rhs, int neqs, double *x_star, double *xn1, double *xn, short init)
{
    //locals
    int i,j;
    int jstart, jend;
    double GS_res = 0.;
    //int counter = 0;

    // allocating permutation matrix
    int *P = (int *)malloc( nnodes * neqs * neqs * sizeof(int) );

    //replace the diagonal matrices with their LU and save in-place
    //also save permutation matrix band per main diagonal in [P]
    for ( i = 0; i < nnodes; i++)
        lu_serial((A + iau[i]*neqs*neqs), (P + i*neqs*neqs), neqs);

    //initializing solution [xn] with [rhs]/A(diag)
    if (init)
        for ( i = 0; i < nnodes; i++)
            for( j = 0; j < neqs; j++)
            {
                jstart = iau[i];
                xn[i*neqs + j] = rhs[i*neqs + j] / A[jstart*neqs*neqs + j*neqs + j];
            }

    do {
        //resetting [x_star]
        for ( i = 0; i < nnodes; i++)
            for( j = 0; j < neqs; j++)
                x_star[i*neqs + j] = 0.;

        //calculating [x_star] = -[O] [xn].
        for( i = 0; i < nnodes; i++)
        {
            jstart = ia[i];
            jend = ia[i+1]-1;
            for ( j = jstart; j <= jend; j++)
                if( j == iau[i] ) // this is diagonal block, skip it!
                    continue;
                else //contribute the off-diagonal elements
                    neg_matrix_vec__mult( (A + j* neqs *neqs) , (xn + ja[j]*neqs) , (x_star + i *neqs) , neqs);

            for ( j = 0; j < neqs; j++) //[x_star] = [rhs]  + [x_star]
                x_star[i *neqs + j] += rhs[i * neqs + j];

        } //matrix multiplication and addition will be finished after this!

        //solving diagonal, i.e. [xn+1] = [D]^-1 [x_star]
        for( i = 0; i < nnodes; i++)
        {
            j = iau[i];
            solve_lu_serial((P + i*neqs*neqs), (A + j*neqs*neqs), (xn1 + i*neqs), (x_star + i*neqs), neqs);

        } //xn+1 will be obtained after this loop
        //calculating residuals
        GS_res = 0.; //initial
        for ( i = 0; i < nnodes; i++)
            for( j = 0; j < neqs; j++)
                GS_res += pow((xn1[i*neqs + j] - xn[i*neqs + j]) , 2.);
        GS_res /= (neqs * nnodes);
        GS_res = sqrt(GS_res);

        //updating [xn]
        for ( i = 0; i < nnodes; i++)
            for( j = 0; j < neqs; j++)
                xn[i*neqs + j]  = xn1[i*neqs + j];
        //printf("\n%e\n", GS_res);
    } while( (GS_res >= GS_RES_EPS) /* && (counter++ < 40) */ );

    //clean - up
    free(P);

    //completed successfully!
    return 0;

}