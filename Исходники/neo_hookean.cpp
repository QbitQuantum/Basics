SquareMatrix<Scalar,Dim> NeoHookean<Scalar,Dim>::cauchyStress(const SquareMatrix<Scalar,Dim> &F) const
{
    Scalar J = F.determinant();
    SquareMatrix<Scalar,Dim> stress = 1/J*firstPiolaKirchhoffStress(F)*F.transpose();
    return stress;
}