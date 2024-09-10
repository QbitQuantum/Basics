Matrix TaskSpace::Task::taskSpaceMassMatrix(const State& s) const
{
    // A^{-1} J^T
    // -------------
    Matrix jac = jacobian(s);
    Matrix jacobianTranspose = jac.transpose();
    // TODO std::cout << "DEBUG Task::taskSpaceMassMatrix jacobianTranspose " << jacobianTranspose << std::endl;
    Matrix systemMassMatrixInverseTimesJacobianTranspose(
            s.getNU(), getNumScalarTasks());

    for (unsigned int iST = 0; iST < getNumScalarTasks(); ++iST)
    {
        m_model->getMatterSubsystem().multiplyByMInv(s,
                jacobianTranspose.col(iST),
                systemMassMatrixInverseTimesJacobianTranspose.updCol(iST));
    }
    // TODO std::cout << "DEBUG Task::taskSpaceMassMatrix systemMassMatrixInverseTimesJacobianTranspose" << systemMassMatrixInverseTimesJacobianTranspose << std::endl;

    // J A^{-1} J^T
    // -------------
    Matrix taskMassMatrixInverse =
        jac * systemMassMatrixInverseTimesJacobianTranspose;
    // TODO std::cout << "DEBUG Task::taskSpaceMassMatrix taskMassMatrixInverse" << taskMassMatrixInverse << std::endl;

    // (J A^{-1} J^T)^{-1}
    // -------------------
    // TODO compute inverse in a different way; this feels messy.
    FactorLU taskMassMatrixInverseLU(taskMassMatrixInverse);
    Matrix taskMassMatrix(getNumScalarTasks(), getNumScalarTasks());
    taskMassMatrixInverseLU.inverse(taskMassMatrix);

// TODO    std::cout << "DEBUG Task::taskSpaceMassMatrix " << taskMassMatrix << std::endl;
    return taskMassMatrix;
}