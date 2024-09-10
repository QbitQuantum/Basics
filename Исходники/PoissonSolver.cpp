void PoissonSolver::add(const SField_t & rho,
                        Teuchos::RCP<Epetra_Vector> & LHS) const
{
    const Epetra_BlockMap & Map = LHS->Map();
    const int * MyGlobalElements = Map.MyGlobalElements();
    const int NumMyElements = Map.NumMyElements();

    NDIndex<DIM> elem;
    NDIndex<DIM> ldom = rho.getLayout().getLocalNDIndex();
    Index II = ldom[0], JJ = ldom[1];
    ST * values = LHS->Values();

    for (int lid = 0; lid < NumMyElements; ++ lid) {
        const size_t idx = MyGlobalElements[lid] % _Nx;
        const size_t idy = MyGlobalElements[lid] / _Nx;
        elem[0] = Index(idx, idx);
        elem[1] = Index(idy, idy);

        values[lid] += rho.localElement(elem);
    }
}