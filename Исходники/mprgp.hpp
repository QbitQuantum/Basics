void SparseMPRGPSolve(const Matrix & M, const Vector & q, Vector & z)
{
    auto solver = IterativeSolver<MPRGPCapsule<Matrix,Vector,
            sparseAlphaBar<Matrix,typename Matrix::Scalar>
            > >(3*M.rows(), 0.001);
    solver.solve(M,q,z);
    if(!solver.success())
    {
        z.setZero();
        solver.solve(M,q,z);
    }
}