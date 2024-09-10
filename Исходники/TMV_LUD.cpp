    void LUDiv<T>::doMakeInverseATA(MatrixView<T> ata) const
    {
        TMVAssert(ata.colsize() == pimpl->LUx.colsize());
        TMVAssert(ata.rowsize() == pimpl->LUx.colsize());
        // (At A)^-1 = A^-1 (A^-1)t
        // = (U^-1 L^-1 Pt) (P L^-1t U^-1t)
        // = U^-1 L^-1 L^-1t U^-1t
        //
        // if PLU is really AT, then
        // A^-1 = P L^-1T U^-1T
        // (At A)^-1 = P L^-1T U^-1T U^-1* L^-1* Pt

        LowerTriMatrixView<T> L = pimpl->LUx.lowerTri(UnitDiag);
        UpperTriMatrixView<T> U = pimpl->LUx.upperTri();

        if (pimpl->istrans) {
            UpperTriMatrixView<T> uinv = ata.upperTri();
            uinv = U.inverse();
            ata = uinv.transpose() * uinv.conjugate();
            ata /= L.transpose();
            ata %= L.conjugate();
            ata.reversePermuteCols(pimpl->P.getValues());
            ata.reversePermuteRows(pimpl->P.getValues());
        } else {
            LowerTriMatrixView<T> linv = ata.lowerTri(UnitDiag);
            linv = L.inverse();
            ata = linv * linv.adjoint();
            ata /= U;
            ata %= U.adjoint();
        }
    }