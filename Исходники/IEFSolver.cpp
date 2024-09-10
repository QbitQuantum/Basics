void IEFSolver::buildAnisotropicMatrix(const Cavity & cav, const IGreensFunction & gf_i, const IGreensFunction & gf_o)
{
    // The total size of the cavity
    size_t cavitySize = cav.size();
    // The number of irreps in the group
    int nrBlocks = cav.pointGroup().nrIrrep();
    // The size of the irreducible portion of the cavity
    int dimBlock = cav.irreducible_size();

    // Compute SI, DI and SE, DE on the whole cavity, regardless of symmetry
    Eigen::MatrixXd SI = gf_i.singleLayer(cav.elements());
    Eigen::MatrixXd DI = gf_i.doubleLayer(cav.elements());
    Eigen::MatrixXd SE = gf_o.singleLayer(cav.elements());
    Eigen::MatrixXd DE = gf_o.doubleLayer(cav.elements());

    // Perform symmetry blocking
    // If the group is C1 avoid symmetry blocking, we will just pack the fullPCMMatrix
    // into "block diagonal" when all other manipulations are done.
    if (cav.pointGroup().nrGenerators() != 0) {
        symmetryBlocking(DI, cavitySize, dimBlock, nrBlocks);
        symmetryBlocking(SI, cavitySize, dimBlock, nrBlocks);
        symmetryBlocking(DE, cavitySize, dimBlock, nrBlocks);
        symmetryBlocking(SE, cavitySize, dimBlock, nrBlocks);
    }

    Eigen::MatrixXd a = cav.elementArea().asDiagonal();
    Eigen::MatrixXd aInv = a.inverse();

    // 1. Form T
    fullPCMMatrix_ = ((2 * M_PI * aInv - DE) * a * SI + SE * a * (2 * M_PI * aInv + DI.adjoint().eval()));
    // 2. Invert T using LU decomposition with full pivoting
    //    This is a rank-revealing LU decomposition, this allows us
    //    to test if T is invertible before attempting to invert it.
    Eigen::FullPivLU<Eigen::MatrixXd> T_LU(fullPCMMatrix_);
    if (!(T_LU.isInvertible())) PCMSOLVER_ERROR("T matrix is not invertible!");
    fullPCMMatrix_ = T_LU.inverse();
    Eigen::FullPivLU<Eigen::MatrixXd> SI_LU(SI);
    if (!(SI_LU.isInvertible())) PCMSOLVER_ERROR("SI matrix is not invertible!");
    fullPCMMatrix_ *= ((2 * M_PI * aInv - DE) - SE * SI_LU.inverse() * (2 * M_PI * aInv - DI));
    fullPCMMatrix_ *= a;
    // 5. Symmetrize K := (K + K+)/2
    if (hermitivitize_) {
        hermitivitize(fullPCMMatrix_);
    }
    // Pack into a block diagonal matrix
    // For the moment just packs into a std::vector<Eigen::MatrixXd>
    symmetryPacking(blockPCMMatrix_, fullPCMMatrix_, dimBlock, nrBlocks);
    std::ofstream matrixOut("PCM_matrix");
    matrixOut << "fullPCMMatrix" << std::endl;
    matrixOut << fullPCMMatrix_ << std::endl;
    for (int i = 0; i < nrBlocks; ++i) {
        matrixOut << "Block number " << i << std::endl;
        matrixOut << blockPCMMatrix_[i] << std::endl;
    }

    built_ = true;
}