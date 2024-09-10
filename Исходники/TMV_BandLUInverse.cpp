    void LU_Inverse(
        const GenBandMatrix<T1>& LUx, const ptrdiff_t* p, MatrixView<T> minv)
    {
        TMVAssert(LUx.isSquare());
        TMVAssert(minv.isSquare());
        TMVAssert(minv.colsize() == LUx.colsize());
#ifdef XDEBUG
        LowerTriMatrix<T,UnitDiag> L0(LUx.colsize());
        LU_PackedPL_Unpack(LUx,p,L0.view());
        UpperTriMatrix<T> U0 = BandMatrixViewOf(LUx,0,LUx.nhi());
        Matrix<T> PLU = L0 * U0;
        if (LUx.nlo() > 0) PLU.reversePermuteRows(p);
        Matrix<T> minv2 = PLU.inverse();
#endif

        if (minv.colsize() > 0) {
            if ( !(minv.iscm() || minv.isrm())) {
                Matrix<T,ColMajor> temp(minv.colsize(),minv.colsize());
                LU_Inverse(LUx,p,temp.view());
                minv = temp;
            } else {
                minv.setZero();
                UpperTriMatrixView<T> U = minv.upperTri();
                U = BandMatrixViewOf(LUx,0,LUx.nhi());
                TriInverse(U,LUx.nhi());
                LU_PackedPL_RDivEq(LUx,p,minv);
            }
        }

#ifdef XDEBUG
        TMV_RealType(T) normdiff = Norm(PLU*minv - T(1));
        TMV_RealType(T) kappa = Norm(PLU)*Norm(minv);
        if (normdiff > 0.001*kappa*minv.colsize()) {
            cerr<<"LUInverse:\n";
            cerr<<"LUx = "<<LUx<<endl;
            cerr<<"p = ";
            for(ptrdiff_t i=0;i<LUx.colsize();i++) cerr<<p[i]<<" ";
            cerr<<endl;
            cerr<<"PLU = "<<PLU<<endl;
            cerr<<"minv = "<<minv<<endl;
            cerr<<"minv2 = "<<minv2<<endl;
            cerr<<"m*minv = "<<PLU*minv<<endl;
            cerr<<"minv*m = "<<minv*PLU<<endl;
            cerr<<"Norm(m*minv - 1) = "<<normdiff<<endl;
            cerr<<"kappa = "<<kappa<<endl;
            abort();
        }
#endif
    }