    static void MultEqMM(
        const T alpha, const GenDiagMatrix<Ta>& A,
        UpperTriMatrixView<T> B)
    // B = alpha * A * B
    {
        TMVAssert(A.size() == B.size());
        TMVAssert(alpha != T(0));
        TMVAssert(B.dt() == NonUnitDiag);
#ifdef XDEBUG
        //cout<<"Start MultEqMM: alpha = "<<alpha<<endl;
        //cout<<"A = "<<TMV_Text(A)<<"  "<<A<<endl;
        //cout<<"B = "<<TMV_Text(B)<<"  "<<B<<endl;
        Matrix<T> B0 = B;
        Matrix<Ta> A0 = A;
        Matrix<T> B2 = alpha*A0*B0;
#endif

        if (B.isconj()) MultEqMM(TMV_CONJ(alpha),A.conjugate(),B.conjugate());
        else if (A.size() > 0) {
            if (alpha == T(1)) 
                if (A.diag().isconj())
                    DoMultEqMM<true,true>(TMV_REAL(alpha),A,B);
                else
                    DoMultEqMM<true,false>(TMV_REAL(alpha),A,B);
            else if (TMV_IMAG(alpha) == TMV_RealType(T)(0)) 
                if (A.diag().isconj())
                    DoMultEqMM<false,true>(TMV_REAL(alpha),A,B);
                else
                    DoMultEqMM<false,false>(TMV_REAL(alpha),A,B);
            else 
                if (A.diag().isconj())
                    DoMultEqMM<false,true>(alpha,A,B);
                else
                    DoMultEqMM<false,false>(alpha,A,B);
        }

#ifdef XDEBUG
        if (!(Norm(Matrix<T>(B)-B2) <= 
              0.001*(TMV_ABS(alpha)*Norm(A0)*Norm(B0)))) {
            cerr<<"MultEqMM: alpha = "<<alpha<<endl;
            cerr<<"A = "<<TMV_Text(A)<<" step "<<A.diag().step()<<"  "<<A0<<endl;
            cerr<<"B = "<<TMV_Text(B)<<"  "<<B0<<endl;
            cerr<<"-> B = "<<B<<endl;
            cerr<<"B2 = "<<B2<<endl;
            abort();
        }
#endif
    }