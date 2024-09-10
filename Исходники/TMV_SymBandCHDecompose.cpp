    void LDL_Decompose(SymBandMatrixView<T> A)
    {
        TMVAssert(A.nlo() == 1);

        if (A.uplo() == Upper) LDL_Decompose(A.adjoint());
        else if (A.isconj()) LDL_Decompose(A.conjugate());
        else if (A.size() > 0) {
            if (A.isherm()) {
#ifdef LAP 
                if (A.isdm()) LapLDL_Decompose(A);
                else {
                    HermBandMatrix<T,Lower|DiagMajor> A2 = A;
                    LapLDL_Decompose(A2.view());
                    A = A2;
                }
#else
                NonLapLDL_Decompose(A);
#endif
            } else {
                SymLDL_Decompose(A);
            }
        }
    }